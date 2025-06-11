//
// Created by oxford on 13.04.25.
//
#pragma once

#include <cstdint>

#include "errors.h"
#include "ITemperatureSensor.h"
#include "IOneWire.h"

namespace module
{
    class DS18B20 : public hal::sensor::ITemperatureSensor
    {
    public:
        DS18B20(std::shared_ptr<hal::oneWire::IOneWire> oneWire);
        eError enable(bool enable) override;
        eError getTemperature(float *val) override;
        eError getAddress(uint64_t *address) override;
    private:
        std::shared_ptr<hal::oneWire::IOneWire> mOneWire;
        const std::uint8_t cReadROM{(0x33)};
    };
} //namespace module