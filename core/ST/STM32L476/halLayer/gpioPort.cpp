//
// Created by oxford on 30.09.23.
//

#include "gpioPort.h"

namespace mcu::ST32L476::gpio {

    gpioPort::gpioPort(uint8_t portId):
    IPort(),
    m_id(portId)
    {
        enableClk();
    }

    error gpioPort::enableClk()
    {
        *m_RCCEnReg |= (1 << m_id);
        return error::eOk;
    }

    error gpioPort::disableClk()
    {
        *m_RCCEnReg &= ~(1 << m_id);
        return error::eOk;
    }
}
