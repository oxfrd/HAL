//
// Created by oxford on 20.09.23.
//

#include "delay.h"

#pragma GCC optimize ("O0")

static volatile bool mTimeIsUp{false};

__attribute__((interrupt)) void TIM2_IRQHandler()
{
    mTimeIsUp = true;

    TIM2->SR &= ~TIM_SR_UIF;
}

namespace mcu::delay
{
    using namespace hal::delay;

    delay::delay(std::shared_ptr<hal::interrupt::ITimeInterrupt> interrupt):
    IDelay()
    {
        if (interrupt != nullptr)
        {
            mInterrupt = interrupt;
            mInterrupt->disable();
        }
    }

    // min 25us for now, dont want to waste time for that
    eError delay::delayUs(uint32_t us)
    {
        mTimeIsUp = false;
        mInterrupt->setPeriod(us);
        mInterrupt->enable();
        while(mTimeIsUp == false){;}
        
        return eError::eOk;
    }

    eError delay::delayMs(uint32_t ms)
    {
        return delayUs(ms*1000);
    }
} // delay