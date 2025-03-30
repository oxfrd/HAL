//
// Created by oxford on 20.09.23.
//

#include "delay.h"

#pragma GCC optimize ("O0")

volatile uint32_t mgDelay1usCnt{0};

__attribute__((interrupt)) void TIM2_IRQHandler()
{
    ++mgDelay1usCnt;
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

    // 10us for now, dont want to waste time for that
    eError delay::delayUs(std::chrono::microseconds us)
    {
        mInterrupt->enable();
        std::uint32_t finalTimestamp = mgDelay1usCnt + us.count();
        while(mgDelay1usCnt <= finalTimestamp)
        {
            asm("NOP");
        }
        // mInterrupt->disable();
    }

    eError delay::delayMs(std::chrono::milliseconds ms)
    {
        mInterrupt->enable();
        std::uint32_t finalTimestamp = mgDelay1usCnt + (50 * ms.count());
        while(mgDelay1usCnt <= finalTimestamp)
        {
            asm("NOP");
        }
        mInterrupt->disable();
    }
} // delay