#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "proxy.h"

Proxy::Proxy(std::unique_ptr<Led> led) : m_led(std::move(led)),
    m_commandMap({  {"set-led-state", [&](const std::string& str) {return this->handleSetLedState(str); }},
                    {"get-led-state", [&](const std::string& str) {return this->handleGetLedState(str); }},
                    {"set-led-color", [&](const std::string& str) {return this->handleSetLedColor(str); }},
                    {"get-led-color", [&](const std::string& str) {return this->handleGetLedColor(str); }},
                    {"set-led-rate",  [&](const std::string& str) {return this->handleSetLedRate(str);  }},
                    {"get-led-rate",  [&](const std::string& str) {return this->handleGetLedRate(str);  }}}),

    m_colorMap( {{"red", eColorRed},
                {"green", eColorGreen},
                {"blue", eColorBlue}}),

    m_stateMap({{"off", ePowerStateOff },
                {"on", ePowerStateOn }})
{

}

std::string Proxy::processRequest(const std::string & request)
{
    std::vector<std::string> commandAndParams = split(request, ' ');
    Answer answer = handleRequest(commandAndParams);
    return answer.isSuccess ? "OK " + answer.answerStr : "FAILED";
}

std::vector<std::string>  Proxy::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

Answer Proxy::handleSetLedState(const std::string& argument)
{
    Answer answer;
    if (argument.empty() || m_stateMap.count(argument) == 0)
        return answer;

    answer.isSuccess = m_led->setPowerState(m_stateMap[argument]);;

    return answer;
}

Answer Proxy::handleGetLedState(const std::string& argument)
{
    Answer answer;
    if (!argument.empty())
        return answer;

    PowerState powerState = m_led->getPowerState();

    for (auto& ps : m_stateMap)
    {
        if (ps.second == powerState)
        {
            answer.answerStr = ps.first;
            answer.isSuccess = true;
        }
    }

    return answer;
}

Answer Proxy::handleSetLedColor(const std::string& argument)
{
    Answer answer;

    if (argument.empty() || m_colorMap.count(argument) == 0)
        return answer;

    m_led->setActiveColor(m_colorMap[argument]);
    answer.isSuccess = true;
    return answer;
}

Answer Proxy::handleGetLedColor(const std::string& argument)
{
    Answer answer;
    if (!argument.empty())
        return answer;

    Color color = m_led->getActiveColor();

    for (auto& c : m_colorMap)
    {
        if (c.second == color)
        {
            answer.answerStr = c.first;
            answer.isSuccess = true;
        }
    }

    return answer;
}

Answer Proxy::handleSetLedRate(const std::string& argument)
{
    Answer answer;

    if (argument.empty())
        return answer;

    int ledRate = 0;

    try
    {
        ledRate = std::stoi(argument);
    }
    catch (std::exception& e)
    {
        std::cout << "Exeption found " << __FUNCTION__ << " " << e.what() << std::endl;
        return answer;
    }

    answer.isSuccess = m_led->setBlinkFrequencyHz(ledRate);
    return answer;
}

Answer Proxy::handleGetLedRate(const std::string& argument)
{
    Answer answer;
    if (!argument.empty())
        return answer;

    uint32_t ledRate = m_led->getBlinkFrequencyHz();
    answer.answerStr = std::to_string(ledRate);
    answer.isSuccess = true;

    return answer;
}

Answer Proxy::handleRequest(const std::vector<std::string>& request)
{
    Answer answer;
    if (request.empty() || request.size() > 2)
        return answer;

    std::string command = request[0];

    if (m_commandMap.count(command) == 0)
        return answer;

    std::string parameters = request.size() == 2 ? request[1] : "";

    return m_commandMap[command](parameters);
}
