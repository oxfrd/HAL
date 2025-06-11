//
// Created by oxford on 09.06.25.
//
#pragma once

#include "ITimer.h"
#include "stm32l476xx.h"

#include <functional>

namespace mcu::blockingTimer 
{
    using namespace hal::timer;

    /**
     * @brief Class holding functionality of blocking timer output. 
     */
    class blockingTimer : public ITimer
    {
    public:
        explicit blockingTimer(TIM_TypeDef* regs, uint32_t mcuClockFreq, period_t period = 25);

        /**
         * @brief Set and block soft execution for specified period. 
         * For now only 1us domain. Minimal settable one is 3us.
         * In the future will be extended to proper settings, leving it now.
         * @param period [us] to wait (cant be smaller than 3) 
         * @return result of execultion
         */
        eError setPeriod(period_t period) override;
        
        /**
         * @brief Enable timer for previously set period.
         * @return eError:eOk
         */
        eError enable() override;

        /**
         * @brief Disable execution of timer.
         * @return eError:eOk
         */
        eError disable() override;

    private:
        const uint32_t cDefault1us{2000000};

        volatile TIM_TypeDef* mRegs;
        uint32_t mMcuClockFreq{};
        uint32_t mPrescalerValue{1};
        period_t mPeriod;

        /**
         * @brief Enable clock which is base for timing.
         * @return eError:eOk
         */
        eError enableClk();
        
        /**
         * @brief Set mode of timer needed to blocking. 
         * @return eError:eOk
         */
        eError setMode();

        /**
         * @brief Set mode of timer needed to blocking. 
         * @return eError:eOk
         */
        eError enableInterrupt();

    };
}  // namespace mcu::blockingTimer