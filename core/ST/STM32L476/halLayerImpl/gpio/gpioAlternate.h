//
// Created by oxford on 28.04.24.
//
#pragma once

#include "stm32l476xx.h"
#include "components/gpio/IPort.h"
#include "IGpioAlternate.h"
#include "gpioPort.h"

namespace mcu::gpio {
    
    enum class eFunctionality 
    {
        eSYS_AF,
        eTIM1_2_5_8_LPTIM1,
        eTIM1_2_3_4_5,
        eTIM8,
        eI2C1_2_3,
        eSPI1_2,
        eSPI3_DFSDM,
        eUART1_2_3,
        eUART4_5_LPUART1,
        eCAN1_TSC,
        eOTG_FS_QUADSPI,
        eLCD,
        eAF12,
        eSAI1_2,
        eTIM2_15_16_17_LPTIM2,
        eLastIdx_EVENTOUT,
    };
    using namespace hal::gpio;
    
    /**
     * @brief Class holding functionality of gpio alternate function. 
     */
    class gpioAlternate : public hal::gpio::IGpioAlternate
    {
    public:
        explicit gpioAlternate(std::uint32_t pinId, std::shared_ptr<gpioPort> port);
        eError setFunctionality(std::uint32_t fun) override final;
    private:
        //reg specific, should be abstracted in future
        static constexpr std::uint32_t cLastPinInAFR0{7};
        std::shared_ptr<mcu::gpio::gpioPort> m_port;
        GPIO_TypeDef *m_regs;
        std::uint32_t m_pinId;
    };
} // mcu::gpio
