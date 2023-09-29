//
// Created by oxford on 27.09.23.
//

#include "IPort.h"

namespace hal::gpio {

    IPort::IPort(GPIO_TypeDef *portId):
    m_regs(portId)
    {
        constexpr uint32_t cPortSizeInMem = 0x400;
        m_id = reinterpret_cast<uint32_t>(&portId - AHB2PERIPH_BASE);
        m_id /= cPortSizeInMem;

        *m_RCCEnReg = RCC->AHB2ENR;

        enableClk();
    }

    error IPort::enableClk()
    {
        *m_RCCEnReg |= (1 << static_cast<uint32_t>(m_id));
        return error::eOk;
    }

    error IPort::disableClk()
    {
        *m_RCCEnReg &= ~(1 << static_cast<uint32_t>(m_id));
        return error::eOk;
    }

}
