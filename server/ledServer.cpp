#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream> 
#include <regex>

#include "proxy.h"
#include "server.h"
#include "ledServer.h"
using namespace std;

volatile std::sig_atomic_t LedServer::m_terminateFlag = 0;

const std::string LedServer::m_serverFifo     = "/tmp/server";
const std::string LedServer::m_clientFifoBase = "/tmp/client";
const std::string LedServer::m_commandRegexp = "(\\d+)\\s+(.*)";

LedServer::LedServer() : m_server(m_serverFifo, m_clientFifoBase), m_proxy(make_unique<Led>())
{
}

void LedServer::signalHandler(__attribute__((unused)) int signo)
{
    m_terminateFlag = 1;
}

bool LedServer::init()
{
    struct sigaction s;

    s.sa_handler = signalHandler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGHUP, &s, NULL);

    m_isInit = m_server.init();
    return m_isInit;
}

void LedServer::run()
{
    if(!m_isInit)
    {
        std::cout << "LedServer is not inited" << endl;
        return;
    }

    std::regex commandExpression(m_commandRegexp);

    while(!m_terminateFlag)
    {
        string readStr;
        m_server.readData(readStr);
        if (!readStr.empty()) {
            smatch match;
            if(regex_search(readStr, match, commandExpression)) {
                string pid = match[1];
                string command = match[2];

                cout << "PID is " << pid << " command is " << command << endl;
                string answer = m_proxy.processRequest(command);
                cout << "Answer is " << answer << endl;

                m_server.writeData(pid, answer);
            }
            else
            {
                cout << "bad request " << readStr << endl;
            }
        }
    }
}
