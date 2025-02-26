//
// Created by oxford on 20.09.23.
//

#include "timeInterrupt.h"
#include <cassert>


namespace mcu::interrupt
{
    using namespace hal::interrupt;

    timeInterrupt::timeInterrupt(IRQn_Type id, std::shared_ptr<hal::timer::ITimer> timer, 
        std::uint32_t priority):
        m_id(id)
    {
        assert(timer != nullptr);
        m_timer = timer;

        setPriority(priority);
        // enable();
        // timer->enableInterrupt();
        // timer->enable();
    }

    eError timeInterrupt::enable() 
    {
        __enable_irq();
        m_timer->enableInterrupt();
        m_timer->enable(); 
        NVIC_EnableIRQ(m_id);
        return eError::eOk; 
    }

    eError timeInterrupt::disable()
    {
        NVIC_DisableIRQ(m_id);
        return eError::eOk;
    }
    
    eError timeInterrupt::setPriority(std::uint32_t priority)
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

} // timer