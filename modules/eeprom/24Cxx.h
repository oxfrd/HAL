//
// Created by oxford on 15.06.25
//
#pragma once

#include <cstdint>

#include "errors.h"
#include "IEeprom.h"
#include <II2c.h>

namespace e24Cxx
{
    static constexpr uint32_t cDefaultAddress{0x50};

    class e24Cxx : public hal::eeprom::IEeprom
    {
    public:
        e24Cxx(std::shared_ptr<hal::i2c::II2c> i2cHandle, uint32_t address = cDefaultAddress);
        eError read(uint32_t offset, uint8_t *data , size_t length) override;
        eError write(uint32_t offset, uint8_t *data , size_t length) override;
        eError getAddress(uint32_t *address) override;
        eError getSize(uint32_t *size) override;
    private:
        std::shared_ptr<hal::i2c::II2c> mI2c{nullptr};
        std::uint8_t mI2cAddress{};

        eError getChipId(std::uint32_t *val);
    };
} //namespace e24Cxx