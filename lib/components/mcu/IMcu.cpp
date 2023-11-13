//
// Created by oxford on 25.09.23.
//

#include "IMcu.h"


namespace hal::mcu {
    // eErrors IMcu::reservePin(uint16_t pinNo, eOwnership ownership)
    // {
    //     if (pinNo > m_allPinsNbr)
    //     {
    //         return eErrors::eNotExist;
    //     }

    //     auto it = m_reservedPins.find(pinNo);

    //     if(it == m_reservedPins.end())
    //     {
    //         m_reservedPins.insert({pinNo, ownership});
    //     }
    //     else if(it->second == eOwnership::eUnique)
    //     {
    //         return eErrors::eAlreadyReserved;
    //     }

    //     return eErrors::eOk;
    // }

error mcuManager::reserveResource(std::uint16_t id, IResource *reference)
{
    auto success = m_resourcesMap.emplace(id, reference);

    if(success.second)
    {
        return error::eOk;        
    }
    return error::eAlreadyReserved;
}

error mcuManager::getResource(std::uint16_t id, IResource *reference) 
{
    auto resource = m_resourcesMap.find(id);
    if (resource != m_resourcesMap.end())
    {
        reference = resource->second;
        return error::eOk;
    }
    
    return error::eUninitialized;
}

} // hal::mcu