//
// Created by oxford on 20.09.23.
//
#pragma once

#include "stm32l476xx.h"
#include "IInterrupt.h"

#include <functional>

namespace mcu::interrupt 
{
    /**
     * @brief Class holding functionality of time interrupt. 
     */
    class interrupt : public hal::interrupt::IInterrupt
    {
    public:
        /**
        * @brief Constructor of the interrupt class.
        *
        * Initializes the interrupt object by setting the interrupt with a specific ID, 
        * a timer, and a priority.
        *
        * @param id           IRQn_Type interrupt ID.
        * @param timer        Pointer to an object of the ITimer class.
        * @param priority     Interrupt priority.
        */
        interrupt(IRQn_Type id, std::uint32_t priority = cDefaultPriority);
        
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
        
        IRQn_Type m_id;
    };
}  // namespace mcu::timer
