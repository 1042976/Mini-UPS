//
// Created on 4/9/22.
//

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "ClientSocket.h"
#include "Common.h"
#include "world_ups.pb.h"

using namespace std;
using namespace google::protobuf::io;
using namespace google::protobuf;

//this is adpated from code that a Google engineer posted online
template<typename T>
bool sendMesgTo(const T& message, google::protobuf::io::FileOutputStream *out){
    //extra scope: make output go away before out->Flush()
    // We create a new coded stream for each message.
    // Don’t worry, this is fast.
    google::protobuf::io::CodedOutputStream output(out);
    //Write the size
    const int size = message.ByteSizeLong();
    cout << size << endl;
    output.WriteVarint32(size);
    uint8_t* buffer = output.GetDirectBufferForNBytesAndAdvance(size);
    if(buffer != NULL){
        // Optimization: The message fits in one buffer,so use the faster
        // direct-to-array serialization path.
        message.SerializeWithCachedSizesToArray(buffer);
    }else{
        // Slightly-slower path when the message is multiple buffers.
        message.SerializeWithCachedSizes(&output);
        if(output.HadError()){
            return false;
        }
    }
    out->Flush();
    return true;
}

//this is adpated from code that a Google engineer posted online template<typename T>
template<typename T>
bool recvMesgFrom(T& message, google::protobuf::io::FileInputStream *in){
    google::protobuf::io::CodedInputStream input(in);
    uint32_t size;
    if(!input.ReadVarint32(&size)){
        return false;
    }
    // Tell the stream not to read beyond that size.
    google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);
    // Parse the message.
    if(!message.MergeFromCodedStream(&input)){
        return false;
    }
    if(!input.ConsumedEntireMessage()){
        return false;
    }
    // Release the limit.
    input.PopLimit(limit);
    return true;
}


int main(int argc, char *argv[]) {
    cout << "hello world!" << endl;
    UInitTruck uInitTruck;
    uInitTruck.set_id(1);
    uInitTruck.set_x(2);
    uInitTruck.set_y(5);
    if(uInitTruck.IsInitialized()){
        cout << "The truck has already initialized." << endl;
        string str = uInitTruck.DebugString();
        cout << str;
    }
//    int fd = open("myfile.txt", O_CREAT | O_WRONLY);
//    FileOutputStream* file_output = new FileOutputStream(fd);
//    sendMesgTo<UInitTruck>(uInitTruck, file_output);
    string hostname = "vcm-25919.vm.duke.edu";
    string port = "12345";

    ClientSocket clientSocket(strToVector(hostname), strToVector(port));
    string msg;
    if(uInitTruck.SerializeToString(&msg)){
        cout << "serialize to string!" << endl;
    }
    google::protobuf::io::FileOutputStream *out;
    bool isParsed = sendMesgTo(uInitTruck, out);
    return EXIT_SUCCESS;
}
