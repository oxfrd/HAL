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
    class gpioOutput : public hal::gpio::IGpioOutput //<GPIO_TypeDef>
    {
    public:
        explicit gpioOutput(std::uint8_t pinId, uint8_t portId, GPIO_TypeDef *regs);
        eError off() override final;
        eError on() override final;
        eError toggle() override final;
        // eError deInit() override;
        // eError init() override;
    protected:
        eError setSpeed(eSpeed speed) override final;
        eError setTermination(eTermination type) override final;
        eError lockConfiguration() override final;
        eError setMode(eMode);
    private:
        
        //reg specific, should be abstracted in future
        mcu::gpio::gpioPort m_port;
        GPIO_TypeDef *m_regs;

        std::int8_t m_pinId;

    };
} // mcu::gpio