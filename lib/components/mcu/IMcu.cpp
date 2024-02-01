//
// Created by oxford on 25.09.23.
//

#include "IMcu.h"


namespace hal::mcu {
    eError IMcu::reservePin(std::uint16_t id, eOwnership pinOwnership)
    {
        auto resource = m_reservedPins.find(id);
        if (resource == m_reservedPins.end())
        {
            auto result = m_reservedPins.insert({id, pinOwnership});
            if(result.second == true)
            {
                return eError::eOk;
            }
            return eError::eFail;
        }

        if((pinOwnership == eOwnership::eUnique) ||
           (resource->second == eOwnership::eUnique))
        {
            return eError::eAlreadyReserved;
        }

        if(resource->second == eOwnership::eShared)
        {
            auto result = m_reservedPins.insert({id, pinOwnership});
            if(result.second == true)
            {
                return eError::eOk;
            }
        }
        return eError::eFail;
    }

    eError mcuManager::reserveResource(std::uint16_t id, std::shared_ptr<IResource> reference)
    {
        auto success = m_resourcesMap.emplace(id, reference);
        if(success.second)
        {
            return eError::eOk;        
        }
        return eError::eAlreadyReserved;
    }

    eError mcuManager::reserveResourceWithPin(std::uint16_t id, std::shared_ptr<IResource> reference, 
        eOwnership pinOwnership)
    {
        auto success = m_resourcesMap.emplace(id, reference);
        if(success.second)
        {
            auto result = reservePin(id, pinOwnership);
            if(result == eError::eFail)
            {
                auto resource = m_resourcesMap.find(id);
                m_resourcesMap.erase(resource);
            }
            
            return result;            
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