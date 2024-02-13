//
// Created by oxford on 20.09.23.
//
#pragma once

#include "ITimer.h"
#include "stm32l476xx.h"

namespace mcu::timer {

    using namespace hal::timer;
    
    /**
     * @brief Class holding functionality of timer output. 
     */
    template<class funArg_t, class reg_t>
    class timer : public hal::timer::ITimer
    {
    public:
        explicit timer(reg_t regs, period_t period, std::function<void(funArg_t)> execFunction);
    private:
        period_t m_period;

        virtual setPeriod(period_t period) = 0;

    };
} // mcu::timer
