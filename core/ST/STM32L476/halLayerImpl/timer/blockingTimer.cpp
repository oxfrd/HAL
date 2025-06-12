//
// Created by oxford on 09.06.25.
//

#include "blockingTimer.h"
#include <cassert>

#pragma GCC optimize ("O0")

namespace mcu::blockingTimer
{
    using namespace hal::timer;

    blockingTimer::blockingTimer(
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

    eError blockingTimer::setPeriod(period_t period) 
    {
        if (period < 3)
        {
            return eError::eBadArgument;
        }

        mRegs->ARR = 2*period-4;
        mRegs->CR1 |= TIM_CR1_CEN;

        while (!(mRegs->SR & TIM_SR_UIF));
        mRegs->SR &= ~TIM_SR_UIF;

        mRegs->CR1 &= ~TIM_CR1_CEN;

        return eError::eOk;
    }

    eError blockingTimer::enable()
    {
        mRegs->CR1 |= TIM_CR1_CEN;
        while(!(mRegs->SR & (1<<0)))
        return eError::eOk;
    }

    eError blockingTimer::disable()
    {
        mRegs->CR1 &= ~TIM_CR1_CEN;
        return eError::eOk;
    }

    eError blockingTimer::enableClk() 
    {
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
        return eError::eOk;
    }

    eError blockingTimer::setMode() 
    {
        mRegs->CR1 &= ~TIM_CR1_DIR;  // Counting direction - upwards
        mRegs->CR1 &= ~TIM_CR1_CMS;  // Basic mode
        mRegs->CR1 &= ~TIM_CR1_CKD;  // No clock dividing
        mRegs->CR1 |= TIM_CR1_OPM;   // One pulse mode
        mRegs->CCR1 = 0;
    
        return eError::eOk;
    }

    eError blockingTimer::enableInterrupt() 
    {
        mRegs->DIER |= TIM_DIER_UIE;
        
        return eError::eOk;
    }
} // blockingTimer