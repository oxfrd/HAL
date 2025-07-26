#include "24Cxx.h"
#include <cassert>

namespace e24Cxx
{
    e24Cxx::e24Cxx(std::shared_ptr<hal::i2c::II2c> i2cHandle, uint32_t address):
    mI2c{i2cHandle},
    mI2cAddress(address)
    {
        assert(mI2c != nullptr);
    }

    eError e24Cxx::write(uint32_t offset, uint8_t *data , size_t length)
    {
        uint8_t memAddr = static_cast<uint8_t>(offset & 0xFF);

        auto err = mI2c->send(mI2cAddress, &memAddr, 1);
        if(err != eError::eOk)
            return err;

        return mI2c->send(mI2cAddress, data, length); 
    }

    eError e24Cxx::read(uint32_t offset, uint8_t *data , size_t length)
    {
        return eError::eUninitialized;
    }

    eError e24Cxx::getAddress(uint32_t *address)
    {
        return eError::eUninitialized;
    }

    eError e24Cxx::getSize(uint32_t *size)
    {
        return eError::eUninitialized;
    }

}

