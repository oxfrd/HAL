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
        virtual error enableClk() = 0;
        virtual error disableClk() = 0;
        virtual error setMode(eMode mode) = 0;
        virtual error setTermination(eTermination type) = 0;
        virtual error lockConfiguration() = 0;

    };

    struct gpioParams
    {
        eTermination termination{eTermination::eNone};
        eSpeed speed{eSpeed::eLow};
    };

    // template<typename port_t>
    class IGpioOutput : virtual public IResource
    {
    public:
        IGpioOutput() = default;
//        IGpioOutput(port_t id, std::uint16_t pinNo, gpioParams initParam);
        virtual error on() = 0;
        virtual error off() = 0;
        virtual error toggle() = 0;

    protected:
        virtual error setSpeed(eSpeed speed) = 0;
        virtual error setTermination(eTermination type) = 0;
        virtual error lockConfiguration() = 0;

    private:
//        auto port = hal::gpio::IPort();
    };


    class IGpioInput
    {
    public:
        virtual error getState();
    };
}