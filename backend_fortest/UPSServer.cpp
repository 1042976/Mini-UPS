//
// Created by Xiaodong Liu on 4/8/22.
//

#include "UPSServer.h"

UPSServer::UPSServer():upsData(make_shared<UPSData>()),
    worldSimulatorHandler(make_shared<WorldSimulatorHandler>(upsData)),
    amazonHandler(make_shared<AmazonHandler>(upsData)),
    frontEndHandler(make_shared<FrontEndHandler>(upsData)){
    worldSimulatorHandler->amazonHandler = amazonHandler;
    worldSimulatorHandler->frontEndHandler = frontEndHandler;
    amazonHandler->frontEndHandler = frontEndHandler;
    amazonHandler->worldSimulatorHandler = worldSimulatorHandler;
    frontEndHandler->amazonHandler = amazonHandler;
    frontEndHandler->worldSimulatorHandler = worldSimulatorHandler;
}

void UPSServer::run() {
    //set up database
//    upsData->createTables();
//    upsData->cleanAllData();
    //connect to the world simulator first
    worldSimulatorHandler->connectToWorldSimulator();

    thread thW = worldSimulatorHandler->run_spawn();
    thW.detach();
    thread thA = amazonHandler->run_spawn();
    thA.detach();
    thread thF = frontEndHandler->run_spawn();
    thF.detach();

    unsigned int microsecond = 1000000;
    while(true){
        cout << "server running" << endl;
        usleep(60*microsecond);
    }
//    thW.join();
}

int main(int argc, char *argv[]) {
    if(argc < 3){
        cerr << "Usage: ./run.sh <world_simulator_host> <amazon_host>" << endl;
        return EXIT_FAILURE;
    }
    WorldSimulatorHandler::WORLDSIMULATOR_HOST = strToVector(argv[1]);
    AmazonHandler::AMAZON_HOST = strToVector(argv[2]);
    srand((int)time(0));
    try{
        UPSServer upsServer;
        upsServer.run();
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

