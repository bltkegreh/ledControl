#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream> 
#include "server.h"

using namespace std;
Server::Server(const string& serverFifoName, const string& clientFifoName) : m_serverFifoName(serverFifoName), m_clientFifoBaseName(clientFifoName)
{
}

Server::~Server()
{
    unlink(m_serverFifoName.c_str());
}

bool Server::init()
{
    unlink(m_serverFifoName.c_str());
    umask(0);

    if(mkfifo(m_serverFifoName.c_str(), 0777)  < 0){
        cout << "mkfifo fail while creating " << m_serverFifoName << " error is " << errno << endl;
        return false;
    }
    return true;
}

bool Server::readData(string& outReadData)
{
    ifstream file(m_serverFifoName);

    if(file)
    {
        string line;
        getline(file, outReadData);
        return true;
    }
    cout << "Error while opening server fifo. Error is " << errno << endl;
    return false;
}

bool Server::writeData(string& pid, string& data)
{
    string clientFifo = m_clientFifoBaseName + pid;
    ofstream file(clientFifo);

    if(file)
    {
        file << data << endl;
        return true;
    }
    cout << "Error while opening client fifo file. Error is " << errno << endl;
    return false;
}
