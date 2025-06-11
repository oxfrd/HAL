//
// Created by oxford on 20.09.23.
//

#include "timer.h"
#include <cassert>


namespace mcu::timer
{
    using namespace hal::timer;

    countingTimer::countingTimer(
        TIM_TypeDef* regs, uint32_t mcuClockFreq, period_t period):
        mRegs(regs),
        mMcuClockFreq(mcuClockFreq)
    {
        assert(mRegs != nullptr);
        enableClk();
        setMode();
        mRegs->PSC = (mMcuClockFreq/cDefault1us)-1;
        setPeriod(period);
    }

    /**
     * @brief Set period for timer. For now only 1us, but minimal proper one is 25us.
     * In the future will be extended to proper settings.
     * @param period number of us to set
     * @return 
     */
    eError countingTimer::setPeriod(period_t period) 
    {
        if (period == 0)
        {
            return eError::eBadArgument;
        }

        mRegs->PSC = 0;
        mRegs->CNT = 0;
        mRegs->ARR = (period * 16)-1;
        return eError::eOk;
    }

    eError countingTimer::enable()
    {
        mRegs->CR1 |= TIM_CR1_CEN;
        while(!(mRegs->SR & (1<<0)))
        return eError::eOk;
    }

    eError countingTimer::disable()
    {
        mRegs->CR1 &= ~TIM_CR1_CEN;
        return eError::eOk;
    }

    eError mcu::timer::countingTimer::enableClk() 
    {
        //Turn on clock for TIM2
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
        return eError::eOk;
    }

    eError mcu::timer::countingTimer::setMode() 
    {
        mRegs->CR1 &= ~TIM_CR1_DIR;  // Counting direction - upwards
        mRegs->CR1 &= ~TIM_CR1_CMS;  // Basic mode
        mRegs->CR1 &= ~TIM_CR1_CKD;  // No clock dividing
        mRegs->CR1 |= TIM_CR1_OPM;   // One pulse mode
        mRegs->CCR1 = 0;

        return eError::eOk;
    }

    eError mcu::timer::countingTimer::enableInterrupt() 
    {
        mRegs->DIER |= TIM_DIER_UIE;
        
        return eError::eOk;
    }
} // timer