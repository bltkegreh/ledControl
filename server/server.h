#pragma once
#include <string>

class Server
{
public:

    Server(const std::string& serverFifoName, const std::string& clientFifoName);
    ~Server();

    bool init();

    bool readData(std::string& outReadData);
    bool writeData(std::string& pid, std::string& writeData);

private:
    const std::string m_serverFifoName;
    const std::string m_clientFifoBaseName;
};