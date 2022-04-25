#ifndef FINALPROJECT_AMAZONSERVER_H
#define FINALPROJECT_AMAZONSERVER_H
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <chrono>
#include <stdint.h>
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Common.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
#include "MyException.h"
#include "SeqnumCreator.h"
using namespace std;
using namespace google::protobuf::io;
using namespace google::protobuf;
class AmazonServer{
private:
    int64_t worldID;
    SeqnumCreator seqnumCreator;
    ClientSocket clientSocketForWorld;
    ClientSocket clientSocketForUPS;
public:
    static vector<char> WORLDSIMULATOR_HOST;
    static vector<char> WORLDSIMULATOR_PORT;
    static vector<char> UPS_HOST;
    static vector<char> UPS_PORT;
    static vector<char> AMAZON_PORT_FOR_UPS;
    AmazonServer();
    void run();

    //to world
    bool initWarehouse(uint64_t targetID);
    void connectToWorld();

    //to ups
    void askTruck();
    void packed();
};

#endif //FINALPROJECT_AMAZONSERVER_H
