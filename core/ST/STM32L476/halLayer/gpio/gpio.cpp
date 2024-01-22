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

    eError gpioOutput::on()
    {
        eError err = eError::eUninitialized;
        m_regs->ODR |= (1 << m_pinId);
        return err;
    }

    eError gpioOutput::off()
    {
        eError err = eError::eUninitialized;
        m_regs->ODR &= ~(1 << m_pinId);
        return err;
    }

    eError gpioOutput::toggle()
    {
        eError err = eError::eUninitialized;
        m_regs->ODR ^= (1 << m_pinId);
        return err;
    }

    // eError gpioOutput::deInit() { return eError::eUninitialized; }

    // eError gpioOutput::init() { return eError::eUninitialized; }

    eError gpioOutput::setSpeed(eSpeed speed)
    {
        const auto pinOffset{2 * m_pinId};      //TODO: fix this masks
        m_regs->OSPEEDR = (static_cast<uint32_t>(speed) << pinOffset);

        return eError::eOk;
    }

    eError gpioOutput::setTermination(eTermination type)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->PUPDR = (static_cast<uint32_t>(type) << pinOffset);
        return eError::eOk;
    }

    eError gpioOutput::lockConfiguration()
    {
        constexpr uint32_t LCKR16 = (1 <<16);
        auto err {eError::eFail};

        auto lockState = [this]() {
            return m_regs->LCKR & LCKR16;
        };

        if (lockState() == true)
        {
            err = eError::eOk;
        } else
        {
            m_regs->LCKR |= LCKR16;
            m_regs->LCKR &= ~LCKR16;
            m_regs->LCKR |= LCKR16;

            if (lockState() == true)
            {
                err = eError::eOk;
            }
        }
        return err;
    }

    eError gpioOutput::setMode(eMode mode)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->MODER = (static_cast<uint32_t>(mode) << pinOffset);
        return eError::eOk;
    }

} // ST32L476::gpio