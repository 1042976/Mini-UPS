//
// Created on 4/6/22.
//

#ifndef FINALPROJECT_CLIENTSOCKET_H
#define FINALPROJECT_CLIENTSOCKET_H

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <memory>
#include <utility>
#include <vector>
#include "world_ups.pb.h"
#include "MyException.h"
#include "Common.h"
#include "Buffer.h"
using namespace std;

class ClientSocket {
private:
    int serverFd;
    struct addrinfo hints, *servinfo;
    std::vector<char> hostname, port;

public:
    ClientSocket(vector<char> _hostname, vector<char> _port);
    int getServerFd();

    vector<char> getHostName();

    vector<char> getPort();

    void setSocket();

    void toConnect();

    void setup();

    template<typename T>
    void sendMesg(const T& message);

    template<typename T>
    void recvMesg(T& message);
};

template<typename T>
void ClientSocket::sendMesg(const T &message) {
    //extra scope: make output go away before out->Flush()
    // We create a new coded stream for each message.
    // Don’t worry, this is fast.

    //get size of message
    const size_t contentSize = message.ByteSizeLong();
    const size_t headSize = to_string(contentSize).length();
    const size_t totalSize = headSize+contentSize;
    vector<char> buffer(totalSize);
    google::protobuf::io::ArrayOutputStream out(buffer.data(), totalSize);
    google::protobuf::io::CodedOutputStream output(&out);
    //Write the size
    output.WriteVarint32(contentSize);
    message.SerializeToCodedStream(&output);
    int status = send(serverFd, buffer.data(), buffer.size(), 0);
    if(status == -1){
        throw MyException("Error: Fail to send request content to the original server!");
    }
}
template<typename T>
void ClientSocket::recvMesg(T &message) {
    ssize_t curLen = 0;
    vector<char> buffer(FIRSTBUFFELEN);
    curLen = recv(serverFd, buffer.data(), buffer.size(), 0);
    if (curLen < 0) {
        throw MyException("Error: Fail to receive response from the original server!");
    }else if(curLen == 0){
        return;
    }
    //get the actual size of the buffer
    uint32_t contentSize = Buffer::getContentLength(buffer);
    uint32_t totalSize = HEADERLEN+contentSize;

    buffer.resize(totalSize);
    while(curLen < totalSize){
        int restLen = totalSize-curLen;
        int tmpLen = recv(serverFd, &(buffer.data()[curLen]), restLen, 0);
        cout << tmpLen << endl;
        if(tmpLen < 0){
            throw MyException("Error: Fail to receive response from the server!");
        }
        curLen += tmpLen;
    }
    google::protobuf::io::ArrayInputStream in(buffer.data(), buffer.size());
    google::protobuf::io::CodedInputStream input(&in);
    uint32_t size;
    if (!input.ReadVarint32(&size)) {
        throw MyException("Error: Fail to get the size of the received message!");
    }
    // Tell the stream not to read beyond that size.
    google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);
    // Parse the message.
//    if (!message.MergeFromCodedStream(&input)) {
//        throw MyException("Error: Fail to parse the message!");
//    }
//    if (!input.ConsumedEntireMessage()){
//        throw MyException("Error: Fail to parse the message!");
//    }
    message.ParseFromCodedStream(&input);
    // Release the limit.
    input.PopLimit(limit);
}
#endif //FINALPROJECT_CLIENTSOCKET_H
