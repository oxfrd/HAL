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
}
