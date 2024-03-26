//
// Created by oxford on 20.09.23.
//
#pragma once

#include "stm32l476xx.h"
#include "IGpioInput.h"
#include "components/gpio/IPort.h"
#include "gpioPort.h"

namespace mcu::gpio {

    using namespace hal::gpio;
    
    /**
     * @brief Class holding functionality of gpio input. 
     */
    class gpioInput : public hal::gpio::IGpioInput
    {
    public:
        explicit gpioInput(std::uint8_t pinId, std::shared_ptr<gpioPort> port, GPIO_TypeDef *regs);
        bool getState() override final;
    protected:
        eError setSpeed(eSpeed speed) override final;
        eError setTermination(eTermination type) override final;
        eError lockConfiguration() override final;
    private:
        //reg specific, should be abstracted in future
        std::shared_ptr<mcu::gpio::gpioPort> m_port;
        GPIO_TypeDef *m_regs;
        std::uint32_t m_pinId;
    };
} // mcu::gpio
