//
// Created by Xiaodong Liu on 4/16/22.
//

#ifndef FINALPROJECT_AMAZONHANDLER_H
#define FINALPROJECT_AMAZONHANDLER_H
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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdint.h>
#include "UPSData.h"
#include "WorldSimulatorHandler.h"
#include "FrontEndHandler.h"
#include "ClientSocket.h"
#include "ServerSocket.h"
#include "Common.h"
#include "MyTimer.h"
#include "ctpl_stl.h"
#include "SeqnumCreator.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
#include "frontend.pb.h"
using namespace std;
using namespace google::protobuf;

class FrontEndHandler;
class WorldSimulatorHandler;

class AmazonHandler: public BaseHandler, public std::enable_shared_from_this<AmazonHandler>{
private:
    int clientFd; //only one amazon client would be accepted
    ServerSocket serverSocket;

    vector<uint64_t> getAllSeqnums(const AmazonCommands &amazonCommands);


    void sendAcks(vector<uint64_t>& acks);

    //handle commands:
    void handleA2UAskTruck(const A2UAskTruck &a2UAskTruck);
    void handleA2UPacked(const A2UPacked &a2UPacked);
    void handleA2ULoading(const A2ULoading &a2ULoading);
    void handleA2ULoaded(const A2ULoaded &a2ULoaded);
    void handleA2UQueryShip(const A2UQueryShip &a2UQueryShip);
    void handleFinish(const bool &finish);
    void handleA2UError(const Error &error);
    

    //handle commands


    //for hashmap

public:
//    std::mutex mtxA;
    static vector<char> AMAZON_HOST;
    static vector<char> AMAZON_PORT;
    static vector<char> UPS_PORT_FOR_AMAZON;
    //all your command names
    static const string U2ATRUCKARRIVED_NAME;
    static const string U2ADELIVERING_NAME;
    static const string U2ADELIVERED_NAME;
    static const string U2ASHIPSTATUS_NAME;
    static const string U2ACHANGEADDRESS_NAME;
    static const string ERROR_NAME;

    static unordered_map<string, string> nameInUPSCommands;

    weak_ptr <WorldSimulatorHandler> worldSimulatorHandler;
    weak_ptr <FrontEndHandler> frontEndHandler;

    AmazonHandler(shared_ptr <UPSData> _upsData);
    AmazonHandler(shared_ptr <UPSData> _upsData, shared_ptr <WorldSimulatorHandler> _worldSimulatorHandler, shared_ptr<FrontEndHandler> _frontEndHandler);
    void run() override;

    //receive commands in a loop
    void handleNewResOrReq() override;

    //delete seqnums of those commands that are successfully sent every once in a while
//    void deleteSeqNums() override;

    //send commands every once in a while
    void sendCommands() override;

    //inform amazon the world id;
    void sendWorldID();

    //handle commands from amazon
    void handleCommands(const AmazonCommands &amazonCommands);

    void generateCommands() override;

    Message* getNewAllocatedMessage(Message* message) override;

    //FOR SEND MESSAGE
    void handleU2ATruckArrived(int truckID,Warehouse warehouse,vector<int64_t> packageIDs);
    void handleU2ADelivering(int truckId,vector<int64_t> packageIDs);
    void handleU2ADelivered(int64_t package_id);
    void handleU2AShipStatus(int64_t package_id,string status);
    void handleU2AChangeAddress(int64_t package_id,int x,int y);
    void handelError(int64_t ori_num, string mess);

    //for thread
    std::thread run_spawn() override;

    static void handleA2UAskTruck_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const A2UAskTruck &a2UAskTruck);
    static void handleA2UPacked_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const A2UPacked &a2UPacked);
    static void handleA2ULoading_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const A2ULoading &a2ULoading);
    static void handleA2ULoaded_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const A2ULoaded &a2ULoaded);
    static void handleA2UQueryShip_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const A2UQueryShip &a2UQueryShip);
    static void handleFinish_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const bool &finish);
    static void handleA2UError_spawn(int id, shared_ptr<AmazonHandler> amazonHandler, const Error &error);
};
#endif //FINALPROJECT_AMAZONHANDLER_H
