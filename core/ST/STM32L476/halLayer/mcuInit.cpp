//created by Oxfrd 8.11.2023

#include "mcuInit.h"
#include "IGpio.h"
#include "gpio.h"
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
    
    auto gpio = std::make_shared<gpio::gpioOutput>(8, 4, GPIOE);
    auto err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_E8),std::move(gpio));
    checkErr(err);

    gpio = std::make_shared<gpio::gpioOutput>(2, 1, GPIOB);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_B2), std::move(gpio));
    checkErr(err);

    return std::move(mcu);
}

}   //mcu
