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
    hal::mcu::mcuManager *mcuST32L476; 
    mcu::ST32L476::init(mcuST32L476);
    
    using namespace mcu::ST32L476;

    hal::gpio::IGpioOutput *gpio;
    auto B2 = mcuST32L476->getResource(static_cast<std::uint16_t> (eMcuResources::eGPIO_B2), gpio);
    while (true)
    {
        gpio->toggle();
        delayMe(10);

        gpio->toggle();

        delayMe(40);

        gpio->toggle();
        delayMe(10);
    }
    return 0;
}