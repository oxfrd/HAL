//
// Created by oxford on 25.09.23.
//
#pragma once

#include "string"
#include "unordered_map"
#include "vector"
#include "errors.h"

namespace hal::mcu {

    enum class eOwnership
    {
        eUnique,
        eShared,
    };

    class IMcu
    {
    public:
        IMcu(uint16_t pinsNbr);
        error reservePin(uint16_t pinNo, eOwnership ownership);

    private:
        std::uint16_t m_allPinsNbr;

//        std::unordered_map<hal::gpio::*IPort>

    };

    template<typename portId_t>
    class devManager
    {
    public:
        devManager();
        devManager(devManager const&) = delete;
        void operator = (devManager const&) = delete;
        virtual error init(eOwnership ownership) = 0;
        error reserveResource(portId_t resourceId);
    private:
        std::unordered_map<std::uint16_t, eOwnership> m_reservedPins;
        std::unordered_map<portId_t, eOwnership> m_resourcesMap;

    };

} // hal::mcu
