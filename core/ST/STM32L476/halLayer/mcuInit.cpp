//created by Oxfrd 8.11.2023

#include "mcuInit.h"
#include "vector"
#include "IGpio.h"
#include "gpio.h"
#include "IMcu.h"

namespace mcu::ST32L476{

void init(hal::mcu::IMcu *mcuHandle)
{
    auto mcu = hal::mcu::mcuManager();

    auto gpio = new mcu::gpio::gpioOutput(8, 4, GPIOE);
    mcu.reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_E8), gpio);

    gpio = new mcu::gpio::gpioOutput(2, 1, GPIOB);
    mcu.reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_B2), gpio);

    *mcuHandle = mcu;
}

}   //mcu::ST32L476
