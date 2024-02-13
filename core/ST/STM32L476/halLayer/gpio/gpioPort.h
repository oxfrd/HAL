//
// Created by oxford on 30.09.23.
//
#pragma once 

#include "stm32l476xx.h"

#include <cstdint>
#include "IPort.h"

namespace mcu::gpio {

    class gpioPort : public hal::gpio::IPort
    {
    public:
        explicit gpioPort(std::uint8_t portId);
        eError enableClk() override;
        eError disableClk() override;
    private:
        //reg specific, should be abstracted in future
        static constexpr uint32_t cPortSizeInMem = 0x400;
        static constexpr std::uint32_t cPeriphBaseOffset = AHB2PERIPH_BASE;
        volatile std::uint32_t *m_RCCEnReg = &(RCC->AHB2ENR);

        std::uint8_t m_id;

    };

}   //namespace mcu::gpio
