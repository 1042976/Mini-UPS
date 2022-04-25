//
// Created by Xiaodong Liu on 4/6/22.
//

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
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <memory>
#include <unordered_map>
#include "world_ups.pb.h"
#include "ups_amazon.pb.h"
#include "ctpl_stl.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;

using namespace google::protobuf;
extern int BACKLOG;
extern int THREADPOOLSIZE;
extern uint32_t FIRSTBUFFELEN;
extern uint32_t HEADERLEN;
extern size_t MAXBUFFERLEN;
extern int TRUCK_START_ID;
extern int NUM_OF_TRUCKS;
extern ctpl::thread_pool p;


int findChar(const vector<char> &A, char target);

void setZeroInTheEnd(vector<char> &buffer);

vector<char> strToVector(string str);

string vectorToStr(vector<char> arr);

void standardizeVector(vector<char> &buffer);

string readFile(const char *filename);

string addLenAsHeader(string content);

int findAnyCharInSubStr(const vector<char> &A, vector<char> target);

string addApostrophe(string str);

void sleepForSeconds(double a);


//print
void printCommandHashMap(std::unordered_map<uint64_t, std::unique_ptr<Message> >& commandHashMap);

template<typename T>
void printVector(vector<T> arr){
    if(arr.empty()){
        cout << endl;
        return;
    }
    size_t i = 0;
    while(i < arr.size()-1){
        cout << arr[i++] << " ";
    }
    cout << arr.back() << endl;
}

template<typename S, typename T>
void printVector(S title, vector<T> arr){
    cout << title << ": ";
    if(arr.empty()){
        cout << endl;
        return;
    }
    size_t i = 0;
    while(i < arr.size()-1){
        cout << arr[i++] << " ";
    }
    cout << arr.back() << endl;
}

//for debug
template<typename T>
void printMNTimes(T t, size_t m, size_t n){
    for(size_t i = 0; i < m; ++i){
        for(size_t j = 0; j < n; ++j){
            cout << t << " ";
        }
        cout << endl;
    }
}
#endif //FINALPROJECT_COMMON_H
