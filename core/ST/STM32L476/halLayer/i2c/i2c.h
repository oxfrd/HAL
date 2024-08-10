//
// Created by oxford on 10.06.24.
//
#pragma once

#include "stm32l476xx.h"
#include "II2c.h"
#include "interrupt.h"
#include "gpioAlternate.h"
#include "circularBuffer.h"

namespace mcu::i2c {

    using namespace hal::i2c;
    
    constexpr std::uint8_t cAllI2cInstances{3};

    /**
     * @brief Class holding functionality of i2c output. 
     */
    class I2c : public II2c
    {
    public:
        explicit I2c(I2C_TypeDef *i2cRegs, std::shared_ptr<gpio::gpioAlternate> clkPin,
                std::shared_ptr<gpio::gpioAlternate> sdaPin,
                std::shared_ptr<interrupt::interrupt> interrupt,
                eSpeedMode speed = eSpeedMode::eStd);
        eError setSpeed(eSpeedMode speed) override;
        eError send(std::uint8_t addr, uint8_t *sendMe, uint16_t len) override;
        eError sendVector(std::uint8_t addr, std::vector<std::uint8_t> sendMe) override; 
        eError get(std::uint8_t addr, std::uint8_t reg, uint8_t *buff, uint16_t len) override;
    private:
        static constexpr size_t cTxBufferSize{1000};
        static constexpr size_t cRxBufferSize{1000};
        static constexpr std::uint16_t cLoopReplaysLimit{1000};

        I2C_TypeDef *mRegs;
        eSpeedMode mSpeedMode;
        std::shared_ptr<gpio::gpioAlternate> mClkPin; 
        std::shared_ptr<gpio::gpioAlternate> mSdaPin;
        std::shared_ptr<interrupt::interrupt> mInterrupt;
        
        circularBuffer mTxBuff;
        circularBuffer mRxBuff;
        
        eError enableI2c(bool enable);
        eError enableClock(bool enable);
        eError setProperPinsFunctionality();
        eError enableTransmit(bool enable);
        eError enableReceive(bool enable);
        eError enableTxInterrupts(bool enable);
        eError enableRxInterrupts(bool enable); 
        eError giveBuffer();
    };
} // mcu::i2c

#ifdef __cplusplus
 extern "C" {
#endif
    __attribute__((interrupt)) void I2C1_EV_IRQHandler(void);
#ifdef __cplusplus
}
#endif
