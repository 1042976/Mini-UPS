#include "ClientSocket.h"

int ClientSocket::getServerFd() {
    return serverFd;
}

vector<char> ClientSocket::getHostName() {
    return hostname;
}

vector<char> ClientSocket::getPort() {
    return port;
}

ClientSocket::ClientSocket(vector<char> _hostname, vector<char> _port) : hostname(_hostname), port(_port) {}

void ClientSocket::setSocket() {
    int status = 0;
    memset(&hints, 0, sizeof(hints));
    string error_message = "Error: Unable to create a client socket!";
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    setZeroInTheEnd(hostname);
    setZeroInTheEnd(port);
    status = getaddrinfo(hostname.data(), port.data(), &hints, &servinfo);
    if (status != 0) {
        throw MyException(error_message);
    }
    serverFd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (serverFd == -1) {
        throw MyException(error_message);
    }
}

void ClientSocket::toConnect() {
    cout << "Connect to " << vectorToStr(hostname) << "::" << vectorToStr(port) << endl;
    int status = 0;
    status = connect(serverFd, servinfo->ai_addr, servinfo->ai_addrlen);
    if (status == -1) {
        throw MyException("Error: Fail to connect to the original server!");
    }else{
        cout << "Successfully connect to server!" << endl;
    }
    freeaddrinfo(servinfo);
}

void ClientSocket::setup() {
    setSocket();
    toConnect();
}

