#pragma once
#include <string>
#include <csignal>
#include "server.h"
#include "proxy.h"

class LedServer
{
public:
	LedServer();

	bool init();
	void run();

	static void signalHandler(int signalHandler);

private:
	static const std::string m_serverFifo;
	static const std::string m_clientFifoBase;

	static const std::string m_commandRegexp;
	Server m_server;
	Proxy  m_proxy;
	bool   m_isInit;

	volatile static std::sig_atomic_t m_terminateFlag;
};