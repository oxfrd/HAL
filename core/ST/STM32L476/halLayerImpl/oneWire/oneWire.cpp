//
// Created by oxford on 19.03.25
//
#include <cassert>
#include <chrono>

#include "oneWire.h"
#include <cstring>

#pragma GCC optimize ("O0")

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

        mDelay->delayUs(5);

        if (mPin->on() != eError::eOk)
            return retVal;

        mDelay->delayUs(5);

        if (mPin->setPinMode(hal::gpio::eMode::eInput) != eError::eOk)
            return retVal;

        retVal = mPin->getState();

        //TODO: critical section stop

        mDelay->delayUs(45);
        return retVal;
    }

    eError oneWire::scanNetwork(uint8_t *p)//std::vector<OneWireAddress>& foundDevices) 
    {
        // std::vector<uint8_t[8]> devs;
        uint8_t intimbecyl = 0;
        uint8_t newAddr[8];
        reset_search();

        while (search(newAddr))
        {
            intimbecyl++;
            asm("NOP");
        }
        memcpy(p,newAddr,8);

        return (eError)intimbecyl;
    }


    unsigned char mROM_NO[8];
    uint8_t mLastDiscrepancy;
    uint8_t mLastFamilyDiscrepancy;
    uint8_t mLastDeviceFlag;

    //
    // You need to use this function to start a search again from the beginning.
    // You do not need to do it for the first search, though you could.
    //
    void oneWire::reset_search()
    {
        // reset the search state
        mLastDiscrepancy = 0;
        mLastDeviceFlag = false;
        mLastFamilyDiscrepancy = 0;
        std::memset(mROM_NO, 0, 8);
    }

    // Setup the search to find the device type 'family_code' on the next call
    // to search(*newAddr) if it is present.
    //
    void oneWire::target_search(uint8_t family_code)
    {
    // set the search state to find SearchFamily type devices
        mROM_NO[0] = family_code;
        std::memset(mROM_NO, 0, 8);
        mLastDiscrepancy = 64;
        mLastFamilyDiscrepancy = 0;
        mLastDeviceFlag = false;
    }

//
// Perform a search. If this function returns a '1' then it has
// enumerated the next device and you may retrieve the ROM from the
// OneWire::address variable. If there are no devices, no further
// devices, or something horrible happens in the middle of the
// enumeration then a 0 is returned.  If a new device is found then
// its address is copied to newAddr.  Use OneWire::reset_search() to
// start over.
//
// --- Replaced by the one from the Dallas Semiconductor web site ---
//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
// Return true  : device found, ROM number in mROM_NO buffer
//        false : device not found, end of search
//
uint8_t oneWire::search(uint8_t *newAddr)
{
    uint8_t id_bit_number = 1;
    uint8_t last_zero = 0;
    uint8_t rom_byte_number = 0;
    uint8_t search_result = 0;
    uint8_t id_bit =0;
    uint8_t cmp_id_bit= 0;
    uint8_t buffer[60];
    memset(buffer, 0, 60);


    unsigned char rom_byte_mask = 0;
    unsigned char search_direction = 0;

    // if the last call was not the last one
    if (!mLastDeviceFlag)
    {
        // 1-Wire reset
        if (eError::eOk != reset())
        {
            // reset the search
            mLastDiscrepancy = 0;
            mLastDeviceFlag = false;
            mLastFamilyDiscrepancy = 0;
            return false;
        }

        // issue the search command
        writeByte(0xF0);

        // loop to do the search
        do
        {
            // read a bit and its complement
            id_bit = readBit();
            cmp_id_bit = readBit();

            // check for no devices on 1-wire
            if ((id_bit == 1) && (cmp_id_bit == 1))
            {
                break;
            }
            else
            {
                // all devices coupled have 0 or 1
                if (id_bit != cmp_id_bit)
                {
                    search_direction = id_bit;  // bit write value for search
                }
                else
                {
                    // if this discrepancy if before the Last Discrepancy
                    // on a previous next then pick the same as last time
                    if (id_bit_number < mLastDiscrepancy)
                    {
                        search_direction = ((mROM_NO[rom_byte_number] & rom_byte_mask) > 0);
                    }
                    else
                    {
                        // if equal to last pick 1, if not then pick 0
                        search_direction = (id_bit_number == mLastDiscrepancy);
                    }

                    // if 0 was picked then record its position in LastZero
                    if (search_direction == 0)
                    {
                        last_zero = id_bit_number;

                        // check for Last discrepancy in family
                        if (last_zero < 9)
                        {
                            mLastFamilyDiscrepancy = last_zero;
                        }
                    }
                }

                // set or clear the bit in the ROM byte rom_byte_number
                // with mask rom_byte_mask
                if (search_direction == 1)
                {
                    mROM_NO[rom_byte_number] |= rom_byte_mask;
                }
                else
                {
                    mROM_NO[rom_byte_number] &= ~rom_byte_mask;
                }

                // serial number search direction write bit
                writeByte(search_direction);

                // increment the byte counter id_bit_number
                // and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;

                // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
                if (rom_byte_mask == 0)
                {
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        }
        while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

        // if the search was successful then
        if (!(id_bit_number < 65))
        {
            // search successful so set mLastDiscrepancy,mLastDeviceFlag,search_result
            mLastDiscrepancy = last_zero;

            // check for last device
            if (mLastDiscrepancy == 0)
                mLastDeviceFlag = true;

            search_result = true;
        }
    }

    // if no device found then reset counters so next 'search' will be like a first
    if (!search_result || !mROM_NO[0])
    {
        mLastDiscrepancy = 0;
        mLastDeviceFlag = false;
        mLastFamilyDiscrepancy = 0;
        search_result = false;
    }

    for (int i = 0; i < 8; i++) 
    {
        newAddr[i] = mROM_NO[i];
    }

    return search_result;
}


}
