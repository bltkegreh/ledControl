#include <experimental/any>
#include "led.h"
#include <iostream>


Led::Led()
{
}

void Led::setActiveColor(Color color)
{
    m_color = color;
}

Color Led::getActiveColor() const
{
    return m_color;
}


bool Led::setPowerState(PowerState powerState)
{
    bool isSuccess = false;
    if(m_powerState != powerState)
    {
        if(m_color != eColorUnknown)
        {
            m_powerState = powerState;
            isSuccess = true;
        }
        else
        {
            std::cout << "Active color not set" << std::endl;
        }
    }
    return isSuccess;
}

PowerState Led::getPowerState() const
{
    return m_powerState;
}

bool Led::setBlinkFrequencyHz(uint32_t blinkFrequency)
{
    if (blinkFrequency <= MAX_BLINK_RATE)
    {
        m_blinkFrequencyHz = blinkFrequency;
        return true;
    }
    return false;
}

uint32_t Led::getBlinkFrequencyHz() const
{
    return m_blinkFrequencyHz;
}

