//
// Created by oxford on 19.03.25.
//
#pragma once

#include "stm32l476xx.h"
#include "IOneWire.h"
#include "interrupt.h"
#include "gpioOutAndInput.h"
#include "circularBuffer.h"

namespace mcu::oneWire {

    using namespace hal::oneWire;
    
    constexpr std::uint8_t cAllI2cInstances{3};

    /**
     * @brief Class holding functionality of one wire. 
     */
    class oneWire : public IOneWire
    {
    public:
        explicit oneWire(std::shared_ptr<gpio::gpioOutAndInput> pin);
    
        eError get(uint8_t *buff, uint16_t len);
    
    private:
        eError oneWire::readBit(uint8_t *data);
    



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
        std::shared_ptr<gpio::gpioOutAndInput> mPin; 
        
        eError enableI2c(bool enable);
        eError enableClock(bool enable);
        eError setProperPinsFunctionality();
        eError enableTransmit(bool enable);
        eError enableReceive(bool enable);
        eError enableTxInterrupts(bool enable);
        eError enableRxInterrupts(bool enable); 
        eError giveBuffer();
        eError waitForFlag(uint32_t flag, bool notNegate);
    };
} // mcu::i2c

#ifdef __cplusplus
 extern "C" {
#endif
    __attribute__((interrupt)) void I2C1_EV_IRQHandler(void* arg);
#ifdef __cplusplus
}
#endif
