#include "ITimeInterrupt.h"

namespace hal::interrupt
{
    std::pair<std::shared_ptr<ITimeInterrupt>, eError> ITimeInterrupt::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<ITimeInterrupt>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto interrupt = std::dynamic_pointer_cast<hal::interrupt::ITimeInterrupt>(res)) 
        {
            retPair.first = std::move(interrupt);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::interrupt