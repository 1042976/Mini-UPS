//
// Created on 4/16/22.
//

#include "WorldSimulatorHandler.h"

vector<char> WorldSimulatorHandler::WORLDSIMULATOR_HOST = strToVector("vcm-25919.vm.duke.edu");
vector<char> WorldSimulatorHandler::WORLDSIMULATOR_PORT = strToVector("12345");
const string WorldSimulatorHandler::UGOPICKUP_NAME = "UGoPickup";
const string WorldSimulatorHandler::UGODELIVER_NAME = "UGoDeliver";
const string WorldSimulatorHandler::UQUERY_NAME = "UQuery";

unordered_map<string, string> WorldSimulatorHandler::nameInUCommands = {
        {"UGoPickup", "pickups"},
        {"UGoDeliver", "deliveries"},
        {"UQuery", "queries"}
};

WorldSimulatorHandler::WorldSimulatorHandler(shared_ptr <UPSData> _upsData):
                        BaseHandler(_upsData, "logs/worldsimulator_handler.log", "worldsimulator_handler"), clientSocket(WORLDSIMULATOR_HOST, WORLDSIMULATOR_PORT){
}

WorldSimulatorHandler::WorldSimulatorHandler(shared_ptr<UPSData> _upsData, shared_ptr<AmazonHandler> _amazonHandler,
                                             shared_ptr<FrontEndHandler> _frontEndHandler):
    BaseHandler(_upsData, "logs/worldsimulator_handler.log", "worldsimulator_handler"),  clientSocket(WORLDSIMULATOR_HOST, WORLDSIMULATOR_PORT), amazonHandler(_amazonHandler), frontEndHandler(_frontEndHandler) {
    connectToWorldSimulator();
}
void WorldSimulatorHandler::connectToWorldSimulator() {
    cout << "Connecting to world simulator..." << endl;
    UConnect uConnect;
    uConnect.set_isamazon(false);

    //init trucks
    vector<Truck> truckGroup;
    for(int i = 0; i < NUM_OF_TRUCKS; ++i){
        truckGroup.emplace_back(Truck());
        hasSentTruckQuery.emplace_back(false);
    }
    for(size_t i = 0; i < truckGroup.size(); ++i){
        //write into database the truck info
        upsData->initTruckTable(truckGroup[i]);
        //msg
        UInitTruck* uInitTruck = uConnect.add_trucks();
        uInitTruck->set_id(truckGroup[i].id);
        uInitTruck->set_x(truckGroup[i].x);
        uInitTruck->set_y(truckGroup[i].y);
    }
    UConnected uConnected;
    //connect to world simulator
    try {
        clientSocket.setup();
        while(uConnected.result() != "connected!"){
                clientSocket.sendMesg(uConnect);
                cout << uConnect.DebugString() << endl;
                clientSocket.recvMesg(uConnected);
                cout << "connected message" << endl;
                cout << uConnected.DebugString()<< endl;
        }
    }catch (MyException &exp) {
        cerr << exp.what() << endl;
        exit(EXIT_FAILURE);
    }
    
    this->worldID = uConnected.worldid();
}

int64_t WorldSimulatorHandler::getWorldID() {
    return this->worldID;
}

void WorldSimulatorHandler::run() {
    
    cout << "World simulator handler is running" << endl;
    thread thH(&WorldSimulatorHandler::handleNewResOrReq, this);
    thH.detach();
    thread thS(&WorldSimulatorHandler::sendCommands, this);
    thS.detach();
    thread thD(&WorldSimulatorHandler::deleteSeqNums, this);
    thD.detach();
    thread thG(&WorldSimulatorHandler::generateCommands, this);
    thG.detach();

    UCommands changeSpeed;
    changeSpeed.set_simspeed(100);
    clientSocket.sendMesg(changeSpeed);
}

void WorldSimulatorHandler::generateCommands() {
    //add commands you want to generate and send in loop
    while(true){
        askAllTruckStatus();
        sleepForSeconds(1);
    }
}

void WorldSimulatorHandler::handleNewResOrReq() {
    while (true) {
        try {
            sleepForSeconds(0.5);
            UResponses uResponses;
            clientSocket.recvMesg(uResponses);
            if (uResponses.ByteSizeLong() == 0) {
                printMNTimes('@', 6,40);
                continue;
            }
            //send acks to client && deal with those commands
            handleCommands(uResponses);
        } catch (MyException &exp) {
            std::cout << exp.what();
            printMNTimes('?', 6, 40);
        }
    }
}

void WorldSimulatorHandler::handleCommands(const UResponses &uResponses) {
    //printLog(uResponses.DebugString());
    vector<uint64_t> acks;
    for(int i = 0; i < uResponses.completions_size(); ++i){
        acks.emplace_back(uResponses.completions(i).seqnum());
        handleUFinished(uResponses.completions(i));
        //p.push(handleUFinished_spawn, shared_from_this(), uResponses.completions(i));
    }
    for(int i = 0; i < uResponses.delivered_size(); ++i){
        acks.emplace_back(uResponses.delivered(i).seqnum());
        handleUDeliveryMade(uResponses.delivered(i));
        //p.push(handleUDeliveryMade_spawn, shared_from_this(), uResponses.delivered(i));
    }
    for(int i = 0; i < uResponses.truckstatus_size(); ++i){
        acks.emplace_back(uResponses.truckstatus(i).seqnum());
        handleUTruck(uResponses.truckstatus(i));
        //p.push(handleUTruck_spawn, shared_from_this(), uResponses.truckstatus(i));
    }

    for(int i = 0; i < uResponses.error_size(); ++i){
        acks.emplace_back(uResponses.error(i).seqnum());
        handleUErr(uResponses.error(i));
        //p.push(handleUErr_spawn, shared_from_this(), uResponses.error(i));
    }
    sendAcks(acks);
    //deal with other types
    if(uResponses.has_finished()){
        //p.push(handleFinished_spawn, shared_from_this(), uResponses.finished());
    }
    std::lock_guard <std::mutex> lck(mtx);
    for(int i = 0; i < uResponses.acks_size(); ++i){
        seqNumQWaitToDelete[uResponses.acks(i)]=std::move(commandHashMap[uResponses.acks(i)]);
        commandHashMap.erase(uResponses.acks(i));
    }

    printMNTimes('?', 2, 40);
    cout << uResponses.DebugString() << endl;
    printVector(acks);
    printMNTimes('?', 2, 40);
}

void WorldSimulatorHandler::sendAcks(vector <uint64_t> &acks) {
    if(!acks.empty()) {
        printLog("sending acks to world simulator");
        printVector("acks", acks);
        UCommands uCommands;
        for (const auto &x: acks) {
            uCommands.add_acks(x);
        }
        clientSocket.sendMesg(uCommands);
    }
}


void WorldSimulatorHandler::sendCommands() {
    while(true){
        printLog("sendCommands()");
        std::unique_lock <std::mutex> munique(mtx, std::defer_lock);
        munique.lock();
        if(!this->commandHashMap.empty()) {
            UCommands uCommands;
            unordered_map < uint64_t, unique_ptr < Message > > ::iterator
            it = this->commandHashMap.begin();
            const Descriptor *descriptor = uCommands.GetDescriptor();
            const Reflection *reflection = uCommands.GetReflection();
            while (it != this->commandHashMap.end()) {
                Message* new_entry = getNewAllocatedMessage((it->second).get());
                const std::string name = it->second->GetDescriptor()->name();
                const FieldDescriptor * fieldDescriptor = descriptor->FindFieldByName(nameInUCommands[name]);
                reflection->AddAllocatedMessage(&uCommands, fieldDescriptor, new_entry);
                ++it;
            }
            //printLog(uCommands.DebugString());
            clientSocket.sendMesg(uCommands);
        }
        munique.unlock();
        sleepForSeconds(0.5);
    }
}

//handle commands

void WorldSimulatorHandler::askAllTruckStatus() {
    printVector("asking?", hasSentTruckQuery);
    for(int id = TRUCK_START_ID; id < TRUCK_START_ID+NUM_OF_TRUCKS; ++id){
        if(hasSentTruckQuery[id-TRUCK_START_ID] == true){
            continue;
        }
        hasSentTruckQuery[id-TRUCK_START_ID] = true;
        UQuery uQuery;
        uQuery.set_truckid(id);
        uQuery.set_seqnum(seqnumCreator.updateSeq());
        this->push(uQuery.seqnum(), uQuery);
    }
}

//void WorldSimulatorHandler::printLog(const string str) {
//    cout << "[World simulator handler] " << str << endl;
//}

pair<int, int64_t> WorldSimulatorHandler::handleUGoPickUp(int warehouseID) {
    //1 get avalible truck
    printLog("------------handleUGoPickUp-------------");
    int truck_id;
    int64_t seq_num;
    while(true){
        sleepForSeconds(2);
        truck_id = upsData->findAvaTruck();
        if(truck_id!=-1){
            break;
        }
    }
    
    //3 Create ws message
    seq_num = seqnumCreator.updateSeq();
    UGoPickup uGoPickup;
    uGoPickup.set_seqnum(seq_num);
    uGoPickup.set_truckid(truck_id);
    uGoPickup.set_whid(warehouseID);
    this->push(seq_num, uGoPickup);
    // update truck status
        
    return make_pair(truck_id, seq_num);
}

void WorldSimulatorHandler::handleUGoDeliver(unordered_map<int64_t,pair<int,int>> packageInfo,int truck_id){
    //1 create message send to world
    printLog("handleUGoDelive");
    int64_t seq_num = seqnumCreator.updateSeq();
    UGoDeliver delivers;
    delivers.set_seqnum(seq_num);
    delivers.set_truckid(truck_id);

    unordered_map<int64_t,pair<int,int>>::iterator it = packageInfo.begin();
    vector<int64_t> packageIDs;
    while(it!=packageInfo.end()){
        UDeliveryLocation * p = delivers.add_packages();
        p->set_packageid(it->first);
        p->set_x(it->second.first);
        p->set_y(it->second.second);
        packageIDs.push_back(it->first);
         //2 change package status to delivering
        upsData->updatePackageStatusID(it->first,"DELIVERING");
        it++;
    }

    upsData->updateTruckStatus(truck_id,"DELIVERING");
    //TODO push delivers to container
    this->push(seq_num,delivers);
   
    //3 Notice Amazon Delivering 
    amazonHandler.lock()->handleU2ADelivering(truck_id,packageIDs);
}

void WorldSimulatorHandler::handleChangeAddress(UDeliveryLocation &location,int truck_id){
    int64_t seq_num = seqnumCreator.updateSeq();
    UGoDeliver delMessage;
    delMessage.set_seqnum(seq_num);
    delMessage.set_truckid(truck_id);
    UDeliveryLocation * p = delMessage.add_packages();
    p->set_packageid(location.packageid());
    p->set_x(location.x());
    p->set_y(location.y());
    this->push(seq_num,delMessage);
}

Message *WorldSimulatorHandler::getNewAllocatedMessage(Message *message) {
    std::string data;
    message->SerializeToString(&data);
    string messageType = message->GetDescriptor()->name();
    Message* res = nullptr ;
    if(messageType == UQUERY_NAME){
        res = new UQuery;
    }else if(messageType == UGODELIVER_NAME){
        res = new UGoDeliver;
    }else if(messageType == UGOPICKUP_NAME){
        res = new UGoPickup;
    }else{
        return nullptr;
    }
    res->ParseFromString(data);
    return res;
}

void WorldSimulatorHandler::handleUFinished(const UFinished &uFinished){
    printLog("handleUFinished");
    // 1 Find warehouse
    int wh_x = uFinished.x();
    int wh_y = uFinished.y();
    int warehouse_id = upsData->findWarehouse(wh_x,wh_y);
    Warehouse warehouse;
    warehouse.set_warehouseid(warehouse_id);
    warehouse.set_x(wh_x);
    warehouse.set_y(wh_y);
    int truck_id = uFinished.truckid();
    upsData->updateTruckStatus(truck_id,"ARRIVE WAREHOUSE");
    //2.find the target package with both packed and packing status
    vector<int64_t> packageIDs = upsData->getTargetPackageIDs(truck_id,warehouse_id,"PACKED","PACKING");
    //3. Send Amazon notice of truck arrive.
    amazonHandler.lock()->handleU2ATruckArrived(truck_id,warehouse,packageIDs);
}

void WorldSimulatorHandler::handleUDeliveryMade(const UDeliveryMade &uDeliveryMade){
    printLog("handleUFinished");
    //1 update package to deliverd
    int64_t package_id = uDeliveryMade.packageid();
    upsData->updatePackageStatusID(package_id,"DELIVERED");
    //2. told amazon 
    amazonHandler.lock()->handleU2ADelivered(package_id);
    //frontEndHandler.lock()->add2Map(package_id);
}

void WorldSimulatorHandler::handleFinished(const bool &finished){
    printLog("handleFinished");
    //Bool finished ?
}

void WorldSimulatorHandler::handleUTruck(const UTruck &uTruck){
    //printLog("handleUTruck");
    //set to false so that server would ask the status of truck again
    hasSentTruckQuery[uTruck.truckid()-TRUCK_START_ID] = false;
    int truck_id = uTruck.truckid();
    string status = uTruck.status();
    upsData->updateTruckStatus(truck_id,status);
}

void WorldSimulatorHandler::handleUErr(const UErr &uErr){
    printLog("handleUErr");
    printLog(uErr.DebugString());
    int64_t ori_seq = uErr.originseqnum();
    //1 check if oriseq in the database
    UCommands uCommands;
    const Descriptor *descriptor = uCommands.GetDescriptor();
    const Reflection *reflection = uCommands.GetReflection();
    std::string name;
    std::lock_guard <std::mutex> lck(mtx);
    if(commandHashMap.count(ori_seq) || seqNumQWaitToDelete.count(ori_seq) || seqNumQToDelete.count(ori_seq)){
        Message* new_entry = getNewAllocatedMessage(seqNumQWaitToDelete[ori_seq].get());
        name = seqNumQWaitToDelete[ori_seq]->GetDescriptor()->name();
        const FieldDescriptor * fieldDescriptor = descriptor->FindFieldByName(nameInUCommands[name]);
        reflection->AddAllocatedMessage(&uCommands, fieldDescriptor, new_entry);
    }else{
        //printLog(uErr.err());
        return;
    }
    //handle uGoPickup
    if(name.compare("UGoPickup")==0){
        printLog("------------In Error handler UGoPickup-----------------");
        printLog(uErr.err());
        UGoPickup pickup = uCommands.pickups(0);
        int whid = pickup.whid();
        pair<int, int64_t> updateInfo = handleUGoPickUp(whid);
        upsData->updatePackageTruck(updateInfo,ori_seq);
    }
    //handle uGoDeliver
    else if(name.compare("UGoDeliver")==0){
        printLog("------------In Error handler UGoDeliver-----------------");
        printLog(uErr.err());
        UGoDeliver deliver = uCommands.deliveries(0);
        int64_t seq_num = seqnumCreator.updateSeq();
        deliver.set_seqnum(seq_num);
        this->push(seq_num,deliver);
    }
    else{
        //printLog(uErr.err());
        return;
    }
}

std::thread WorldSimulatorHandler::run_spawn() {
    return std::thread(&WorldSimulatorHandler::run, this);
}

void WorldSimulatorHandler::handleUFinished_spawn(int id, shared_ptr <WorldSimulatorHandler> worldSimulatorHandler,
                                                  const UFinished &uFinished) {
    worldSimulatorHandler->handleUFinished(uFinished);
}

void WorldSimulatorHandler::handleUDeliveryMade_spawn(int id, shared_ptr <WorldSimulatorHandler> worldSimulatorHandler,
                                                      const UDeliveryMade &uDeliveryMade) {
    worldSimulatorHandler->handleUDeliveryMade(uDeliveryMade);
}

void WorldSimulatorHandler::handleFinished_spawn(int id, shared_ptr <WorldSimulatorHandler> worldSimulatorHandler,
                                                 const bool &finished) {
    worldSimulatorHandler->handleFinished(finished);
}

void WorldSimulatorHandler::handleUTruck_spawn(int id, shared_ptr <WorldSimulatorHandler> worldSimulatorHandler,
                                               const UTruck &uTruck) {
    worldSimulatorHandler->handleUTruck(uTruck);
}

void WorldSimulatorHandler::handleUErr_spawn(int id, shared_ptr <WorldSimulatorHandler> worldSimulatorHandler,
                                             const UErr &uErr) {
    worldSimulatorHandler->handleUErr(uErr);
}
