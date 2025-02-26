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
        explicit countingTimer(TIM_TypeDef* regs); //, period_t period);
        eError setPeriod(period_t period) override;
        eError setPeriod();
        eError enable() override;
        eError disable() override;
        eError enableClk() override;
        eError enableInterrupt() override; 

    private:
        period_t m_period;
        TIM_TypeDef* m_regs;

        eError setMode();
    };
}  // namespace mcu::timer
