//
// Created by oxford on 20.09.23.
//
#pragma once

#include "stm32l476xx.h"
#include "IGpioOutput.h"
#include "components/gpio/IPort.h"
#include "gpioPort.h"


namespace mcu::gpio {

    using namespace hal::gpio;
    
    /**
     * @brief Class holding functionality of gpio output. 
     */
    class gpioOutput : public hal::gpio::IGpioOutput
    {
    public:
        explicit gpioOutput(std::uint8_t pinId, std::shared_ptr<gpioPort> port,
            eTermination, bool lockConfig, eSpeed speed = eSpeed::eLow);
        eError off() override final;
        eError on() override final;
        eError toggle() override final;
        // eError deInit() override;
        // eError init() override;
        eError setSpeed(eSpeed speed) override final;
        eError setTermination(eTermination type) override final;
        eError lockConfiguration() override final;
    private:
        
        //reg specific, should be abstracted in future
        std::shared_ptr<mcu::gpio::gpioPort> m_port;
        GPIO_TypeDef *m_regs;

        std::int8_t m_pinId;

    };
} // mcu::gpio
