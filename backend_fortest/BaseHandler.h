//
// Created on 4/21/22.
//

#ifndef FINALPROJECT_BASEHANDLER_H
#define FINALPROJECT_BASEHANDLER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <stdint.h>
#include "UPSData.h"
#include "ClientSocket.h"
#include "SeqnumCreator.h"
#include "MyTimer.h"
#include "Truck.h"
#include "Common.h"
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
using namespace std;
using namespace google::protobuf;
class BaseHandler{
protected:
    SeqnumCreator seqnumCreator;
    MyTimer myTimer;
    unordered_map<uint64_t, unique_ptr<Message>> commandHashMap; //seqnum, message
    unordered_map<uint64_t, unique_ptr<Message>> seqNumQToDelete; //seqnum
    unordered_map<uint64_t, unique_ptr<Message>> seqNumQWaitToDelete; //seqnum
    shared_ptr<UPSData> upsData;
    //send
    template<class T>
    void push(int64_t seqnum, const T& message);
public:
    std::mutex mtx;
    std::ofstream logs;
    std::string handler_name;
    BaseHandler(shared_ptr<UPSData> _upsData, const char* _logs, string _handler_name);
    virtual void run() = 0;
    //generate commands to be sent once in a while
    virtual void generateCommands() = 0;

    //handle response in a loop
    virtual void handleNewResOrReq() = 0;

    virtual void sendAcks(vector<uint64_t>& acks) = 0;

    //delete seqnums of those commands that are successfully sent every once in a while
    void deleteSeqNums();

    void printLog(const string str);

    //send commands every once in a while
    virtual void sendCommands() = 0;


    //for thread
    virtual std::thread run_spawn() = 0;

    //deal with message
    virtual Message* getNewAllocatedMessage(Message* message) = 0;

    virtual ~BaseHandler(){
        logs.close();
    }
};

template<typename T>
void BaseHandler::push(int64_t seqnum, const T &message) {
    unique_ptr<Message> m_ptr = make_unique<T>(message);
    std::lock_guard <std::mutex> lck(mtx);
    commandHashMap[seqnum] = std::move(m_ptr);
}
#endif //FINALPROJECT_BASEHANDLER_H
