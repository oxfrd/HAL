#include "IUart.h"

namespace hal::uart
{
    std::pair<std::shared_ptr<IUart>, eError> IUart::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IUart>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<hal::uart::IUart>(res)) 
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::uart