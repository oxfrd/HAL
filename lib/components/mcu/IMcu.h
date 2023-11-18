//
// Created by oxford on 25.09.23.
//
#pragma once

#include "string"
#include "unordered_map"
#include "vector"
#include "errors.h"

#include "IComponent.h"

namespace hal::mcu {

    enum eOwnership
    {
        eUnique,
        eShared,
    };

    class IMcu
    {
    public:
        // IMcu(uint16_t pinsNbr);
        // error reservePin(uint16_t pinNo, eOwnership ownership);
    private:
        std::uint16_t m_allPinsNbr;
    };

    class mcuManager : public IMcu
    {
    public:
        mcuManager() = default;
        mcuManager(mcuManager const&) = delete;
        void operator = (mcuManager const&) = delete;
        error reserveResource(std::uint16_t id, IResource *reference);
        error getResource(std::uint16_t id, IResource *reference);
    private:
        // std::unordered_map<std::uint16_t, eOwnership> m_reservedPins;
        std::unordered_map<std::uint16_t, IResource*> m_resourcesMap;

    };

} // hal::mcu
