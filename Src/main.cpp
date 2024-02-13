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

static void func(std::shared_ptr<hal::mcu::mcuManager> x)
{
    using namespace mcu;

    std::shared_ptr<gpio::gpioOutput> led{nullptr};
    auto getter = led->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2), x);
    if (getter.second == eError::eOk)
    {
        led = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
    }

    led->toggle();
    delayMe(40);
    led->toggle();
    delayMe(40);
    led->toggle();
    delayMe(40);
}

int main()
{
    using namespace mcu;
    auto mcu = init();
    
    std::shared_ptr<gpio::gpioOutput> ledRed{nullptr};
    auto getter = ledRed->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2),mcu);
    if (getter.second == eError::eOk)
    {
        ledRed = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
    }

    std::shared_ptr<gpio::gpioOutput> ledGreen{nullptr};
    getter = ledGreen->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_E8),mcu);
    if (getter.second == eError::eOk)
    {
        ledGreen = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
    }
    
    while (true)
    {
        ledRed->toggle();
        ledGreen->toggle();
        delayMe(10);

        ledRed->toggle();
        ledGreen->toggle();

        delayMe(40);

        func(mcu);

        ledRed->toggle();
        ledGreen->toggle();
        delayMe(10);
    }
    
    return 0;
}