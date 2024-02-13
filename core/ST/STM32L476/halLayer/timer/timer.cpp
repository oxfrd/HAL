//
// Created by oxford on 20.09.23.
//

#include "timer.h"


namespace mcu::timer
{
    using namespace hal::timer;

    timer::timer(period_t period):
    ITimer(),
    m_regs(regs),
    {
        setPeriod(period);
    }

} // timer