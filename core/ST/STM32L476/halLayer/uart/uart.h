//
// Created by oxford on 20.09.23.
//
#pragma once

#include "IUart.h"
#include "interrupt.h"
#include "gpioAlternate.h"
#include "stm32l476xx.h"
#include "circularBuffer.h"

namespace mcu::uart {

    using namespace hal::uart;
    
    /**
     * @brief Class holding functionality of uart output. 
     */
    class uart : public IUart
    {
    public:
        explicit uart(USART_TypeDef *uartRegs, std::shared_ptr<gpio::gpioAlternate> txPin, 
                std::shared_ptr<gpio::gpioAlternate> rxPin, 
                std::shared_ptr<interrupt::interrupt> interrupt, 
                eBaudrate baudrate = eBaudrate::e9600);
        eError setBaudrate(eBaudrate speed) override;
        eError send(uint8_t *sendMe, uint16_t len) override;
        eError sendVector(std::vector<std::uint8_t> sendMe) override; 

        eError get(uint8_t *buff, uint16_t len) override;
    private:
        static constexpr size_t cTxBufferSize{1000};
        static constexpr size_t cRxBufferSize{1000};

        USART_TypeDef *mRegs;
        eBaudrate mBaudRate;
        std::shared_ptr<gpio::gpioAlternate> mTxPin; 
        std::shared_ptr<gpio::gpioAlternate> mRxPin;
        std::shared_ptr<interrupt::interrupt> mInterrupt;
        
        circularBuffer mTxBuff;
        circularBuffer mRxBuff;
        
        eError setProperPinsFunctionality();
        eError enableClock(bool enable);
        eError enableTransmit(bool enable);
        eError enableReceive(bool enable);
        eError enableUART(bool enable);
        eError giveBuffer();
        eError enableTxInterrupts(bool enable);
        eError enableRxInterrupts(bool enable); 

    };
} // mcu::uart

#ifdef __cplusplus
 extern "C" {
#endif
    __attribute__((interrupt)) void USART2_IRQHandler(void);
#ifdef __cplusplus
}
#endif
