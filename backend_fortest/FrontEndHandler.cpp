//
// Created by Xiaodong Liu on 4/16/22.
//
#include "FrontEndHandler.h"

vector<char> FrontEndHandler::UPS_PORT_FOR_FRONTEND = strToVector("45678");

FrontEndHandler::FrontEndHandler(shared_ptr <UPSData> _upsData):
                                        BaseHandler(_upsData, "logs/frontend_handler.log", "frontend_handler"),
                                        serverSocket(UPS_PORT_FOR_FRONTEND, BACKLOG){}

FrontEndHandler::FrontEndHandler(shared_ptr<UPSData> _upsData, shared_ptr<WorldSimulatorHandler> _worldSimulatorHandler,
                                 shared_ptr<AmazonHandler> _amazonHandler) :
                                    BaseHandler(_upsData, "logs/frontend_handler.log", "frontend_handler"),
                                    serverSocket(UPS_PORT_FOR_FRONTEND, BACKLOG),
                                     worldSimulatorHandler(_worldSimulatorHandler),
                                    amazonHandler(_amazonHandler){}

void FrontEndHandler::run(){
    cout << "Front end handler is running" << endl;
    serverSocket.setUp();
//    clientFd = serverSocket.toAccept();
//    printLog("already accept!");
    while(true){
        clientFd = serverSocket.toAccept();
        printLog("already accept!");
        while(true) {
            try{
                F2BChangeAddress f2BChangeAddress;
                cout << "client fd: " << clientFd << endl;
                //vector<char> str = serverSocket.toReceive(clientFd);
                serverSocket.recvMesg(clientFd, f2BChangeAddress);
                if(f2BChangeAddress.ByteSizeLong() == 0){
                    printLog("Front End disconnected");
                    break;
                }
                int64_t package_id = f2BChangeAddress.shipid();
                int x = f2BChangeAddress.x();
                int y = f2BChangeAddress.y();
                amazonHandler.lock()->handleU2AChangeAddress(package_id, x, y);
                printLog(f2BChangeAddress.DebugString());
            }catch (MyException &exp){
                cout << exp.what() << endl;
                break;
            }
        }
    }

}

void FrontEndHandler::sendChangeAddResp(B2FChangeAddressResp response){
    printLog("sendChangeAddResp!");
    int64_t seq_num = seqnumCreator.updateSeq();
    response.set_seqnum(seq_num);
    serverSocket.resMesg(clientFd,response);
}

// void FrontEndHandler::add2Map(int64_t package_id){
//     deliveredPackageID.insert(package_id);
// }


std::thread FrontEndHandler::run_spawn() {
    return std::thread(&FrontEndHandler::run, this);
}

void FrontEndHandler::handleNewResOrReq() {

}

void FrontEndHandler::sendCommands() {

}

void FrontEndHandler::sendAcks(vector <uint64_t> &acks) {

}

void FrontEndHandler::generateCommands() {

}

Message* FrontEndHandler::getNewAllocatedMessage(Message* message) {
    return nullptr;
}