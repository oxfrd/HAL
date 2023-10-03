//
// Created by oxford on 30.09.23.
//

#include "port.h"

namespace mcu::gpio {

    port::port(GPIO_TypeDef *portId) :
    IPort(),
    m_regs(portId)
    {
        m_id = reinterpret_cast<uint32_t>(&portId - cPeriphBaseOffset);
        m_id /= cPortSizeInMem;

        enableClk();
    }

    error port::enableClk()
    {
        *m_RCCEnReg |= (1 << static_cast<uint32_t>(m_id));
        return error::eOk;
    }

    error port::disableClk()
    {
        *m_RCCEnReg &= ~(1 << static_cast<uint32_t>(m_id));
        return error::eOk;
    }

}
