//
// Created by oxford on 20.09.23.
//

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "IGpio.h"
#include "../../../../core/ST/STM32L476/Include/stm32l476xx.h"
#include "components/gpio/IPort.h"

namespace hal {
    namespace gpio {

        class gpioOutput : public IGpioOutput, IGpioInit
        {
        public:
            explicit gpioOutput(std::uint8_t portId);
            error off() override;
            error on() override;
            error setMode(eMode mode) override;
            error setTermination(eTermination type) override;
            error lockConfiguration() override;
        private:
            hal::gpio::IPort m_port;
        };

    } // hal
} // gpio

#endif //HAL_GPIO_H
