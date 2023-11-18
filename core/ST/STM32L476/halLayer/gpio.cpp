//
// Created by oxford on 20.09.23.
//

#include "gpio.h"


namespace mcu::ST32L476::gpio
{
    using namespace hal::gpio;

    gpioOutput::gpioOutput(std::uint8_t pinId, uint8_t portId, GPIO_TypeDef *regs):
    IGpioOutput(),
    m_port(gpioPort(portId)),
    m_regs(regs),
    m_pinId(pinId)
    {
        setMode(eMode::eOutput);
    }

    error gpioOutput::on()
    {
        error err = error::eUninitialized;
        m_regs->ODR |= (1 << m_pinId);
        return err;
    }

    error gpioOutput::off()
    {
        error err = error::eUninitialized;
        m_regs->ODR &= ~(1 << m_pinId);
        return err;
    }

    error gpioOutput::toggle()
    {
        error err = error::eUninitialized;
        m_regs->ODR ^= (1 << m_pinId);
        return err;
    }

    // error gpioOutput::deInit() { return error::eUninitialized; }

    // error gpioOutput::init() { return error::eUninitialized; }

    error gpioOutput::setSpeed(eSpeed speed)
    {
        const auto pinOffset{2 * m_pinId};      //TODO: fix this masks
        m_regs->OSPEEDR = (static_cast<uint32_t>(speed) << pinOffset);

        return error::eOk;
    }

    error gpioOutput::setTermination(eTermination type)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->PUPDR = (static_cast<uint32_t>(type) << pinOffset);
        return error::eOk;
    }

    error gpioOutput::lockConfiguration()
    {
        constexpr uint32_t LCKR16 = (1 <<16);
        auto err {error::eFail};

        auto lockState = [this]() {
            return m_regs->LCKR & LCKR16;
        };

        if (lockState() == true)
        {
            err = error::eOk;
        } else
        {
            m_regs->LCKR |= LCKR16;
            m_regs->LCKR &= ~LCKR16;
            m_regs->LCKR |= LCKR16;

            if (lockState() == true)
            {
                err = error::eOk;
            }
        }
        return err;
    }

    error gpioOutput::setMode(eMode mode)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->MODER = (static_cast<uint32_t>(mode) << pinOffset);
        return error::eOk;
    }

} // ST32L476::gpio