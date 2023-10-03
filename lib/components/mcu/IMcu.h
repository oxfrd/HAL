//
// Created by oxford on 25.09.23.
//
#pragma once

#include "string"
#include "unordered_map"
#include "vector"


namespace hal::mcu {

    enum class eErrors
    {
        eOk,
        eAlreadyReserved,
        eNotExist,
    };

    enum class eOwnership
    {
        eUnique,
        eShared,
    };

    enum class eComponent
    {
    };

    using pinsMap = std::unordered_map<std::uint16_t, eOwnership>;

    class IMcu
    {
    public:
        IMcu(uint16_t pinsNbr);
        eErrors reservePin(uint16_t pinNo, eOwnership ownership);

    private:
        std::uint16_t m_allPinsNbr;
        pinsMap m_reservedPins;

        std::unordered_map<hal::gpio::*IPort>

    };

} // hal::mcu
