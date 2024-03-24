//
// Created by oxford on 20.09.23.
//

#include "gpioOutput.h"
#include <cassert>


namespace mcu::gpio
{
    gpioOutput::gpioOutput(std::uint8_t pinId, std::shared_ptr<gpioPort> port, GPIO_TypeDef *regs):
    IGpioOutput(),
    m_port(port),
    m_regs(regs),
    m_pinId(pinId)
    {
        auto err = setMode(eMode::eOutput);
        if (err != eError::eOk)
        {
            assert(0);
        }
        if (m_port == nullptr)
        {
            assert(0);   
        } 
        else
        {
            err = m_port->enableClk();
            if (err != eError::eOk)
            {
                assert(0);
            }
        }
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

} // gpio