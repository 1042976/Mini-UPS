#include "AmazonServer.h"

vector<char> AmazonServer::WORLDSIMULATOR_HOST = strToVector("localhost");
vector<char> AmazonServer::WORLDSIMULATOR_PORT = strToVector("23456");
vector<char> AmazonServer::UPS_HOST = strToVector("vcm-25919.vm.duke.edu");
vector<char> AmazonServer::UPS_PORT = strToVector("56789");
vector<char> AmazonServer::AMAZON_PORT_FOR_UPS = strToVector("34567");

AmazonServer::AmazonServer():seqnumCreator(), clientSocketForWorld(WORLDSIMULATOR_HOST, WORLDSIMULATOR_PORT),
                             clientSocketForUPS(UPS_HOST, UPS_PORT){}

void AmazonServer::run() {
    cout << "Amazon server running" << endl;
    clientSocketForUPS.setup();
    clientSocketForWorld.setup();
    //receive world id from ups
    connectToWorld();

    //ask for trucks
    askTruck();
    usleep(3000000);
    packed();

    unsigned int microsecond = 1000000;
    while(true){
        cout << "server running" << endl;
        usleep(2*microsecond);
    }
}
void AmazonServer::packed(){
    cout<<"AmazonServer::packed()"<<endl;
    AmazonCommands amazonCommands;
    
    for(int i=1;i<21;i++){
        A2UPacked* packed = amazonCommands.add_packed();
        packed->set_shipid(i);
        packed->set_seqnum(seqnumCreator.updateSeq());
    }
    
    cout << "clientSocketForUPS.sendMesg(packedMessage);" << endl;
    clientSocketForUPS.sendMesg(amazonCommands);
}
void AmazonServer::askTruck() {
    cout << "void AmazonServer::askTruck()" << endl;
    //init mesg
    AmazonCommands amazonCommands;
    A2UAskTruck* a2UAskTruck = amazonCommands.add_gettruck();
    a2UAskTruck->set_seqnum(seqnumCreator.updateSeq());
//    Warehouse wh;
//    wh.set_warehouseid(1);
//    wh.set_x(0);
//    wh.set_y(1);
//    a2UAskTruck->set_allocated_warehouse(&wh);
    a2UAskTruck->mutable_warehouse()->set_warehouseid(1);
    a2UAskTruck->mutable_warehouse()->set_x(0);
    a2UAskTruck->mutable_warehouse()->set_y(1);
    
    for(int i=1;i<21;i++){
        PackageInfo* packageInfo = a2UAskTruck->add_package();
        packageInfo->set_shipid(i);
        packageInfo->set_x(i);
        packageInfo->set_y(i+1);
        Product* product = packageInfo->add_product();
        product->set_name("banana");
        product->set_description("delicious banana");
        product->set_count(10);
    }
    
    //send msg
    cout << "clientSocketForUPS.sendMesg(amazonCommands);" << endl;
    clientSocketForUPS.sendMesg(amazonCommands);

    //recv ack from ups
    UPSCommands upsCommands;
    clientSocketForUPS.recvMesg(upsCommands);
    if(upsCommands.ByteSizeLong() == 0){
        return;
    }

    if(upsCommands.acks_size() != 0 && upsCommands.acks(0) == amazonCommands.gettruck(0).seqnum()){
        cout << "UPS is dealing with the A2UAskTruck request" << endl;
    }
}

void AmazonServer::connectToWorld() {
    //recv from ups
    U2AConnect u2AConnect;
    clientSocketForUPS.recvMesg(u2AConnect);

    //connect
    uint64_t  targetID = u2AConnect.worldid();
    A2UConnected a2UConnected;
    a2UConnected.set_worldid(targetID);
    if(initWarehouse(targetID)){
        a2UConnected.set_result("connected!");
    }else{

    }
    clientSocketForUPS.sendMesg(a2UConnected);
}

bool AmazonServer::initWarehouse(uint64_t targetID) {
    //msg to send
    AConnect aConnect;
    aConnect.set_worldid(targetID);
    aConnect.set_isamazon(true);
    AInitWarehouse* aInitWarehouse = aConnect.add_initwh();
    aInitWarehouse->set_id(1);
    aInitWarehouse->set_x(0);
    aInitWarehouse->set_y(1);
    aInitWarehouse = aConnect.add_initwh();
    aInitWarehouse->set_id(2);
    aInitWarehouse->set_x(1);
    aInitWarehouse->set_y(2);

    //connect to world
    AConnected aConnected;
    //connect to world simulator
    try {
        while(aConnected.result() != "connected!"){
            clientSocketForWorld.sendMesg(aConnect);
            cout << aConnect.DebugString() << endl;
            clientSocketForWorld.recvMesg(aConnected);
            cout << "connected message" << endl;
            cout << aConnected.DebugString()<< endl;
        }
    }catch (MyException &exp) {
        cerr << exp.what() << endl;
        return false;
    }
    this->worldID = aConnected.worldid();
    return true;
}

int main(int argc, char *argv[]) {
    if(argc < 3){
        cerr << "Usage: ./run.sh <world_simulator_host> <ups_host>" << endl;
        return EXIT_FAILURE;
    }
    AmazonServer::WORLDSIMULATOR_HOST = strToVector(argv[1]);
    AmazonServer::UPS_HOST = strToVector(argv[2]);
    try{
        AmazonServer amazonServer;
        amazonServer.run();
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}