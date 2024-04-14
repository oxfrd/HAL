//
// Created by oxford on 20.09.23.
//

#include "gpioOutput.h"
#include <cassert>


namespace mcu::gpio
{
    gpioOutput::gpioOutput(std::uint8_t pinId, std::shared_ptr<gpioPort> port):
    IGpioOutput(),
    m_port(port),
    m_pinId(pinId)
    {
        if (m_port == nullptr)
        {
            assert(0);   
        } 
        else
        {
            auto err = m_port->enableClk();
            if (err != eError::eOk)
            {
                assert(0);
            }

            err = m_port->setPinMode(eMode::eOutput, m_pinId);
            if (err != eError::eOk)
            {
                assert(0);
            }
            auto portReg = m_port->giveReg();
            m_regs = reinterpret_cast<GPIO_TypeDef*>(portReg);
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
} // namespace gpio