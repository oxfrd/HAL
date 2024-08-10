//
// Created by oxford on 02.07.24.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include <memory>
#include "IPressureSensor.h"
#include <II2c.h>
#include <functional>

namespace module
{
    namespace Bmp280
    {
        enum class eTemperatureOversampling
        {
            eSkipped = 0,
            eX1,
            eX2,
            eX4,
            eX8,
            eX16,
        };

        enum class ePressureOversampling
        {
            eUltraLowPower = 1,
            eLowPower,
            eStandard,
            eHighRes,
            eUltraHighRes,
        };

        enum class eStandbyTime
        {
            MS_0_5,
            MS_62_5,
            MS_125,
            MS_250,
            MS_500,
            MS_1000,
            MS_10,
            MS_20,
        };

        enum class eIIRFilter
        {
            OFF,
            X2,
            X4,
            X8,
            X16,
        };

        enum class eMode
        {
            eSleep,
            eForced,
            eForcedToo,
            eNormal,
            eUnInit_UnsettableAtDevice = 100,
        };

        //	Coeff registers
        constexpr std::uint8_t cDIG_T1 {0x88};
        constexpr std::uint8_t cDIG_T2 {0x8A};
        constexpr std::uint8_t cDIG_T3 {0x8C};

        constexpr std::uint8_t cDIG_P1 {0x8E};
        constexpr std::uint8_t cDIG_P2 {0x90};
        constexpr std::uint8_t cDIG_P3 {0x92};
        constexpr std::uint8_t cDIG_P4 {0x94};
        constexpr std::uint8_t cDIG_P5 {0x96};
        constexpr std::uint8_t cDIG_P6 {0x98};
        constexpr std::uint8_t cDIG_P7 {0x9A};
        constexpr std::uint8_t cDIG_P8 {0x9C};
        constexpr std::uint8_t cDIG_P9 {0x9E};

        // Registers
        constexpr std::uint8_t cChipId		{0xD0};
        constexpr std::uint8_t cVersion		{0xD1};
        constexpr std::uint8_t cSoftReset	{0xE0};
        constexpr std::uint8_t cCal26		{0xE1};
        constexpr std::uint8_t cStatus		{0xF3};
        constexpr std::uint8_t cControl		{0xF4};
        constexpr std::uint8_t cConfig		{0xF5};
        constexpr std::uint8_t cPressureData{0xF7};
        constexpr std::uint8_t cTempData	{0xFA};

        constexpr std::uint8_t cMeasuring (1<<3); // Conversion in progress
    } //namespace Bmp280
    class BMP280 : public hal::sensor::IPressureSensor
    {
    public:
        BMP280(std::shared_ptr<hal::i2c::II2c> i2cHandle, std::uint8_t addr = cDefaultAdrr);
        eError enable(bool enable) override;
        eError getPressure(float *valPa) override;
        eError getTemperature(float *val) override;
    private:
        static constexpr std::uint8_t cDefaultAdrr{0xEC};
        Bmp280::eMode mMode{Bmp280::eMode::eUnInit_UnsettableAtDevice};
        std::uint16_t mCalibT1;
        std::int16_t mCalibT[2];
        std::uint16_t mCalibP1;
        std::int16_t mCalibP[9];
        std::int32_t mTFine;
        std::shared_ptr<hal::i2c::II2c> mI2c{nullptr};
        std::uint8_t mI2cAddress{0};

        eError init();
        eError getChipId(std::uint32_t *val);
        std::uint8_t readU8(std::uint8_t reg);
        std::uint16_t readU16(std::uint8_t reg);
        std::uint16_t readU16LE(std::uint8_t reg);
        bool writeU8(std::uint8_t reg, std::uint8_t data);
        std::uint32_t readU24(std::uint8_t reg);
    };
} //namespace module