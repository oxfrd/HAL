//created by Oxfrd 8.11.2023

#include "mcuInit.h"
#include "IGpio.h"
#include "gpio.h"
#include "gpioPort.h"
#include <cassert>

void checkErr(eError err)
{
    if(err != eError::eOk)
    {
        assert(0);
    }
}

namespace mcu{

std::shared_ptr<hal::mcu::mcuManager> init()
{
    auto mcu = std::make_shared<hal::mcu::mcuManager>(hal::mcu::mcuManager());
    if (mcu == nullptr)
    {
        assert(0);
    }

    auto portE = std::make_shared<mcu::gpio::gpioPort>(mcu::gpio::gpioPort(4));
    auto err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::ePortE),std::move(portE));
    checkErr(err);
    auto getter = portE->getPtr(static_cast<uint16_t>(eMcuResources::ePortE),mcu);
    if (getter.second == eError::eOk)
    {
        portE = std::dynamic_pointer_cast<mcu::gpio::gpioPort>(getter.first);
    }

    auto portB = std::make_shared<mcu::gpio::gpioPort>(mcu::gpio::gpioPort(1));
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::ePortB),std::move(portB));
    checkErr(err);
    
    getter = portB->getPtr(static_cast<uint16_t>(eMcuResources::ePortB),mcu);
    if (getter.second == eError::eOk)
    {
        portB = std::dynamic_pointer_cast<mcu::gpio::gpioPort>(getter.first);
    }


    auto gpio = std::make_shared<gpio::gpioOutput>(8, portE, GPIOE);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_E8),std::move(gpio));
    checkErr(err);

    gpio = std::make_shared<gpio::gpioOutput>(2, portB, GPIOB);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_B2), std::move(gpio));
    checkErr(err);

    return std::move(mcu);
}

}   //mcu
