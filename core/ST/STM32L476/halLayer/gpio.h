//
// Created by oxford on 20.09.23.
//
#pragma once

#include "IGpio.h"
#include "stm32l476xx.h"
#include "components/gpio/IPort.h"
#include "gpioPort.h"


namespace mcu::gpio {

    using namespace hal::gpio;
    class gpioOutput : public hal::gpio::IGpioOutput<GPIO_TypeDef>
    {
    public:
        explicit gpioOutput(std::uint8_t pinId, uint8_t portId, GPIO_TypeDef *regs);
        error off() override;
        error on() override;
        error toggle() override;
    protected:
        error setSpeed(eSpeed speed) override;
        error setTermination(eTermination type) override;
        error lockConfiguration() override;
        error setMode(eMode);
    private:
        //reg specific, should be abstracted in future
        mcu::gpio::gpioPort m_port;
        GPIO_TypeDef *m_regs;

        std::int8_t m_pinId;

    };
} // mcu::gpio
