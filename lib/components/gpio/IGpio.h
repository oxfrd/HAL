//
// Created by oxford on 19.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IPort.h"
#include "IMcu.h"

namespace hal::gpio
{
    enum class eMode
    {
        eInput,
        eOutput,
        eAlternateFun,
        eAnalog,
    };

    enum class eSpeed
    {
        eVeryLow,
        eLow,
        eMediumLow,
        eMedium,
        eMediumHigh,
        eHigh,
        eVeryHigh,
    };

    enum class eTermination
    {
        eNone,
        ePullUp,
        ePullDown,
        eReserved,
    };

    class IGpioInit
    {
    public:
        virtual eError enableClk() = 0;
        virtual eError disableClk() = 0;
        virtual eError setMode(eMode mode) = 0;
        virtual eError setTermination(eTermination type) = 0;
        virtual eError lockConfiguration() = 0;

    };

    struct gpioParams
    {
        eTermination termination{eTermination::eNone};
        eSpeed speed{eSpeed::eLow};
    };

    // template<typename port_t>
    class IGpioOutput : public IResource
    {
    public:
        IGpioOutput() = default;
//        IGpioOutput(port_t id, std::uint16_t pinNo, gpioParams initParam);
        virtual eError on() = 0;
        virtual eError off() = 0;
        virtual eError toggle() = 0;
        std::pair<std::shared_ptr<IGpioOutput>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    protected:
        virtual eError setSpeed(eSpeed speed) = 0;
        virtual eError setTermination(eTermination type) = 0;
        virtual eError lockConfiguration() = 0;

    private:
//        auto port = hal::gpio::IPort();
    };


    class IGpioInput
    {
    public:
        virtual eError getState();
    };
}