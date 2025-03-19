//
// Created by oxford on 01.10.23.
//
#include "errors.h"
#include "IPort.h"
#include "IGpio.h"
#include "IMcu.h"

namespace hal::gpio
{
    class IGpioOutAndInput : public IResource
    {
    public:
        IGpioOutAndInput() = default;
        virtual eError on() = 0;
        virtual eError off() = 0;
        virtual bool getState() = 0;
        virtual eError setPinMode(eMode mode) = 0;
        std::pair<std::shared_ptr<IGpioOutAndInput>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError setSpeed(eSpeed speed) = 0;
        virtual eError setTermination(eTermination type) = 0;
        
    };
} // namespace hal::gpio