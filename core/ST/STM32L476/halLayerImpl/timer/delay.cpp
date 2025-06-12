//
// Created by oxford on 20.09.23.
//

#include "delay.h"
#include <cassert>

namespace mcu::delay
{
    using namespace hal::delay;

    delay::delay(std::shared_ptr<hal::timer::ITimer> blocker):
    IDelay()
    {
        mBlocker = blocker;
        assert(mBlocker != nullptr);
        mBlocker->disable();
    }

    eError delay::delayUs(uint32_t us)
    {
        return mBlocker->setPeriod(us);
    }

    eError delay::delayMs(uint32_t ms)
    {
        return mBlocker->setPeriod(ms*1000+(ms/125*250));
    }

} // delay