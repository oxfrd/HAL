//
// Created by oxford on 30.09.23.
//

#include "gpioPort.h"

namespace mcu::gpio {

    gpioPort::gpioPort(std::uint8_t portId):
    IPort(),
    m_id(portId)
    {
        enableClk();
    }

    eError gpioPort::enableClk()
    {
        *m_RCCEnReg |= (1 << m_id);
        return eError::eOk;
    }

    eError gpioPort::disableClk()
    {
        *m_RCCEnReg &= ~(1 << m_id);
        return eError::eOk;
    }
    
    eError gpioPort::setPinMode(hal::gpio::eMode mode, std::uint32_t pinId)
    {
        const auto pinOffset{2 * pinId};
        m_regs->MODER = (static_cast<uint32_t>(mode) << pinOffset);
        return eError::eOk;
    }
}
