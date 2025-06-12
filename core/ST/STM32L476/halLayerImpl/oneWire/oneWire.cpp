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

    oneWire::oneWire(std::shared_ptr<hal::gpio::IGpioOutAndInput> pin, 
        std::shared_ptr<hal::delay::IDelay> delay):
    IOneWire(),
    mPin(pin),
    mDelay(delay)
    {
        assert(mPin != nullptr);
        assert(mDelay != nullptr);

        mPin->setSpeed(hal::gpio::eSpeed::eVeryHigh);
    }

    eError oneWire::reset()
    {
        uint8_t retries = cRetriesDuringReset;

        auto err = mPin->setPinMode(hal::gpio::eMode::eInput);
        if (err != eError::eOk)
            return err;

        do 
        {
            if (--retries == 0) 
            {
                return eError::eFail;
            }
            mDelay->delayUs(2);
        } 
        while (not mPin->getState());

        //critical section
        err = mPin->setPinMode(hal::gpio::eMode::eOutput);
        if (err != eError::eOk)
            return err;

        err = mPin->off();
        if (err != eError::eOk)
            return err;
        
        err = mDelay->delayUs(480);
        if (err != eError::eOk)
            return err;

        err = mPin->setPinMode(hal::gpio::eMode::eInput);
        if (err != eError::eOk)
            return err;

        err = mDelay->delayUs(70);
        if (err != eError::eOk)
            return err;

        bool retVal = not mPin->getState();
        //critical section stop
        err = mDelay->delayUs(410);
        if (err != eError::eOk)
            return err;

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
        if (err != eError::eOk)
            return err;

        for (uint8_t i = 0; i < 8; i++) 
        {
            err = writeByte(rom[i]);
            if (err != eError::eOk)
                return err;
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
        auto err{eError::eFail};
        for(uint16_t i = 0; i<len; i++)
        {
            err = writeByte(buff[i]);
            if (err != eError::eOk)
                return err;
        }
        return eError::eOk;
    }

    //
    // Write a bit. Port and bit is used to cut lookup time and provide
    // more certain timing.
    //
    eError oneWire::writeBit(bool bit)
    {
        auto err = mPin->setPinMode(hal::gpio::eMode::eOutput);
        if (err != eError::eOk)
            return err;

        if (bit) 
        {
            //critical section
            err = mPin->off();
            if (err != eError::eOk)
                return err;
            
            err = mDelay->delayUs(6);
            if (err != eError::eOk)
                return err;

            err = mPin->on();
            if (err != eError::eOk)
                return err;

            //critical section end
            return mDelay->delayUs(64);
        } else 
        {
            //critical section
            err = mPin->off();
            if (err != eError::eOk)
                return err;

            err = mDelay->delayUs(60);
            if (err != eError::eOk)
                return err;

            err = mPin->on();
            if (err != eError::eOk)
                return err;

            //critical section end
            return mDelay->delayUs(10);
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
        eError err{eError::eFail};

        for (uint8_t bitMask = 0x01; bitMask; bitMask <<= 1)
        {
            err = writeBit(bitMask & byte ? 1 : 0);
            if (err != eError::eOk)
                return err;
        }

        if (powerOff)
        {
            //critical section
            err = mPin->setPinMode(hal::gpio::eMode::eOutput);
            if (err != eError::eOk)
                return err;

            err = mPin->off();
            if (err != eError::eOk)
                return err;
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
            return retVal;

        if (mPin->off() != eError::eOk)
            return retVal;

        mDelay->delayUs(6);

        if (mPin->on() != eError::eOk)
            return retVal;

        mDelay->delayUs(9);

        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
            return retVal;

        retVal = mPin->getState();

        //TODO: critical section stop

        mDelay->delayUs(55);
        return retVal;
    }
}
