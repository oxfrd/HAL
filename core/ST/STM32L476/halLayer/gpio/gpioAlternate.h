//
// Created by oxford on 28.04.24.
//
#pragma once

#include "stm32l476xx.h"
#include "components/gpio/IPort.h"
#include "IGpioAlternate.h"
#include "gpioPort.h"

namespace mcu::gpio {

    using namespace hal::gpio;
    
    /**
     * @brief Class holding functionality of gpio alternate function. 
     */
    class gpioAlternate : public hal::gpio::IGpioAlternate
    {
    public:
        explicit gpioAlternate(std::uint32_t pinId, std::shared_ptr<gpioPort> port);
    private:
        //reg specific, should be abstracted in future
        std::shared_ptr<mcu::gpio::gpioPort> m_port;
        std::uint32_t m_pinId;
    };
} // mcu::gpio
