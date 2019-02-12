#pragma once
#include <string>

class Server
{
public:

    Server(const std::string& serverFifoName, const std::string& clientFifoName);
    ~Server();

	bool init();

    void readData(std::string& outReadData);
    bool writeData(std::string& pid, std::string& writeData);

private:
    int serverFd = -1;
    int clientFd = -1;

	const std::string m_serverFifoName;
	const std::string m_clientFifoBaseName;
};