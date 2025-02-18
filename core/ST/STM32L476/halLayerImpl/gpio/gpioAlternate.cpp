//
// Created by oxford on 28.04.24.
//

#include "gpioAlternate.h"
#include <cassert>


namespace mcu::gpio
{
    gpioAlternate::gpioAlternate(std::uint32_t pinId, std::shared_ptr<gpioPort> port):
    IGpioAlternate(),
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

            err = m_port->setPinMode(eMode::eAlternateFun, m_pinId);
            if (err != eError::eOk)
            {
                assert(0);
            }
            auto portReg = m_port->giveReg();
            m_regs = reinterpret_cast<GPIO_TypeDef*>(portReg);
        }
    }

    eError gpioAlternate::setFunctionality(std::uint32_t fun) 
    { 
        if(fun > static_cast<std::uint32_t>(eFunctionality::eLastIdx_EVENTOUT))
        {
            return eError::eBadArgument;
        }

        if(m_pinId <= cLastPinInAFR0)
        {
            m_regs->AFR[0] |= (fun << m_pinId*4);
        }
        else
        {
            m_regs->AFR[1] |= (fun << (m_pinId - 7)*4);
        }

        return eError::eOk; 
    }

} // namespace gpio