//
// Created by oxford on 20.09.23.
//

#include "interrupt.h"
#include <cassert>


namespace mcu::interrupt
{
    using namespace hal::interrupt;

    interrupt::interrupt(IRQn_Type id, std::uint32_t priority):
        m_id(id)
    {
        setPriority(priority);
        enable();
    }

    eError interrupt::enable() 
    {
        __enable_irq();
        NVIC_EnableIRQ(m_id);
        return eError::eOk;
    }

    eError interrupt::disable()
    {
        NVIC_DisableIRQ(m_id);
        return eError::eOk;
    }
    
    eError interrupt::setPriority(std::uint32_t priority)
    {
        if(m_id < 0) 
        {
            return eError::eNotPermitted;
        }

        if(priority == cDefaultPriority)
        {
            NVIC_SetPriority(m_id, 1);
            return eError::eOk;
        }

        if(priority > cLastPiority)
        {
            return eError::eBadArgument;
        }

        NVIC_SetPriority(m_id, priority);
        return eError::eOk;
    }

} // interrupt