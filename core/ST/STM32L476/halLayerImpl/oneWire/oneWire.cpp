//
// Created by oxford on 19.03.25
//

#include "oneWire.h"
#include <cassert>


namespace mcu::oneWire
{
    using namespace hal::oneWire;

    oneWire::oneWire(std::shared_ptr<gpio::gpioOutAndInput> pin):
    IOneWire()
    {
        if(pin == nullptr)
        {
            assert(0);
        }
        mPin = pin; 
        mPin->setSpeed(hal::gpio::eSpeed::eVeryHigh);
    }

    eError oneWire::get(uint8_t *buff, uint16_t len) 
    {
        for(uint16_t i = 0; i<len; i++)
        {
            // if (not mRxBuff.pop(buff))
            // {
            //     return eError::eEmpty;
            // }
        }
        return eError::eOk;
    }

    eError oneWire::readBit(uint8_t *data)
    {
        //TODO: critical section start
        if (mPin->setPinMode(hal::gpio::eMode::eOutput) != eError::eOk)
        {
            assert(0);
            return eError::eFail;
        }

        if (mPin->off() != eError::eOk)
        {
            assert(0);
            return eError::eFail;
        }

        // delayUs(3);

        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
        {
            assert(0);
            return eError::eFail;
        }

        // delayUs(10);

        *data = mPin->getState();

        //TODO: critical section stop

        // delayUs(53);
        return eError::eOk;
    }
}
