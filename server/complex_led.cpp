#include <memory>
#include "complex_led.h"

ComplexLed::ComplexLed()
{
	m_inactiveLedPrimitives[eColorRed]   = std::make_unique<PrimitiveLed>(eColorRed);
	m_inactiveLedPrimitives[eColorGreen] = std::make_unique<PrimitiveLed>(eColorGreen);
	m_inactiveLedPrimitives[eColorBlue]  = std::make_unique<PrimitiveLed>(eColorBlue);
}

bool ComplexLed::setActiveColor(Color color)
{
	bool result = false;
	if (m_activeLedPrimitives.count(color) > 0)
	{
		result = true;
	}
	else if (m_inactiveLedPrimitives.count(color) > 0)
	{
		//TODO: make correct move
		for (auto& pl : m_activeLedPrimitives)
		{
			m_inactiveLedPrimitives[pl.first] = std::move(m_activeLedPrimitives[pl.first]);
		}
		m_activeLedPrimitives.clear();
		m_activeLedPrimitives[color] = std::move(m_inactiveLedPrimitives[color]);
		m_inactiveLedPrimitives.erase(color);

		result = true;
	}
	return result;
}

Color ComplexLed::getActiveColor() const
{
	if (m_activeLedPrimitives.size())
	{
		return m_activeLedPrimitives.begin()->first;
	}
	return eColorUnknown;
}


void ComplexLed::setPowerState(PowerState powerState)
{
	if(m_powerState != powerState)
	{
		m_powerState = powerState;
	}
}

PowerState ComplexLed::getPowerState() const
{
	return m_powerState;
}

bool ComplexLed::setBlinkFrequencyHz(uint32_t blinkFrequency)
{
	if (blinkFrequency <= MAX_BLINK_RATE)
	{
		bool isFound = false;
		for (auto& ap : m_activeLedPrimitives)
		{
			isFound = true;
			ap.second->m_blinkFrequencyHz = blinkFrequency;
		}
		return isFound;
	}
	return false;
}

uint32_t ComplexLed::getBlinkFrequencyHz() const
{
	if (m_activeLedPrimitives.size())
	{
		return m_activeLedPrimitives.begin()->second->m_blinkFrequencyHz;
	}
	return 0;
}

