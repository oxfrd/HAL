//
// Created by oxford on 20.09.23.
//

#include "timer.h"


namespace mcu::timer
{
    using namespace hal::timer;

    countingTimer::countingTimer(
        timerReg_t regs)://, period_t period):
        m_regs(regs)
    {
        // setPeriod(5);
        setMode();
        enable();
    }

    eError countingTimer::setPeriod(period_t period) 
    {
        m_period = period;
        // Set prescaler and period
        m_regs->PSC = 39999;   // Prescaler (APB1 = 40 MHz, wanted 1 kHz)
        m_regs->ARR = 999;    // Period (1 kHz / 1 Hz = 1000)

        return eError::eOk;
    }

    eError countingTimer::enable()
    {
        m_regs->CR1 |= TIM_CR1_CEN;
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

} // timer