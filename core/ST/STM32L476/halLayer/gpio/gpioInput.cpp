//
// Created by oxford on 20.09.23.
//

#include "gpioInput.h"
#include <cassert>


namespace mcu::gpio
{
    gpioInput::gpioInput(std::uint32_t pinId, std::shared_ptr<gpioPort> port):
    IGpioInput(),
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

            err = m_port->setPinMode(eMode::eInput, m_pinId);
            if (err != eError::eOk)
            {
                assert(0);
            }
            
            // TODO: m_regs = 
        }
    }

    bool gpioInput::getState()
    {
        return m_regs->IDR & (1 << m_pinId);
    }

    // eError gpioInput::deInit() { return eError::eUninitialized; }

    // eError gpioInput::init() { return eError::eUninitialized; }

    eError gpioInput::setSpeed(eSpeed speed)
    {
        const auto pinOffset{2 * m_pinId};      //TODO: fix this masks
        m_regs->OSPEEDR = (static_cast<uint32_t>(speed) << pinOffset);

        return eError::eOk;
    }

    eError gpioInput::setTermination(eTermination type)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->PUPDR = (static_cast<uint32_t>(type) << pinOffset);
        return eError::eOk;
    }

    eError gpioInput::lockConfiguration()
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