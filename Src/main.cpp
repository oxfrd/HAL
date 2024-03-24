//
// Created by oxford on 30.05.23.
//
#include <vector>
#include "stm32l476xx.h"
#include "gpioOutput.h"
#include "IComponent.h"
#include "mcuInit.h"
#include "main.h"
#include "timeInterrupt.h"
#include "delay.h"

static void errHandler()
{
    while(1)
    {
        asm("NOP");
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
    {
        auto getter = ledRed->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2),mcu);
        if (getter.second == eError::eOk)
        {
            ledRed = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
        } else { errHandler();}
    }

    std::shared_ptr<gpio::gpioOutput> ledGreen{nullptr};
    {
        auto getter = ledGreen->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_E8),mcu);
        if (getter.second == eError::eOk)
        {
            ledGreen = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
        } else { errHandler();}
    }
    
    std::shared_ptr<interrupt::timeInterrupt> interrupt{nullptr};
    {
        auto getter = interrupt->getPtr(static_cast<uint16_t>(eMcuResources::eIntTim2),mcu);
        if (getter.second == eError::eOk)
        {
            interrupt = std::dynamic_pointer_cast<interrupt::timeInterrupt>(getter.first);
        } else { errHandler();}
    }

    interrupt->enable();

    while (true)
    {
        constexpr std::uint32_t x{500};
        ledRed->toggle();
        // ledGreen->toggle();
        delayMe(x);

        ledRed->toggle();
        // ledGreen->toggle();

        delayMe(500);

        // func(mcu);

        ledRed->toggle();
        // ledGreen->toggle();
        delayMe(x);
    }
    
    return 0;
}