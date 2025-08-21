//
// Created by oxford on 13.04.25.
//
#pragma once

#include <cstdint>

#include "errors.h"
#include "ITemperatureSensor.h"
#include "IOneWire.h"
#include "IDelay.h"

namespace module
{
    constexpr size_t cScratchPadSize{9};

    class DS18B20 : public hal::sensor::ITemperatureSensor
    {
    public:
        DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire, std::shared_ptr<hal::delay::IDelay> delay, const uint8_t *adress = nullptr);
        eError enable(bool enable) override;
        eError getTemperature(float *val) override;
        eError getAddress(uint64_t *address) override;
    private:
        static constexpr std::uint8_t cAdressBytesCnt{8};

        const std::uint8_t cReadROM{0x33};
        const std::uint8_t cConvertTemperature{0x44};
        const std::uint8_t cNotSkipAdressing{0x55};
        const std::uint8_t cReadScratchpad{0xBE};
        const std::uint8_t cSkipAdressing{0xCC};

        const std::uint32_t cTemperatureReadTimeout{500};
        const float cMaxValidMeasurement{150.0f};

        uint8_t mAdressingMode = cNotSkipAdressing;
        uint8_t mAdress[8];

        std::uint8_t mScratchPad[cScratchPadSize];
        
        eError sendAddress();
        uint8_t crc8( uint8_t *addr, uint8_t len);

        std::shared_ptr<hal::oneWire::IOneWire> mOneWire{nullptr};
        std::shared_ptr<hal::delay::IDelay> mDelay{nullptr};
    };
} //namespace module