//
// Created by oxford on 20.09.23.
//

#include "gpio.h"


namespace hal::gpio
{

    gpioOutput::gpioOutput(std::uint8_t portId):
    m_port(hal::gpio::IPort(GPIOB))
    {
        setMode(eMode::eOutput);
    }

    error gpioOutput::on()
    {
        error err = error::eUninitialized;
        return err;
    }

    error gpioOutput::off()
    {
        error err = error::eUninitialized;
        return err;
    }

    error gpioOutput::setMode(eMode mode)
    {
        GPIOB->MODER = static_cast<uint32_t>(mode);
        return error::eOk;
    }

    error gpioOutput::setTermination(eTermination type)
    {
        GPIOB->PUPDR = static_cast<uint32_t>(type);
        return error::eOk;
    }

    error gpioOutput::lockConfiguration()
    {
        constexpr uint32_t LCKR16 = (1 <<16);
        auto err {error::eFail};

        auto lockState = []() {
            return GPIOB->LCKR & LCKR16;
        };

        if (lockState() == true)
        {
            err = error::eOk;
        } else
        {
            GPIOB->LCKR |= LCKR16;
            GPIOB->LCKR &= ~LCKR16;
            GPIOB->LCKR |= LCKR16;

            if (lockState() == true)
            {
                err = error::eOk;
            }
        }
        return err;
    }


} // hal::gpio