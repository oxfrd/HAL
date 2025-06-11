#include "DS18B20.h"
#include <cassert>
#include <cstring>

namespace module
{
    DS18B20::DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire)
    {
        assert(mOneWire != nullptr);
    }

    eError DS18B20::enable(bool enable)
    {
        auto err = mOneWire->reset();
        if (err != eError::eOk)
        {
            return err;
        }
        return mOneWire->skipAdressing();
    }

    eError DS18B20::getTemperature(float* val)
    {

        return eError::eUninitialized;
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
