//
// Created by oxford on 30.05.23.
//
#include <vector>
#include "stm32l476xx.h"
#include "IGpio.h"
#include "gpio.h"

//hal::gpio::IGpioOutput<GPIO_TypeDef> *out;

enum class cGPIOs
{
    ledRed,
    ledGreen,
};

void delayMe(int ticks)
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
    std::vector<hal::gpio::IGpioOutput<GPIO_TypeDef>*> outs;

    outs.push_back(new mcu::gpio::gpioOutput(8, 4, GPIOE));
    outs.push_back(new mcu::gpio::gpioOutput(2, 1, GPIOB));

    while (true)
    {
        for(auto out : outs)
        {
            out->toggle();
        }
        delayMe(10);

        for(auto out : outs)
        {
            out->toggle();
        }
        delayMe(40);

        for(auto out : outs)
        {
            out->toggle();
        }
        delayMe(10);
    }
    return 0;
}