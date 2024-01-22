//
// Created by oxford on 30.05.23.
//
#include <vector>
#include "stm32l476xx.h"
#include "IGpio.h"
#include "gpio.h"
#include "IComponent.h"
#include "mcuInit.h"
#include "main.h"

enum class cGPIOs
{
    ledRed,
    ledGreen,
};

static void delayMe(int ticks)
{
    int x = ticks;
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < x; j++)
        {
            asm("NOP");
        }
    }
}

int main()
{
    auto mcu = mcu::ST32L476::init();
    using namespace mcu::ST32L476;
    
    std::shared_ptr<hal::gpio::IGpioOutput> gpio{nullptr};
    auto x = gpio->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2),mcu);
    if (x.second == eError::eOk)
    {
        gpio = std::move(x.first);
    }

    std::shared_ptr<hal::gpio::IGpioOutput> green{nullptr};
    x = green->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_E8),mcu);
    if (x.second == eError::eOk)
    {
        green = std::move(x.first);
    }
    
    while (true)
    {
        gpio->toggle();
        green->toggle();
        delayMe(10);

        gpio->toggle();
        green->toggle();

        delayMe(40);

        gpio->toggle();
        green->toggle();
        delayMe(10);
    }
    
    return 0;
}