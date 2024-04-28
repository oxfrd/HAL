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
        }
    }
} // namespace gpio