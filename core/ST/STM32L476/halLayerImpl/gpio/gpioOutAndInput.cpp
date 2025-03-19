//
// Created by oxford on 20.09.23.
//

#include "gpioOutAndInput.h"
#include <cassert>


namespace mcu::gpio
{
    gpioOutAndInput::gpioOutAndInput(std::uint8_t pinId, std::shared_ptr<gpioPort> port,
        eMode startMode, eTermination termination, eSpeed speed):
    IGpioOutAndInput(),
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

            err = m_port->setPinMode(startMode, m_pinId);
            if (err != eError::eOk)
            {
                assert(0);
            }
            m_actualMode = startMode;

            auto portReg = m_port->giveReg();
            m_regs = reinterpret_cast<GPIO_TypeDef*>(portReg);

            setTermination(termination);
            setSpeed(speed);
            }
    }

    eError gpioOutAndInput::on()
    {
        if (m_actualMode == eMode::eOutput)
        {
            m_regs->ODR |= (1 << m_pinId);
        }
        else
        {
            return eError::eNotPermitted;
        }
        
        return eError::eOk;
    }

    eError gpioOutAndInput::off()
    {
        if (m_actualMode == eMode::eOutput)
        {
            m_regs->ODR &= ~(1 << m_pinId);
        }
        else
        {
            return eError::eNotPermitted;
        }
        
        return eError::eOk;
    }

    bool gpioOutAndInput::getState()
    {
        if (m_actualMode == eMode::eInput)
        {
            return m_regs->IDR & (1 << m_pinId);
        }
        else
        {
            return false;
        }
    }

    eError gpioOutAndInput::setPinMode(eMode mode)
    {
        if (mode == eMode::eAlternateFun || mode == eMode::eAnalog)
        {
            return eError::eBadArgument;
        }

        auto err = m_port->setPinMode(mode, m_pinId);
        if (err == eError::eOk)
        {
            m_actualMode = mode;
        }
        return err;
    }

    eError gpioOutAndInput::setSpeed(eSpeed speed)
    {
        const auto pinOffset{2 * m_pinId};      //TODO: fix this masks
        m_regs->OSPEEDR = (static_cast<uint32_t>(speed) << pinOffset);

        return eError::eOk;
    }

    eError gpioOutAndInput::setTermination(eTermination type)
    {
        const auto pinOffset{2 * m_pinId};
        m_regs->PUPDR = (static_cast<uint32_t>(type) << pinOffset);
        return eError::eOk;
    }
} // namespace gpio