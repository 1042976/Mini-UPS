//
// Created by Xiaodong Liu on 4/16/22.
//

#ifndef FINALPROJECT_FRONTENDHANDLER_H
#define FINALPROJECT_FRONTENDHANDLER_H
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
#include <unordered_set>
#include "UPSData.h"
#include "WorldSimulatorHandler.h"
#include "AmazonHandler.h"
#include "BaseHandler.h"
#include "ServerSocket.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
#include "frontend.pb.h"

using namespace std;
using namespace google::protobuf;

class AmazonHandler;
class WorldSimulatorHandler;

class FrontEndHandler:public BaseHandler, public std::enable_shared_from_this<FrontEndHandler>{
private:
    int clientFd; //only one amazon client would be accepted
    ServerSocket serverSocket;
    unordered_set<int64_t> deliveredPackageID;
public:
    std::mutex mtxF;
    static vector<char> UPS_PORT_FOR_FRONTEND;
    weak_ptr<WorldSimulatorHandler> worldSimulatorHandler;
    weak_ptr<AmazonHandler> amazonHandler;
    FrontEndHandler(shared_ptr<UPSData> _upsData);
    FrontEndHandler(shared_ptr<UPSData> _upsData, shared_ptr<WorldSimulatorHandler> _worldSimulatorHandler, shared_ptr<AmazonHandler> _amazonHandler);
    void run();

    //for thread
    std::thread run_spawn();

    //receive commands in a loop
    void handleNewResOrReq() override;

   void sendAcks(vector<uint64_t>& acks) override;
    //delete seqnums of those commands that are successfully sent every once in a while
//    void deleteSeqNums() override;

    //send commands every once in a while
    void sendCommands() override;
    void sendChangeAddResp(B2FChangeAddressResp response);
    //void add2Map(int64_t package_id);
    void generateCommands() override;

    Message* getNewAllocatedMessage(Message* message) override;
};

#endif //FINALPROJECT_FRONTENDHANDLER_H
