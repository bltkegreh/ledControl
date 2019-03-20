#pragma once
#include <string>
#include <vector>
#include <functional>
#include "led.h"

struct Answer
{
    bool isSuccess = false;
    std::string answerStr;
};

class Proxy
{
public:

    Proxy(std::unique_ptr<Led> led);
    std::string processRequest(const std::string& request);

private:
    Answer handleRequest(const std::vector<std::string>& request);
    std::vector<std::string> split(const std::string &s, char delim);

    std::unique_ptr<Led> m_led;

    std::map<std::string, std::function<Answer(const std::string& argument)>> m_commandMap;
    std::map<std::string, Color> m_colorMap;
    std::map<std::string, PowerState> m_stateMap;

    Answer handleSetLedState(const std::string& argument);
    Answer handleGetLedState(const std::string& argument);

    Answer handleSetLedColor(const std::string& argument);
    Answer handleGetLedColor(const std::string& argument);

    Answer handleSetLedRate(const std::string& argument);
    Answer handleGetLedRate(const std::string& argument);
};