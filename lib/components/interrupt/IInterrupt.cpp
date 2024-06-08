#include "IInterrupt.h"

namespace hal::interrupt
{
    std::pair<std::shared_ptr<IInterrupt>, eError> IInterrupt::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IInterrupt>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto interrupt = std::dynamic_pointer_cast<hal::interrupt::IInterrupt>(res)) 
        {
            retPair.first = std::move(interrupt);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::interrupt