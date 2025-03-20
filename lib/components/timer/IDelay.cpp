#include "IDelay.h"

namespace hal::delay
{
    std::pair<std::shared_ptr<IDelay>, eError> IDelay::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IDelay>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto tim = std::dynamic_pointer_cast<hal::delay::IDelay>(res)) 
        {
            retPair.first = std::move(tim);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::delay