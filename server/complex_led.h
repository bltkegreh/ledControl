#include "primitive_led.h"
#include <map>
#include <memory>

enum PowerState
{
	ePowerStateOff,
	ePowerStateOn
};

class ComplexLed
{
public:
	ComplexLed();

	bool setActiveColor(Color color);
	Color getActiveColor() const;

	void setPowerState(PowerState powerState);
	PowerState getPowerState() const;

	bool setBlinkFrequencyHz(uint32_t blinkRateHz);
	uint32_t getBlinkFrequencyHz() const;


private:
	PowerState m_powerState = ePowerStateOff;
	
	std::map<Color, std::unique_ptr<PrimitiveLed>> m_inactiveLedPrimitives;
	std::map<Color, std::unique_ptr<PrimitiveLed>> m_activeLedPrimitives;
};