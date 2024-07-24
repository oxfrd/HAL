#include "ILightSensor.h"
#include "BMP280.h"
#include <cassert>

namespace module
{
    BMP280::BMP280(std::shared_ptr<hal::i2c::II2c> i2cHandle, std::uint8_t addr):
    mI2c{i2cHandle},
    mI2cAddress{addr}
    {
        assert(mI2c == nullptr);
    }

    eError BMP280::enable(bool enable) 
    {
        return eError::eUninitialized;
    }

    eError BMP280::getValue(float* valkPa)
    {
        return eError::eUninitialized;
    }

    std::uint8_t BMP280::readU8()
    {   
        std::uint8_t sign{0};
        mI2c->get(mI2cAddress, &sign, 1);
        return sign;
    }

    std::uint16_t BMP280::readU16()
    {
        uint8_t buff[2];
        if (mI2c->get(mI2cAddress,buff, 2) != eError::eOk)
        {
            return 0;
        }
        return ((buff[0] << 8) | buff[1]);
    }

    std::uint16_t BMP280::readU16LE()
    {
        uint16_t tmp = BMP280::readU16();
        return (tmp >> 8) | (tmp << 8);
    }

    bool BMP280::writeU8(uint8_t data)
    {
        if (mI2c->send(mI2cAddress, &data, 1) != eError::eOk)
        {
            return false;
        }
        return true;
    }

    std::uint32_t BMP280::readU24()
    {
        uint8_t buff[3];
        if (mI2c->get(mI2cAddress, buff, 3) != eError::eOk)
        {
            return 0;
        }
        return ((buff[0] << 16) | buff[1] << 8 | buff[2]);
    }
}

