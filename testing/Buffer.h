#ifndef FINALPROJECT_BUFFER_H
#define FINALPROJECT_BUFFER_H

#include <string>
#include <utility>
#include "Common.h"
#include "MyException.h"
class Buffer {
public:

    static uint32_t getWholeBufferLength(vector<char> buffer);
    static uint32_t getContentLength(vector<char> buffer);
};

#endif //FINALPROJECT_BUFFER_H
