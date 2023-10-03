//
// Created by oxford on 30.09.23.
//
#include "stm32l476xx.h"

#include <cstdint>
#include "IPort.h"

namespace mcu::gpio {

    class port : public hal::gpio::IPort<GPIO_TypeDef> {
    public:
        explicit port(GPIO_TypeDef *portId);

    protected:
        error enableClk() override;
        error disableClk() override;
    private:
        //reg specific, should be abstracted in future
        static constexpr uint32_t cPortSizeInMem = 0x400;
        static constexpr std::uint32_t cPeriphBaseOffset = AHB2PERIPH_BASE;
        volatile std::uint32_t *m_RCCEnReg = &(RCC->AHB2ENR);

        GPIO_TypeDef *m_regs{};
        std::uint32_t m_id;

    };

}   //namespace mcu::gpio
