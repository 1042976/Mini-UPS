//
// Created on 4/6/22.
//

#include "Common.h"

int BACKLOG = 50;
int THREADPOOLSIZE = 100;
uint32_t FIRSTBUFFELEN = 1024;
uint32_t HEADERLEN = 1;
size_t MAXBUFFERLEN = 1048576;
int TRUCK_START_ID = 1;
int NUM_OF_TRUCKS = 20;
ctpl::thread_pool p(17);

int findChar(const vector<char> &A, char target) {
    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] == target) {
            return i;
        }
    }
    return -1;
}

int findAnyCharInSubStr(const vector<char> &A, vector<char> target) {
    int min_index = INT_MAX;
    for (size_t i = 0; i < target.size(); ++i) {
        int cur = findChar(A, target[i]);
        if (cur == -1) {
            continue;
        }
        min_index = std::min(min_index, cur);
    }
    return min_index == INT_MAX ? -1 : min_index;
}

void setZeroInTheEnd(vector<char> &buffer) {
    int firstZeroIdx = findChar(buffer, '\0');
    if (firstZeroIdx == -1) {
        buffer.emplace_back('\0');
    }
}

vector<char> strToVector(string str) {
    return vector<char>(str.begin(), str.end());
}

string vectorToStr(vector<char> arr) {
    return string(arr.begin(), arr.end());
}

void standardizeVector(vector<char> &buffer) {
    size_t actual_len = 0;
    while (actual_len < buffer.size() && buffer[actual_len] != '\0') {
        ++actual_len;
    }
    buffer.resize(actual_len);
}


string readFile(const char *filename) {
    std::ifstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

string addLenAsHeader(string content) {
    int contentLen = content.length();
    return std::to_string(contentLen) + "\n" + content;
}

string addApostrophe(string str) {
    return "\'" + str + "\'";
}

void sleepForSeconds(double a){
    usleep((int)(a*1000000));
}

void printCommandHashMap(std::unordered_map<uint64_t, std::unique_ptr<Message> >& commandHashMap){
    cout << "Command hash map: ";
    auto it = commandHashMap.begin();
    while(it != commandHashMap.end()){
        cout << it->first << " ";
        ++it;
    }
    cout << endl;
}