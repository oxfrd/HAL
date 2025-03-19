#include "ITemperatureSensor.h"

namespace hal::sensor
{
    std::pair<std::shared_ptr<ITemperatureSensor>, eError> ITemperatureSensor::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<ITemperatureSensor>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<ITemperatureSensor>(res)) 
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} // namespace hal::sensor