//
// Created by Xiaodong Liu on 4/16/22.
//

#ifndef FINALPROJECT_WORLDSIMULATORHANDLER_H
#define FINALPROJECT_WORLDSIMULATORHANDLER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <stdint.h>
#include "UPSData.h"
#include "ClientSocket.h"
#include "SeqnumCreator.h"
#include "BaseHandler.h"
#include "AmazonHandler.h"
#include "FrontEndHandler.h"
#include "MyTimer.h"
#include "Truck.h"
#include "Common.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"

using namespace std;
using namespace google::protobuf;

class AmazonHandler;
class FrontEndHandler;

class WorldSimulatorHandler: public BaseHandler, public std::enable_shared_from_this<WorldSimulatorHandler>{
private:
    int64_t worldID;
    ClientSocket clientSocket;
//    SeqnumCreator seqnumCreator;
//    MyTimer myTimer;
    vector<bool> hasSentTruckQuery;
//    unordered_map<uint64_t, unique_ptr<Message> > commandHashMap; //seqnum, message
//    vector<uint64_t> seqNumQToDelete; //seqnum
//    vector<uint64_t> seqNumQWaitToDelete; //seqnum
//    shared_ptr<UPSData> upsData;
    //send
//    template<class T>
//    void push(int64_t seqnum, const T& message);

    //handle commands:
    void handleUFinished(const UFinished &uFinished);
    void handleUDeliveryMade(const UDeliveryMade &uDeliveryMade);
    void handleFinished(const bool &finished);
    void handleUTruck(const UTruck &uTruck);
    void handleUErr(const UErr &uErr);


public:
//    std::mutex mtxW;
    static vector<char> WORLDSIMULATOR_HOST;
    static vector<char> WORLDSIMULATOR_PORT;
    //all your command names
    static const string UGOPICKUP_NAME;
    static const string UGODELIVER_NAME;
    static const string UQUERY_NAME;

    static unordered_map<string, string> nameInUCommands;
    weak_ptr<AmazonHandler> amazonHandler;
    weak_ptr<FrontEndHandler> frontEndHandler;
    WorldSimulatorHandler(shared_ptr<UPSData> _upsData);
    WorldSimulatorHandler(shared_ptr<UPSData> _upsData, shared_ptr<AmazonHandler> _amazonHandler, shared_ptr<FrontEndHandler> _frontEndHandler);
    void connectToWorldSimulator();
    int64_t getWorldID();
    void run() override;
//    //generate commands to be sent once in a while
    void generateCommands() override;
//
//    //handle response in a loop
    void handleNewResOrReq() override;
//
    //handle commands from amazon
    void handleCommands(const UResponses &uResponses);
//
    void sendAcks(vector<uint64_t>& acks) override;

//    //delete seqnums of those commands that are successfully sent every once in a while
//    void deleteSeqNums() override;
//
//    //send commands every once in a while
    void sendCommands() override;

    //to get data every once in a while
    void askAllTruckStatus();

////    //print log

//    //for thread
    std::thread run_spawn() override;

    //command
    pair<int, int64_t> handleUGoPickUp(int warehouseID);
    void handleUGoDeliver(unordered_map<int64_t,pair<int,int>> packageInfo,int truck_id);
    void handleChangeAddress(UDeliveryLocation &location,int truck_id);
    //deal with message
    Message* getNewAllocatedMessage(Message* message) override;

    static void handleUFinished_spawn(int id, shared_ptr<WorldSimulatorHandler> worldSimulatorHandler, const UFinished &uFinished);
    static void handleUDeliveryMade_spawn(int id, shared_ptr<WorldSimulatorHandler> worldSimulatorHandler, const UDeliveryMade &uDeliveryMade);
    static void handleFinished_spawn(int id, shared_ptr<WorldSimulatorHandler> worldSimulatorHandler, const bool &finished);
    static void handleUTruck_spawn(int id, shared_ptr<WorldSimulatorHandler> worldSimulatorHandler, const UTruck &uTruck);
    static void handleUErr_spawn(int id, shared_ptr<WorldSimulatorHandler> worldSimulatorHandler, const UErr &uErr);



};



//template<typename T>
//void WorldSimulatorHandler::push(int64_t seqnum, const T &message) {
//    unique_ptr<Message> m_ptr = make_unique<T>(message);
//    std::lock_guard <std::mutex> lck(mtxW);
//    commandHashMap[seqnum] = std::move(m_ptr);
//}

#endif //FINALPROJECT_WORLDSIMULATORHANDLER_H
