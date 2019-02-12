#pragma once
#include <string>
#include <vector>
#include <functional>
#include "complex_led.h"

struct Answer
{
	bool isSuccess = false;
	std::string answerStr;
};

class Proxy
{
public:

	Proxy(std::unique_ptr<ComplexLed> complexLed);
	std::string processRequest(std::string& request);

private:
	Answer handleRequest(std::vector<std::string>& request);
	std::vector<std::string> split(const std::string &s, char delim);

	std::unique_ptr<ComplexLed> m_complexLed;

	std::map<std::string, std::function<Answer(std::string& argument)>> m_commandMap;
	std::map<std::string, Color> m_colorMap;
	std::map<std::string, PowerState> m_stateMap;

	Answer handleSetLedState(std::string& argument);
	Answer handleGetLedState(std::string& argument);

	Answer handleSetLedColor(std::string& argument);
	Answer handleGetLedColor(std::string& argument);

	Answer handleSetLedRate(std::string& argument);
	Answer handleGetLedRate(std::string& argument);
	
};