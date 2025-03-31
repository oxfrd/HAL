//
// Created by oxford on 20.09.23.
//

#include "timer.h"


namespace mcu::timer
{
    using namespace hal::timer;

    countingTimer::countingTimer(
        TIM_TypeDef* regs)://, period_t period):
        m_regs(regs)
    {
        // setPeriod(5);
        enableClk();
        setMode();
        setPeriod();
        // enable();
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

        m_regs->PSC = 0;
        m_regs->ARR = (period * 16)-1;
        return eError::eOk;
    }

    eError countingTimer::enable()
    {
        m_regs->CR1 |= TIM_CR1_CEN;
        while(!(m_regs->SR & (1<<0)))
        return eError::eOk;
    }

    eError countingTimer::disable()
    {
        m_regs->CR1 &= ~TIM_CR1_CEN;
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
        m_regs->CR1 &= ~TIM_CR1_DIR;  // Counting direction - upwards
        m_regs->CR1 &= ~TIM_CR1_CMS;  // Basic mode
        m_regs->CR1 &= ~TIM_CR1_CKD;  // No clock dividing
        
        return eError::eOk;
    }

    eError mcu::timer::countingTimer::enableInterrupt() 
    {
        m_regs->DIER |= TIM_DIER_UIE;
        
        return eError::eOk;
    }
} // timer