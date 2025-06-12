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

    /**
     * @brief Class holding functionality of timer output. 
     */
    class countingTimer : public ITimer
    {
    public:
        explicit countingTimer(TIM_TypeDef* regs, uint32_t mcuClockFreq, period_t period = 25);
        eError setPeriod(period_t period) override;
        eError enable() override;
        eError disable() override;
        eError enableClk() override;
        eError enableInterrupt() override; 

    private:
        uint32_t cDefault1us{1000000};
        uint32_t mMcuClockFreq{};
        uint32_t mPrescalerValue{1};
        period_t mPeriod;
        TIM_TypeDef* mRegs{nullptr};

        eError setMode();
    };
}  // namespace mcu::timer
