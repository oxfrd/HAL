#include "DS18B20.h"
#include <cassert>

namespace module
{
    DS18B20::DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire)
    {
        if (oneWire == nullptr)
        {
            while (1)
            {
                asm("NOP");
            }
        }
        mOneWire = oneWire;
    }

    eError DS18B20::enable(bool enable)
    {
        if (mOneWire->reset() == eError::eBusy)
        {
            return eError::eBusy;
        }
        return mOneWire->skipAdressing();
    }

    eError DS18B20::getTemperature(float* val)
    {

        return eError::eUninitialized;
    }

    eError DS18B20::getAddress(uint64_t *address) 
    { 
        return eError::eUninitialized;
    }

}  // namespace module
