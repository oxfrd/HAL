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
        mId(id)
    {
        assert(timer != nullptr);
        mTimer = timer;

        setPriority(priority);
        // enable();
        // timer->enableInterrupt();
        // timer->enable();
    }

    eError timeInterrupt::enable() 
    {
        __enable_irq();
        mTimer->enableInterrupt();
        mTimer->enable(); 
        NVIC_EnableIRQ(mId);
        return eError::eOk; 
    }

    eError timeInterrupt::disable()
    {
        NVIC_DisableIRQ(mId);
        return eError::eOk;
    }
    
    eError timeInterrupt::setPriority(std::uint32_t priority)
    {
        if(mId < 0) 
        {
            return eError::eUninitialized;
        }

        if(priority == cDefaultPriority)
        {
            NVIC_SetPriority(mId, 1);
            return eError::eOk;
        }

        if(priority > cLastPiority)
        {
            return eError::eBadArgument;
        }

        NVIC_SetPriority(mId, priority);
        return eError::eOk;
    }

    eError timeInterrupt::setPeriod(hal::timer::period_t period)
    {
        if(mId < 0) 
        {
            return eError::eUninitialized;
        }

        mTimer->setPeriod(period);

        return eError::eOk;
    }


} // timer