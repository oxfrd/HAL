//
// Created by oxford on 20.09.23.
//
#pragma once

#include "stm32l476xx.h"
#include "ITimer.h"
#include "ITimeInterrupt.h"
#include "timer.h"

#include <functional>

namespace mcu::interrupt 
{
    /**
     * @brief Class holding functionality of time interrupt. 
     */
    class timeInterrupt : public hal::interrupt::ITimeInterrupt
    {
    public:
        /**
        * @brief Constructor of the TimeInterrupt class.
        *
        * Initializes the TimeInterrupt object by setting the interrupt with a specific ID, 
        * a timer, and a priority.
        *
        * @param id           IRQn_Type interrupt ID.
        * @param timer        Pointer to an object of the ITimer class.
        * @param priority     Interrupt priority.
        */
        timeInterrupt(IRQn_Type id, std::shared_ptr<hal::timer::ITimer> timer, 
            std::uint32_t priority = cDefaultPriority);
        
        /**
        * @brief Enable interrupt.
        *
        * @return always eError::eOk
        */
        eError enable() override;
        
        /**
        * @brief Disable interrupt.
        *
        * @return always eError::eOk
        */
        eError disable() override;

        /**
        * @brief Sets interrupt priority.
        * 
        * @param priority     Priority to be set.
        * @return eError::eOk if priority was set successfully or set to default.
        *         eError::eNotPermitted if tried to set priority of cpu exception.
        */
        eError setPriority(std::uint32_t priority) override;
    private:
        static constexpr std::uint32_t cDefaultPriority{UINT32_MAX};
        static constexpr std::uint32_t cLastPiority{20};
        
        std::shared_ptr<hal::timer::ITimer> m_timer;
        IRQn_Type m_id;
    };
}  // namespace mcu::timer
