//
// Created by oxford on 30.09.23.
//

#include "gpioPort.h"

namespace mcu::gpio 
{
    gpioPort::gpioPort(std::uint8_t portId):
    IPort(),
    m_id(portId)
    {
        m_regs = reinterpret_cast<GPIO_TypeDef*>
                (reinterpret_cast<uintptr_t>(cFirstGpioPort) + (cPortSizeInMem * m_id));
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
        constexpr std::uint32_t cAllModeBits{3}; 
        const auto pinOffset{2 * pinId};
        GPIO_TypeDef *defg = cFirstGpioPort;
        m_regs->MODER &= ~(cAllModeBits << pinOffset);
        m_regs->MODER |= (static_cast<uint32_t>(mode) << pinOffset);
        return eError::eOk;
    }

    void* gpioPort::giveReg() 
    {
      return m_regs;
    }
}  // namespace mcu::gpio
