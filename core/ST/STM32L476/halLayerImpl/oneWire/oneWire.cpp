//
// Created by oxford on 19.03.25
//
#include <cassert>
#include <chrono>

#include "oneWire.h"


namespace mcu::oneWire
{
    using namespace hal::oneWire;
    using namespace std::chrono_literals;

    oneWire::oneWire(std::shared_ptr<gpio::gpioOutAndInput> pin, 
        std::shared_ptr<hal::delay::IDelay> delay):
    IOneWire()
    {
        if(pin == nullptr)
        {
            assert(0);
        }
        mPin = pin; 
        mPin->setSpeed(hal::gpio::eSpeed::eVeryHigh);
        
        if(delay == nullptr)
        {
            assert(0);
        }
        mDelay = delay;
    }

    eError oneWire::reset()
    {
        uint8_t retries = cRetriesDuringReset;

        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
        {
            assert(0);
            return eError::eUninitialized;
        }

        do 
        {
            if (--retries == 0) 
            {
                return eError::eFail;
            }
            mDelay->delayUs(2us);
        } 
        while (not mPin->getState());

        //critical section
        if (mPin->setPinMode(hal::gpio::eMode::eOutput) != eError::eOk)
        {
            assert(0);
            return eError::eUninitialized;
        }
        mPin->off();

        mDelay->delayUs(480us);
        
        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
        {
            assert(0);
            return eError::eUninitialized;
        }
        mDelay->delayUs(70us);
        
        uint8_t retVal = not mPin->getState();
        //critical section stop
        mDelay->delayUs(410us);

        if(retVal)
        {
            return eError::eOk;
        }
        else
        {
            return eError::eBusy;
        }
    }

    eError oneWire::selectDevice(const uint8_t rom[8])
    {
        auto err = writeByte(0x55);

        for (uint8_t i = 0; i < 8; i++) 
        {
            if (writeByte(rom[i]) != eError::eOk);
            {
                return eError::eFail;
            }
        }
        return eError::eOk;
    }

    eError oneWire::skipAdressing()
    {
        return writeByte(0xCC);
    }

    eError oneWire::get(uint8_t *buff, const uint16_t len) 
    {
        for(uint16_t i = 0; i<len; i++)
        {
            buff[i] = readByte();
        }
        return eError::eOk;
    }

    eError oneWire::send(const uint8_t *buff, const uint16_t len) 
    {
        for(uint16_t i = 0; i<len; i++)
        {
            writeByte(buff[i]);
        }
        return eError::eOk;
    }

    //
    // Write a bit. Port and bit is used to cut lookup time and provide
    // more certain timing.
    //
    eError oneWire::writeBit(bool bit)
    {
        if (bit) 
        {
            //critical section
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
            
            mDelay->delayUs(10us);
            if (mPin->setPinMode(hal::gpio::eMode::eOutput) != eError::eOk)
            {
                assert(0);
                return eError::eFail;
            }

            if (mPin->on() != eError::eOk)
            {
                assert(0);
                return eError::eFail;
            }
            //critical section end
            return mDelay->delayUs(55us);
        } else 
        {
            //critical section
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

            mDelay->delayUs(65us);

            if (mPin->off() != eError::eOk)
            {
                assert(0);
                return eError::eFail;
            }
            //critical section end
            return mDelay->delayUs(5us);
        }
    }

    /*
    * Write a byte. The writing code uses the active drivers to raise the
    * pin high.
    * @param byte - bytes to write
    * @param powerOff - set false if you need power after the write (e.g. DS18S20 in
    *           parasite power mode) otherwise the pin will go tri-state 
    *           at the end of the write to avoid heating
    * @return state of operation 
    */
    eError oneWire::writeByte(uint8_t byte, bool powerOff) 
    {
        for (uint8_t bitMask = 0x01; bitMask; bitMask <<= 1)
        {
            if (writeBit((bitMask & byte) ? 1 : 0) != eError::eOk)
            {
                return eError::eFail;
            }
        }

        if (powerOff)
        {
            //critical section
            if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
            {
                assert(0);
                return eError::eFail;
            }

            if (mPin->off() != eError::eOk)
            {
                assert(0);
                return eError::eFail;
            }
            //critical section end
        }
        return eError::eOk;
    }

    uint8_t oneWire::readByte()
    {
        uint8_t byte = 0;

        for (uint8_t bitMask = 0x01; bitMask > 0; bitMask <<= 1) 
        {
            if (oneWire::readBit()) 
            {
                byte |= bitMask;
            }
        }
        return byte;
    }

    bool oneWire::readBit()
    {
        bool retVal{false};

        //TODO: critical section start
        if (mPin->setPinMode(hal::gpio::eMode::eOutput) != eError::eOk)
        {
            assert(0);
            return retVal;
        }

        if (mPin->off() != eError::eOk)
        {
            assert(0);
            return retVal;
        }

        mDelay->delayUs(3us);

        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
        {
            assert(0);
            return retVal;
        }

        mDelay->delayUs(10us);

        retVal = mPin->getState();

        //TODO: critical section stop

        mDelay->delayUs(53us);
        return retVal;
    }
}
