//
// Created by Xiaodong Liu on 4/16/22.
//

#include "AmazonHandler.h"

vector<char> AmazonHandler::AMAZON_HOST = strToVector("vcm-25919.vm.duke.edu");
vector<char> AmazonHandler::AMAZON_PORT = strToVector("34567");
vector<char> AmazonHandler::UPS_PORT_FOR_AMAZON = strToVector("56789");

const string AmazonHandler::U2ATRUCKARRIVED_NAME = "U2ATruckArrived";
const string AmazonHandler::U2ADELIVERING_NAME = "U2ADelivering";
const string AmazonHandler::U2ADELIVERED_NAME = "U2ADelivered";
const string AmazonHandler::U2ASHIPSTATUS_NAME = "U2AShipStatus";
const string AmazonHandler::U2ACHANGEADDRESS_NAME = "U2AChangeAddress";
const string AmazonHandler::ERROR_NAME = "Error";

unordered_map<string, string> AmazonHandler::nameInUPSCommands = {
        {"U2ATruckArrived", "arrived"},
        {"U2ADelivering", "delivering"},
        {"U2ADelivered", "delivered"},
        {"U2AShipStatus", "status"},
        {"U2AChangeAddress", "address"},
        {"Error", "error"}
};

AmazonHandler::AmazonHandler(shared_ptr <UPSData> _upsData): BaseHandler(_upsData,"logs/amazon_handler.log", "amazon_handler"), serverSocket(UPS_PORT_FOR_AMAZON, BACKLOG){}

AmazonHandler::AmazonHandler(shared_ptr<UPSData> _upsData,  shared_ptr<WorldSimulatorHandler> _worldSimulatorHandler,
                             shared_ptr<FrontEndHandler> _frontEndHandler): BaseHandler(_upsData,"logs/amazon_handler.log", "amazon_handler"),
                                    serverSocket(UPS_PORT_FOR_AMAZON, BACKLOG),
                                    worldSimulatorHandler(_worldSimulatorHandler),
                                    frontEndHandler(_frontEndHandler){}



void AmazonHandler::run() {
    cout << "Amazon handler is running" << endl;

    //remember to set up the server socket at the beginning
    serverSocket.setUp();

    //accept request from amazon
    this->clientFd = serverSocket.toAccept();

    thread thH(&AmazonHandler::handleNewResOrReq, this);
    thH.detach();
    thread thS(&AmazonHandler::sendCommands, this);
    thS.detach();
    thread thD(&AmazonHandler::deleteSeqNums, this);
    thD.detach();
    thread thG(&AmazonHandler::generateCommands, this);
    thG.detach();
}

void AmazonHandler::generateCommands() {
    //printLog("Amazon handler does not have automated commands");
}

Message *AmazonHandler::getNewAllocatedMessage(Message *message) {
    std::string data;
    message->SerializeToString(&data);
    string messageType = message->GetDescriptor()->name();
    Message* res = nullptr ;
    if(messageType == AmazonHandler::U2ATRUCKARRIVED_NAME){
        res = new U2ATruckArrived;
    }else if(messageType == AmazonHandler::U2ADELIVERING_NAME){
        res = new U2ADelivering;
    }else if(messageType == AmazonHandler::U2ADELIVERED_NAME){
        res = new U2ADelivered;
    }else if(messageType == AmazonHandler::U2ASHIPSTATUS_NAME){
        res = new U2AShipStatus;
    }else if(messageType == AmazonHandler::U2ACHANGEADDRESS_NAME){
        res = new U2AChangeAddress;
    }else if(messageType == AmazonHandler::ERROR_NAME){
        res = new Error;
    }else{
        return nullptr;
    }
    res->ParseFromString(data);
    return res;
}
//receive commands in a loop
void AmazonHandler::handleNewResOrReq() {
    //ask amazon to connect to world
    sendWorldID();
    while (true) {
        try {
            //sleepForSeconds(1);
            //printLog(to_string(serverSocket.getFd()));
            AmazonCommands amazonCommands;
            //printLog(to_string(clientFd));
            serverSocket.recvMesg(clientFd, amazonCommands);
            //printLog(amazonCommands.DebugString());
            if (amazonCommands.ByteSizeLong() == 0) {
                printMNTimes('@', 6,40);
                continue;
            }
            //send acks to client && deal with those commands
            handleCommands(amazonCommands);
        } catch (MyException &exp) {
            std::cout << exp.what();
            printMNTimes('?', 6, 40);
            continue;
        }
    }
}


//send commands every once in a while
void AmazonHandler::sendCommands() {
    while(true){
        printLog("sendCommands()");
        std::unique_lock <std::mutex> munique(mtx, std::defer_lock);
        munique.lock();
        if(!this->commandHashMap.empty()) {   
            UPSCommands upsCommands;     
            unordered_map < uint64_t, unique_ptr < Message > > ::iterator
            it = this->commandHashMap.begin();
            const Descriptor *descriptor = upsCommands.GetDescriptor();
            const Reflection *reflection = upsCommands.GetReflection();
            while (it != this->commandHashMap.end()) {
                Message* new_entry = getNewAllocatedMessage((it->second).get());
                const std::string name = it->second->GetDescriptor()->name();
                const FieldDescriptor * fieldDescriptor = descriptor->FindFieldByName(nameInUPSCommands[name]);
                reflection->AddAllocatedMessage(&upsCommands, fieldDescriptor, new_entry);
                // seqNumQWaitToDelete[it->first]=std::move(commandHashMap[it->first]);
                // commandHashMap.erase(it->first);
                
                ++it;
            }
            commandHashMap.clear();
            printLog(upsCommands.DebugString());
            serverSocket.resMesg(clientFd, upsCommands);
        }
        munique.unlock();
        sleepForSeconds(2.0);
    }
}


void AmazonHandler::handleA2UAskTruck(const A2UAskTruck &a2UAskTruck) {
    printLog("----------handleA2UAskTruck----------");
    //1 world->UgoPickUP
    Warehouse warehouse = a2UAskTruck.warehouse();
    upsData->insertWarehouse(warehouse);
    //printLog("----------insertWarehouse----------");
    int warehouseID = warehouse.warehouseid();
    pair<int, int64_t> message_info = worldSimulatorHandler.lock()->handleUGoPickUp(warehouseID);
    //2 insert package
    int truck_id = message_info.first;
    int64_t seq_num = message_info.second;
    for(int i=0;i<a2UAskTruck.package_size();i++){
        printMNTimes("===================", 3,3);
        PackageInfo package = a2UAskTruck.package(i);
        //Insert package to database
        upsData->insertPackage(package,warehouseID,truck_id,seq_num);
    }
}

void AmazonHandler::handleA2UPacked(const A2UPacked &a2UPacked) {
    printLog("---------------handleA2UPacked----------------------");
    int64_t package_id = a2UPacked.shipid();
    printLog(to_string(a2UPacked.shipid()));
    upsData->updatePackageStatusID(package_id,"PACKED");
}

void AmazonHandler::handleA2ULoading(const A2ULoading &a2ULoading) {
    printLog("handleA2ULoading");
    int truck_id = a2ULoading.truckid();
    upsData->updateTruckStatus(truck_id,"LOADING");
    //update package status to loading
    for(int64_t i=0;i<a2ULoading.shipid_size();i++){
        int64_t package_id = a2ULoading.shipid(i);
        upsData->updatePackageStatusID(package_id,"LOADING");
    }   
} 

void AmazonHandler::handleA2ULoaded(const A2ULoaded &a2ULoaded) {
    printLog("handleA2ULoaded");
    int truck_id = a2ULoaded.truckid();
    Warehouse warehouse = a2ULoaded.warehouse();
    int warehouse_id = warehouse.warehouseid();
    upsData->updateTruckStatus(truck_id,"LOADED");
    //1.update package status to loaded
    vector<int64_t> packageIDs;
    for(int i=0;i<a2ULoaded.shipid_size();i++){
        int64_t package_id = a2ULoaded.shipid(i);
        packageIDs.push_back(package_id);
        upsData->updatePackageStatusID(package_id,"LOADED");
    }  
    //3.check if status : no packing, no packed, no loading
    if(upsData->checkStatus4Deliver(truck_id, warehouse_id)==false){
        return;
    }
    //unordered_map<int64_t,pair<int,int>> packages = upsData->getTargetPackageInfo(packageIDs);
    unordered_map<int64_t,pair<int,int>> packages = upsData->getTargetPackageInfo(truck_id,warehouse_id);
    worldSimulatorHandler.lock()->handleUGoDeliver(packages,truck_id);
}

void AmazonHandler::handleA2UQueryShip(const A2UQueryShip &a2UQueryShip) {
    printLog("handleA2UQueryShip");
    int64_t package_id = a2UQueryShip.shipid();    
    string status = upsData->getPackageStatus(package_id);
    handleU2AShipStatus(package_id,status);
}

void AmazonHandler::handleFinish(const bool &finish) {
    printLog("handleFinish");
}
void AmazonHandler::handleA2UError(const Error &error) {
    printLog("handleA2UError");

}

void AmazonHandler::handleU2ATruckArrived(int truckID,Warehouse warehouse,vector<int64_t> packageIDs){
    printLog("handleU2ATruckArrived");
    U2ATruckArrived truckArrived;
    int64_t seq_num = seqnumCreator.updateSeq();
    truckArrived.set_seqnum(seq_num);
    truckArrived.set_truckid(truckID);
    
    for(size_t i=0;i<packageIDs.size();i++){
        truckArrived.add_shipid(packageIDs[i]);
    }
    Warehouse *wh = new Warehouse;
    wh->set_warehouseid(warehouse.warehouseid());
    wh->set_x(warehouse.x());
    wh->set_y(warehouse.y());
    truckArrived.set_allocated_warehouse(wh);
    printLog(truckArrived.DebugString());
    this->push(seq_num,truckArrived);
}

void AmazonHandler::handleU2ADelivering(int truckId,vector<int64_t> packageIDs){
    printLog("handleU2ADelivering");
    long long seq_num = seqnumCreator.updateSeq();
    U2ADelivering delivering;
    delivering.set_seqnum(seq_num);
    delivering.set_truckid(truckId);
    for(size_t i=0;i<packageIDs.size();i++){
        delivering.add_shipid(packageIDs[i]);
    }
    //TODO: push to container
    this->push(seq_num,delivering);
}

void AmazonHandler::handleU2ADelivered(int64_t package_id){
    printLog("handleU2ADelivered");
    int64_t seq_num = seqnumCreator.updateSeq();
    U2ADelivered delivered;
    delivered.set_seqnum(seq_num);
    delivered.add_shipid(package_id);
    //TODO: MULTIPLE ID? PUSH TO CONTAINER
    this->push(seq_num,delivered);
}

void AmazonHandler::handleU2AShipStatus(int64_t package_id,string status){
    printLog("handleU2AShipStatus");
    int64_t seq_num = seqnumCreator.updateSeq();
    U2AShipStatus shipStatus;
    shipStatus.set_seqnum(seq_num);
    shipStatus.set_shipid(package_id);
    shipStatus.set_status(status);
    this->push(seq_num,shipStatus);
}

void AmazonHandler::handleU2AChangeAddress(int64_t package_id,int x,int y){
    //check package status -> only can change when status are packing, packed or loading 
    //if can, update database
    printLog("handleU2AChangeAddress");
    if(upsData->changeAddress(package_id,x,y)==false){
        B2FChangeAddressResp response;
        response.set_shipid(package_id);
        int result = 0;
        response.set_result(result);
        frontEndHandler.lock()->sendChangeAddResp(response);
        return;
    }    

    //Send to world 
    // UDeliveryLocation packageInfo;
    // packageInfo.set_packageid(package_id);
    // packageInfo.set_x(x);
    // packageInfo.set_y(y);
    // worldSimulatorHandler.lock()->handleChangeAddress(packageInfo,truck_id);    
    
    //Send change address to amazon
    int64_t seq_num = seqnumCreator.updateSeq();
    U2AChangeAddress changeAdd;
    changeAdd.set_seqnum(seq_num);
    changeAdd.set_shipid(package_id);
    changeAdd.set_x(x);
    changeAdd.set_y(y);
    this->push(seq_num,changeAdd);

    //send message back to front end;
    B2FChangeAddressResp response;
    response.set_shipid(package_id);
    int result = 1;
    response.set_result(result);
    frontEndHandler.lock()->sendChangeAddResp(response);
}

void AmazonHandler::handelError(int64_t ori_num, string mess){
    int64_t seq_num = seqnumCreator.updateSeq();
    Error err;
    err.set_seqnum(seq_num);
    err.set_info(mess);
    err.set_originseqnum(ori_num);
    this->push(seq_num,err);
}

void AmazonHandler::handleCommands(const AmazonCommands &amazonCommands) {
    vector<uint64_t> acks;
    for(int i = 0; i < amazonCommands.gettruck_size(); ++i){
        acks.emplace_back(amazonCommands.gettruck(i).seqnum());
        handleA2UAskTruck(amazonCommands.gettruck(i));
        //p.push(handleA2UAskTruck_spawn, shared_from_this(), amazonCommands.gettruck(i));
    }
    for(int i = 0; i < amazonCommands.packed_size(); ++i){
        acks.emplace_back(amazonCommands.packed(i).seqnum());
        handleA2UPacked(amazonCommands.packed(i));
        //p.push(handleA2UPacked_spawn, shared_from_this(), amazonCommands.packed(i));
    }
    for(int i = 0; i < amazonCommands.loading_size(); ++i){
        acks.emplace_back(amazonCommands.loading(i).seqnum());
        handleA2ULoading(amazonCommands.loading(i));
        //p.push(handleA2ULoading_spawn, shared_from_this(),  amazonCommands.loading(i));
    }
    for(int i = 0; i < amazonCommands.loaded_size(); ++i){
        acks.emplace_back(amazonCommands.loaded(i).seqnum());
        handleA2ULoaded(amazonCommands.loaded(i));
        //p.push(handleA2ULoaded_spawn, shared_from_this(), amazonCommands.loaded(i));
    }
    for(int i = 0; i < amazonCommands.query_size(); ++i){
        acks.emplace_back(amazonCommands.query(i).seqnum());
        handleA2UQueryShip(amazonCommands.query(i));
        //p.push(handleA2UQueryShip_spawn, shared_from_this(), amazonCommands.query(i));
    }
    for(int i = 0; i < amazonCommands.error_size(); ++i){
        acks.emplace_back(amazonCommands.error(i).seqnum());
        handleA2UError(amazonCommands.error(i));
        //p.push(handleA2UError_spawn, shared_from_this(),  amazonCommands.error(i));
    }
    sendAcks(acks);
    //deal with other types
    if(amazonCommands.has_finish()){
        //p.push(handleFinish_spawn, shared_from_this(), amazonCommands.finish());
    }
    std::lock_guard <std::mutex> lck(mtx);
    for(int i = 0; i < amazonCommands.acks_size(); ++i){
        seqNumQWaitToDelete[amazonCommands.acks(i)]=std::move(commandHashMap[amazonCommands.acks(i)]);
        commandHashMap.erase(amazonCommands.acks(i));
    }
    printLog(amazonCommands.DebugString());
}

void AmazonHandler::sendAcks(vector <uint64_t> &acks) {
    if(!acks.empty()) {
        printLog("sending acks to amazon");
        printVector("send to amazon: ", acks);
        UPSCommands upsCommands;
        string pr = "Send ACT ------------" + upsCommands.DebugString();
        printLog(pr);
        for (const auto &x: acks) {
            upsCommands.add_acks(x);
        }
        for (size_t i = 0; i < acks.size(); ++i) {
            cout << acks[i] << " ";
        }
        cout << endl;
        serverSocket.resMesg(clientFd, upsCommands);
    }
}

vector <uint64_t> AmazonHandler::getAllSeqnums(const AmazonCommands &amazonCommands) {
    vector<uint64_t> res;
    for(int i = 0; i < amazonCommands.gettruck_size(); ++i){
        res.emplace_back(amazonCommands.gettruck(i).seqnum());
    }
    for(int i = 0; i < amazonCommands.loading_size(); ++i){
        res.emplace_back(amazonCommands.loading(i).seqnum());
    }
    for(int i = 0; i < amazonCommands.loaded_size(); ++i){
        res.emplace_back(amazonCommands.loaded(i).seqnum());
    }
    for(int i = 0; i < amazonCommands.query_size(); ++i){
        res.emplace_back(amazonCommands.query(i).seqnum());
    }
    for(int i = 0; i < amazonCommands.error_size(); ++i){
        res.emplace_back(amazonCommands.error(i).seqnum());
    }
    return res;
}

void AmazonHandler::sendWorldID() {
    //mesg to send
    U2AConnect u2AConnect;
    u2AConnect.set_worldid(worldSimulatorHandler.lock()->getWorldID());

    //result
    A2UConnected a2UConnected;

//    ClientSocket clientSocket(AMAZON_HOST, AMAZON_PORT);
//    clientSocket.setup();
//    clientSocket.sendMesg(u2AConnect);
    serverSocket.resMesg(clientFd, u2AConnect);
    printLog(u2AConnect.DebugString());
//    clientSocket.recvMesg(a2UConnected);
    serverSocket.recvMesg(clientFd, a2UConnected);
    printLog(a2UConnected.DebugString());
    cout << "connected message" << endl;
    cout << a2UConnected.DebugString()<< endl;
    cout << "a2UConnected's result:" << a2UConnected.result() << endl;
}


//for thread
std::thread AmazonHandler::run_spawn() {
    return std::thread(&AmazonHandler::run, this);
}


void AmazonHandler::handleA2UAskTruck_spawn(int id, shared_ptr <AmazonHandler> amazonHandler,
                                            const A2UAskTruck &a2UAskTruck) {
    amazonHandler->handleA2UAskTruck(a2UAskTruck);
}

void AmazonHandler::handleA2UPacked_spawn(int id, shared_ptr <AmazonHandler> amazonHandler, const A2UPacked &a2UPacked) {
    amazonHandler->handleA2UPacked(a2UPacked);
}

void
AmazonHandler::handleA2ULoading_spawn(int id, shared_ptr <AmazonHandler> amazonHandler,
                                      const A2ULoading &a2ULoading) {
    amazonHandler->handleA2ULoading(a2ULoading);
}

void AmazonHandler::handleA2ULoaded_spawn(int id, shared_ptr <AmazonHandler> amazonHandler,
                                          const A2ULoaded &a2ULoaded) {
    amazonHandler->handleA2ULoaded(a2ULoaded);
}

void AmazonHandler::handleA2UQueryShip_spawn(int id, shared_ptr <AmazonHandler> amazonHandler,
                                             const A2UQueryShip &a2UQueryShip) {
    amazonHandler->handleA2UQueryShip(a2UQueryShip);
}

void AmazonHandler::handleFinish_spawn(int id, shared_ptr <AmazonHandler> amazonHandler, const bool &finish) {
    amazonHandler->handleFinish(finish);
}

void
AmazonHandler::handleA2UError_spawn(int id, shared_ptr <AmazonHandler> amazonHandler, const Error &error) {
    amazonHandler->handleA2UError(error);
}


