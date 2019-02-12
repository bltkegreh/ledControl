#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#include "server.h"

using namespace std;
Server::Server(const std::string& serverFifoName, const std::string& clientFifoName):m_serverFifoName(serverFifoName), m_clientFifoBaseName(clientFifoName)
{
}

Server::~Server()
{
    if(serverFd != -1)
    {
        close(serverFd);
        unlink(m_serverFifoName.c_str());
    }
}

bool Server::init()
{
    unlink(m_serverFifoName.c_str());
    umask(0);

    if(mkfifo(m_serverFifoName.c_str(), 0777)  < 0){
        cout << "mkfifo fail while creating " << m_serverFifoName << " error is " << errno;
        return false;
    }
    if((serverFd = open(m_serverFifoName.c_str(), O_RDONLY)) < 0){
        cout << "mkfifo fail while opening " << m_serverFifoName << " error is " << errno;
        return false;
    }

    return true;
}

void Server::readData(std::string& outReadData)
{
    char line[BUFSIZ] = {'\0'};                                                 
    int read_res = 0;
    do  
    {
        read_res = read(serverFd, line, BUFSIZ);
        if (read_res > 0) {
            outReadData += std::string(line);
        }
       
    }while(read_res > 0);
}

bool Server::writeData(std::string& pid, std::string& data)
{
    std::string clientFifo = m_clientFifoBaseName + pid;
    if((clientFd = open(clientFifo.c_str(), O_WRONLY)) < 0){
        cout << "Error while opening client fifo file " << clientFifo;
        return false;
    }
    if(clientFd != -1) {
        std::string sendDdata = data + '\n';
        write(clientFd, sendDdata.c_str(), sendDdata.size());
        close(clientFd);
    }

    return true;
}
