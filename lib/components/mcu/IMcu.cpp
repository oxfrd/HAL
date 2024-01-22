//
// Created by oxford on 25.09.23.
//

#include "IMcu.h"


namespace hal::mcu {
    // eError IMcu::reservePin(uint16_t pinNo, eOwnership ownership)
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
    //          return eError::eAlreadyReserved;
    //     }

    //     return eError::eOk;
    // }

    eError mcuManager::reserveResource(std::uint16_t id, std::shared_ptr<IResource> reference)
    {
        auto success = m_resourcesMap.emplace(id, reference);
        if(success.second)
        {
            return eError::eOk;        
        }
        return eError::eAlreadyReserved;
    }

    std::shared_ptr<IResource> mcuManager::getResource(std::uint16_t id) 
    {
        auto resource = m_resourcesMap.find(id);
        if (resource != m_resourcesMap.end())
        {
            return resource->second;;
        }
        return nullptr;   
    }

} // hal::mcu