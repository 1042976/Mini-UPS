//
// Created on 4/8/22.
//

#ifndef FINALPROJECT_UPSSERVER_H
#define FINALPROJECT_UPSSERVER_H
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include "UPSData.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Common.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
#include "WorldSimulatorHandler.h"
#include "AmazonHandler.h"
#include "FrontEndHandler.h"
#include "SeqnumCreator.h"
#include "ctpl_stl.h"
using namespace std;
using namespace google::protobuf::io;
using namespace google::protobuf;
class UPSServer{
private:
    shared_ptr<UPSData> upsData;
    shared_ptr<WorldSimulatorHandler> worldSimulatorHandler;
    shared_ptr<AmazonHandler> amazonHandler;
    shared_ptr<FrontEndHandler> frontEndHandler;

public:
    UPSServer();
    void run();
};

#endif //FINALPROJECT_UPSSERVER_H
