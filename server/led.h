#include <map>
#include <memory>

enum PowerState
{
    ePowerStateOff,
    ePowerStateOn
};

enum Color
{
    eColorUnknown,
    eColorRed,
    eColorGreen,
    eColorBlue
};

const uint32_t MAX_BLINK_RATE = 5;

class Led
{
public:
    Led();

    void setActiveColor(Color color);
    Color getActiveColor() const;

    bool setPowerState(PowerState powerState);
    PowerState getPowerState() const;

    bool setBlinkFrequencyHz(uint32_t blinkRateHz);
    uint32_t getBlinkFrequencyHz() const;


private:
    PowerState m_powerState = ePowerStateOff;
    Color m_color = eColorUnknown;
    uint32_t m_blinkFrequencyHz = 0;
};