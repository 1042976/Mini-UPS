//
// Created on 4/21/22.
//

#include "BaseHandler.h"

BaseHandler::BaseHandler(shared_ptr <UPSData> _upsData, const char* _logs, string _handler_name):seqnumCreator(), myTimer(), upsData(_upsData), logs(_logs),
        handler_name(_handler_name){}

void BaseHandler::deleteSeqNums() {
    while(true){
        sleepForSeconds(10);
        printLog("deleteSeqNums()");
        if(!this->seqNumQToDelete.empty()){
            sleepForSeconds(20);
            seqNumQToDelete.clear();
        }
        printLog("++++++++++++++++++++++++++++++++++");
        printCommandHashMap(commandHashMap);
        // printVector("seqNumQToDelete", seqNumQToDelete);
        // printVector("seqNumQWaitToDelete", seqNumQWaitToDelete);
        printLog("----------------------------------");
        if(!this->seqNumQWaitToDelete.empty()){
            std::lock_guard <std::mutex> lck(mtx);
            seqNumQToDelete.swap(seqNumQWaitToDelete);
        }
    }
}

void BaseHandler::printLog(const string str)  {
    cout << "[" << handler_name << "]" << str << endl;
    logs << "[" << handler_name << "]" << str << endl;
}