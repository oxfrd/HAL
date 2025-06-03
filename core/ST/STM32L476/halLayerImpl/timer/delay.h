//
// Created by oxford on 20.03.25.
//
#pragma once

#include "IDelay.h"
#include "ITimeInterrupt.h"
#include "stm32l476xx.h"

#include <functional>

namespace mcu::delay 
{
    using namespace hal::delay;

    /**
     * @brief Class holding functionality of delay. 
     */
    class delay : public IDelay
    {
    public:
        explicit delay(std::shared_ptr<hal::interrupt::ITimeInterrupt> interrupt);

        eError delayUs(uint32_t us) override final;
        eError delayMs(uint32_t ms) override final;
    private:
        std::shared_ptr<hal::interrupt::ITimeInterrupt> mInterrupt{nullptr};
    };
}  // namespace mcu::delay

#ifdef __cplusplus
extern "C" {
#endif
    __attribute__((interrupt)) void TIM2_IRQHandler();
#ifdef __cplusplus
}
#endif