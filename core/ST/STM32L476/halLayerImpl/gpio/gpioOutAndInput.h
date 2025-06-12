//
// Created by oxford on 20.09.23.
//
#pragma once

#include "stm32l476xx.h"
#include "IGpioOutAndInput.h"
#include "components/gpio/IPort.h"
#include "gpioPort.h"


namespace mcu::gpio {

    using namespace hal::gpio;
    
    /**
     * @brief Class holding functionality of gpio output. 
     */
    class gpioOutAndInput : public hal::gpio::IGpioOutAndInput
    {
    public:
        explicit gpioOutAndInput(std::uint8_t pinId, std::shared_ptr<gpioPort> port, 
            eMode startMode = eMode::eOutput, eTermination termination = eTermination::ePullUp,
            eSpeed speed = eSpeed::eLow);
        eError off() override final;
        eError on() override final;
        bool getState() override final;
        eError setPinMode(eMode mode) override final;
        eError setSpeed(eSpeed speed) override final;
        eError setTermination(eTermination type) override final;
    private:
        //reg specific, should be abstracted in future
        std::shared_ptr<mcu::gpio::gpioPort> m_port;
        GPIO_TypeDef *m_regs;

        std::int8_t m_pinId;
        eMode m_actualMode;
    };
} // mcu::gpio
