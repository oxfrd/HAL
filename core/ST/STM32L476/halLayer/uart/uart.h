//
// Created by oxford on 20.09.23.
//
#pragma once

#include "IUart.h"
#include "gpioAlternate.h"
#include "stm32l476xx.h"

namespace mcu::uart {

    using namespace hal::uart;
    
    /**
     * @brief Class holding functionality of uart output. 
     */
    class uart : public hal::uart::IUart
    {
    public:
        explicit uart(USART_TypeDef *uartRegs, std::shared_ptr<gpio::gpioAlternate> txPin, std::shared_ptr<gpio::gpioAlternate> rxPin, 
            eBaudrate baudrate);
        eError setBaudrate(eBaudrate speed) override;
        eError send(std::vector<std::uint8_t> sendMe) override;
        eError get() override;
    private:
        USART_TypeDef *m_regs;
        eBaudrate m_baudRate;
        std::shared_ptr<gpio::gpioAlternate> m_txPin; 
        std::shared_ptr<gpio::gpioAlternate> m_rxPin;
    
        eError setProperPinsFunctionality();
        eError enableClock(bool enable);
        eError enableTransmit(bool enable);
        eError enableReceive(bool enable);
        eError enableUART(bool enable);
    };
} // mcu::uart
