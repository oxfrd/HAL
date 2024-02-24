//
// Created by oxford on 20.09.23.
//
#pragma once

#include "ITimer.h"
#include "stm32l476xx.h"

#include <functional>

namespace mcu::timer 
{
    using namespace hal::timer;
    using timerReg_t = TIM_TypeDef*;

    /**
     * @brief Class holding functionality of timer output. 
     */
    class countingTimer : public ITimer
    {
    public:
        explicit countingTimer(timerReg_t regs); //, period_t period);
        eError setPeriod(period_t period) override;
        eError enable() override;
        eError disable() override;
        eError enableClk() override;

    private:
        period_t m_period;
        timerReg_t m_regs;

        eError setMode();
    };
}  // namespace mcu::timer
