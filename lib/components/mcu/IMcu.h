//
// Created by oxford on 25.09.23.
//
#pragma once

#include "string"
#include "unordered_map"
#include "vector"
#include "errors.h"

#include "IComponent.h"
#include <memory>

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
        // eError reservePin(uint16_t pinNo, eOwnership ownership);
    private:
        std::uint16_t m_allPinsNbr;
    };

    class mcuManager : public IMcu
    {
    public:
        mcuManager() = default;
        eError reserveResource(std::uint16_t id, std::shared_ptr<IResource> reference);
        eError reserveResource(std::shared_ptr<IResource>);
        std::shared_ptr<IResource> getResource(std::uint16_t id, std::shared_ptr<IResource> reference);
        std::shared_ptr<IResource> getResource(std::uint16_t id); 
        
    private:
        // std::unordered_map<std::uint16_t, eOwnership> m_reservedPins;
        std::unordered_map<std::uint16_t, std::shared_ptr<IResource>> m_resourcesMap;
    };
} // hal::mcu
