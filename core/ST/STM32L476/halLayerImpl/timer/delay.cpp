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
        }
    }

    // min 25us for now, dont want to waste time for that
    eError delay::delayUs(std::chrono::microseconds us)
    {
        mTimeIsUp = false;
        mInterrupt->setPeriod(us.count());
        mInterrupt->enable();
        while(mTimeIsUp == false)
        {
             asm("NOP");
        }
        mInterrupt->disable();
    }

    eError delay::delayMs(std::chrono::milliseconds ms)
    {
        delayUs(ms);
        return eError::eOk;
    }
} // delay