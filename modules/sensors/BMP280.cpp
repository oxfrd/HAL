#include "ILightSensor.h"
#include "BMP280.h"
#include <cassert>

namespace module
{
    BMP280::BMP280(std::shared_ptr<hal::i2c::II2c> i2cHandle, std::uint8_t addr):
    mI2c{i2cHandle},
    mI2cAddress{addr}
    {
        if (i2cHandle == nullptr)
        {
            while (1)
            {
                asm("NOP");
            }
        }
        
        mI2c = i2cHandle;
        if (mI2c.get() == nullptr)
        {
            while (1)
            {
                asm("NOP");
            }
        }
        init();
    }

    eError BMP280::init()
    {
        while(readU8(Bmp280::cChipId) != 0x58);
        /* read calibration data */
        mCalibT1 = readU16LE(Bmp280::cDIG_T1);
        mCalibT[0] = readU16LE(Bmp280::cDIG_T2);
        mCalibT[1] = readU16LE(Bmp280::cDIG_T3);
        mCalibP1 = readU16LE(Bmp280::cDIG_P1);
        mCalibP[0] = readU16LE(Bmp280::cDIG_P2);
        mCalibP[1] = readU16LE(Bmp280::cDIG_P3);
        mCalibP[2] = readU16LE(Bmp280::cDIG_P4);
        mCalibP[3] = readU16LE(Bmp280::cDIG_P5);
        mCalibP[4] = readU16LE(Bmp280::cDIG_P6);
        mCalibP[5] = readU16LE(Bmp280::cDIG_P7);
        mCalibP[6] = readU16LE(Bmp280::cDIG_P8);
        mCalibP[7] = readU16LE(Bmp280::cDIG_P9);
        std::uint8_t ctrl = ((static_cast<std::uint8_t>(Bmp280::eTemperatureOversampling::eX1) << 5) 
                | (static_cast<std::uint8_t>(Bmp280::ePressureOversampling::eStandard)<<2)) 
                | (static_cast<std::uint8_t>(Bmp280::eMode::eNormal));
        writeU8(Bmp280::cControl, ctrl);
        mMode = Bmp280::eMode::eForced;
        return eError::eOk; 
    }

    eError BMP280::enable(bool enable) 
    {
        return eError::eUninitialized;
    }

    eError BMP280::getValue(float* valkPa)
    {

        int64_t var1, var2, p;
        // Must be done first to get the t_fine variable set up
        getTemperature(valkPa);
        // *valkPa = readU8(Bmp280::cStatus);   

        // int32_t adc_P = readU24(PRESSUREDATA);
        // adc_P >>= 4;

        // var1 = ((int64_t)t_fine) - 128000;
        // var2 = var1 * var1 * (int64_t)p6;
        // var2 = var2 + ((var1*(int64_t)p5)<<17);
        // var2 = var2 + (((int64_t)p4)<<35);
        // var1 = ((var1 * var1 * (int64_t)p3)>>8) +
        //     ((var1 * (int64_t)p2)<<12);
        // var1 = (((((int64_t)1)<<47)+var1))*((int64_t)p1)>>33;

        // if (var1 == 0) {
        //     return 0;  // avoid exception caused by division by zero
        // }
        // p = 1048576 - adc_P;
        // p = (((p<<31) - var2)*3125) / var1;
        // var1 = (((int64_t)p9) * (p>>13) * (p>>13)) >> 25;
        // var2 = (((int64_t)p8) * p) >> 19;

        // p = ((p + var1 + var2) >> 8) + (((int64_t)p7)<<4);
        // return (int32_t)p/256;
        return eError::eOk;
    }

    eError BMP280::getChipId(std::uint32_t* val) 
    {
        *val = readU8(Bmp280::cChipId);   
        return eError::eOk;
    }

    eError BMP280::getTemperature(float *val) 
    {
        int32_t adc_T = readU24(Bmp280::cTempData);
        adc_T >>= 4;

        int32_t var1  = ((((adc_T>>3) - ((int32_t)mCalibT1 <<1))) *
                ((int32_t)mCalibT[0])) >> 11;

        int32_t var2  = (((((adc_T>>4) - ((int32_t)mCalibT1)) *
                ((adc_T>>4) - ((int32_t)mCalibT1))) >> 12) *
                ((int32_t)mCalibT[1])) >> 14;

        int32_t t_fine = var1 + var2;

        int32_t T  = (t_fine * 5 + 128) >> 8;
        *val = ((float)T/100);
        return eError::eOk;
    }

    std::uint8_t BMP280::readU8(std::uint8_t reg)
    {   
        std::uint8_t sign{0};
        mI2c->get(mI2cAddress, reg, &sign, 1);
        return sign;
    }

    std::uint16_t BMP280::readU16(std::uint8_t reg)
    {
        uint8_t buff[2];
        if (mI2c->get(mI2cAddress, reg, buff, 2) != eError::eOk)
        {
            return 0;
        }
        return ((buff[0] << 8) | buff[1]);
    }

    std::uint16_t BMP280::readU16LE(std::uint8_t reg)
    {
        uint16_t tmp = BMP280::readU16(reg);
        return (tmp >> 8) | (tmp << 8);
    }

    bool BMP280::writeU8(std::uint8_t reg, std::uint8_t data)
    {
        std::uint8_t sendMe[2] = {reg, data};
        if (mI2c->send(mI2cAddress, sendMe, 2) != eError::eOk)
        {
            return false;
        }
        return true;
    }

    std::uint32_t BMP280::readU24(std::uint8_t reg)
    {
        uint8_t buff[3]{0,0,0};
        if (mI2c->get(mI2cAddress, reg, buff, 3) != eError::eOk)
        {
            return 0;
        }
        return ((buff[0] << 16) | buff[1] << 8 | buff[2]);
    }
}

