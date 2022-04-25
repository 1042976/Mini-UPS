#ifndef FINALPROJECT_COMMON_H
#define FINALPROJECT_COMMON_H
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include "world_amazon.pb.h"
#include "ups_amazon.pb.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

extern int BACKLOG;
extern int THREADPOOLSIZE;
extern uint32_t FIRSTBUFFELEN;
extern uint32_t HEADERLEN;
extern size_t MAXBUFFERLEN;

int findChar(const vector<char> &A, char target);

void setZeroInTheEnd(vector<char> &buffer);

vector<char> strToVector(string str);

string vectorToStr(vector<char> arr);

void standardizeVector(vector<char> &buffer);

void printVector(vector<char> arr);

string readFile(const char *filename);

string addLenAsHeader(string content);

int findAnyCharInSubStr(const vector<char> &A, vector<char> target);

#endif //FINALPROJECT_COMMON_H
