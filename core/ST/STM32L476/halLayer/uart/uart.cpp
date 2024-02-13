//
// Created by oxford on 20.09.23.
//

#include "uart.h"


namespace mcu::uart
{
    using namespace hal::uart;

    uart::uart(std::uint8_t pinId, uint8_t portId, GPIO_TypeDef *regs):
    IUart(),
    m_port(uartPort(portId)),
    m_regs(regs),
    m_pinId(pinId)
    {
        setBaudrate(eMode::eOutput);
    }


    // eError uart::deInit() { return eError::eUninitialized; }

    // eError uart::init() { return eError::eUninitialized; }

    eError uart::setBaudrate(eBaudrate baudrate)
    {
        const auto pinOffset{2 * m_pinId};      //TODO: fix this masks

        return eError::eOk;
    }

} // uart