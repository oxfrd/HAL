//
// Created by oxford on 20.03.25.
//
#pragma once

#include "IDelay.h"
#include "ITimeInterrupt.h"
#include "stm32l476xx.h"

namespace mcu::delay 
{
    using namespace hal::delay;

    /**
     * @brief Class holding functionality of hardware, blocking delay. 
     */
    class delay : public IDelay
    {
    public:
        explicit delay(std::shared_ptr<hal::timer::ITimer> blocker);

        
        /**
         * @brief Block program execution for specified number of us.
         * @param us block for .. [us]
         * @return result of execution
         */
        eError delayUs(uint32_t us) override final;
        
        /**
         * @brief Block program execution for specified number of ms.
         * @param ms block for .. [ms]
         * @return result of execution
         */
        eError delayMs(uint32_t ms) override final;

    private:

        /**
         * @brief Pointer to timer component with blocking functionality. 
         */
        std::shared_ptr<hal::timer::ITimer> mBlocker{nullptr};
    };
}  // namespace mcu::delay
