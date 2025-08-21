#include "DS18B20.h"
#include <cassert>
#include <cstring>

namespace module
{
    DS18B20::DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire, std::shared_ptr<hal::delay::IDelay> delay, const uint8_t *adress):
    mOneWire(oneWire),
    mDelay(delay)
    {
        assert(mOneWire != nullptr);
        assert(mDelay != nullptr);
        
        if (adress != nullptr)
        {
            memcpy(mAdress, adress, cAdressBytesCnt);
            mAdress[7] = crc8(mAdress, 7);
            mAdressingMode = cNotSkipAdressing;
        }
        else
        {
            uint64_t notUsed;
            getAddress(&notUsed);
            mAdressingMode = cSkipAdressing;
        }
    }

    eError DS18B20::enable(bool reset)
    {
        auto err = mOneWire->reset();
        if (err != eError::eOk || (not reset))
        {
            return err;
        }
        
        return mOneWire->send(&mAdressingMode, 1);
    }

    eError DS18B20::getTemperature(float* val)
    {
        auto err = enable(true);
        if (err != eError::eOk)
        {
            return err;
        }

        sendAddress();

        err = mOneWire->send(&cConvertTemperature, 1);
        if (err != eError::eOk)
        {
            return err;
        }

        err = mDelay->delayMs(cTemperatureReadTimeout);
        if (err != eError::eOk)
        {
            return err;
        }

        err = enable(true);
        if (err != eError::eOk)
        {
            return err;
        }

        sendAddress();

        err = mOneWire->send(&cReadScratchpad, 1);
        if (err != eError::eOk)
        {
            return err;
        }

        err = mOneWire->get(mScratchPad, cScratchPadSize);
        if (err != eError::eOk)
        {
            return err;
        }

        uint16_t temp{(uint16_t)mScratchPad[0] | ((uint16_t)mScratchPad[1] << 8)};
        *val = static_cast<float>(temp);
        *val /=16;
        if (*val > cMaxValidMeasurement)
        {
            return eError::eFail;
        }
        
        return eError::eOk;
    }

    eError DS18B20::getAddress(uint64_t *address) 
    { 
        if (mAdressingMode == cNotSkipAdressing)
        {
            memcpy(address, mAdress, sizeof(*address));
            return eError::eOk;
        }

        auto err = mOneWire->reset();
        if (err != eError::eOk)
        {
            return err;
        }

        err = mOneWire->send(&cReadROM,1);
        if (err != eError::eOk)
        {
            return err;
        }
        
        err = mOneWire->get(mAdress, cAdressBytesCnt);
        if (err != eError::eOk)
        {
            return err;
        }

        std::memcpy(address, mAdress, sizeof(*address));
        return err;
    }

    eError DS18B20::sendAddress()
    {
        eError err = eError::eOk;
        if (mAdressingMode == cNotSkipAdressing)
        {
            err = mOneWire->send(mAdress, cAdressBytesCnt);
        }
        return err;
    }

    uint8_t DS18B20::crc8( uint8_t *addr, uint8_t len)
    {
        uint8_t crc = 0;
        
        while (len--) {
            uint8_t inbyte = *addr++;
            for (uint8_t i = 8; i; i--) {
                uint8_t mix = (crc ^ inbyte) & 0x01;
                crc >>= 1;
                if (mix) crc ^= 0x8C;
                inbyte >>= 1;
            }
        }
        return crc;
    }

}  // namespace module
