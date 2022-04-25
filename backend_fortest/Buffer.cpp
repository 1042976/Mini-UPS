//
// Created on 4/13/22.
//

#include "Buffer.h"

uint32_t Buffer::getWholeBufferLength(vector<char> buffer) {
    uint32_t contentSize = getContentLength(buffer);
    return std::to_string(contentSize).length()+contentSize;
}

uint32_t Buffer::getContentLength(vector<char> buffer) {
    google::protobuf::io::ArrayInputStream in(buffer.data(), buffer.size());
    google::protobuf::io::CodedInputStream input(&in);
    uint32_t contentSize;
    if(!input.ReadVarint32(&contentSize)){
        throw MyException("Error: Fail to get the size of the received message!");
    }
    return contentSize;
}
