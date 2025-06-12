#include "DS18B20.h"
#include <cassert>
#include <cstring>

namespace module
{
    DS18B20::DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire, std::shared_ptr<hal::delay::IDelay> delay):
    mOneWire(oneWire),
    mDelay(delay)
    {
        assert(mOneWire != nullptr);
        assert(mDelay != nullptr);
    }

    eError DS18B20::enable(bool reset)
    {
        auto err = mOneWire->reset();
        if (err != eError::eOk || (not reset))
        {
            return err;
        }
        return mOneWire->skipAdressing();
    }

    eError DS18B20::getTemperature(float* val)
    {
        auto err = enable(true);
        if (err != eError::eOk)
        {
            return err;
        }

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

        err = mOneWire->send(&cReadScratchpad, 1);
        if (err != eError::eOk)
        {
            return err;
        }
        
        std::uint8_t scratchPad[cScratchPadSize];

        err = mOneWire->get(scratchPad, cScratchPadSize);
        if (err != eError::eOk)
        {
            return err;
        }

        uint16_t temp{(uint16_t)scratchPad[0] | ((uint16_t)scratchPad[1] << 8)};
        *val = static_cast<float>(temp);
        *val /=16;

        return eError::eOk;
    }

    eError DS18B20::getAddress(uint64_t *address) 
    { 
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
        
        uint8_t rom_code[8];
        err = mOneWire->get(rom_code,8);
        if (err != eError::eOk)
        {
            return err;
        }

        std::memcpy(address, rom_code, sizeof(address));
        return err;
    }

}  // namespace module
