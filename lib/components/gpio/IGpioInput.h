//
// Created by oxford on 01.10.23.
//
#include "errors.h"
#include "IPort.h"
#include "IGpio.h"
#include "IMcu.h"

namespace hal::gpio
{
    class IGpioInput : public IResource
    {
    public:
        IGpioInput() = default;
        virtual bool getState() = 0;
        std::pair<std::shared_ptr<IGpioInput>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    protected:
        virtual eError setSpeed(eSpeed speed) = 0;
        virtual eError setTermination(eTermination type) = 0;
        virtual eError lockConfiguration() = 0;
    };
} // namespace hal::gpio