//
// Created by oxford on 19.09.23.
//
#pragma once
#include "errors.h"

namespace hal::gpio
{
    enum class eMode
    {
        eInput,
        eOutput,
        eAlternateFun,
        eAnalog
    };

    enum class eTermination
    {
        eNone,
        ePullUp,
        ePullDown,
        eReserved,
    };

    enum class eGPIOPort
    {
        ePortA,
        ePortB,
        ePortC,
        ePortD,
        ePortE,
        ePortF,
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
    
    class IGpioOutput
    {
    public:
        virtual error on();
        virtual error off();
        virtual error toggle();

    protected:
        virtual error setSpeed();
    };

    class IGpioInput
    {
    public:
        virtual error getState();
    };
}