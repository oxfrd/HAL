//
// Created by oxford on 30.05.23.
//
#include "stm32l476xx.h"
#include "IGpio.h"
#include "gpio.h"

//hal::gpio::IGpioOutput out;

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
    auto ledGreen = mcu::gpio::gpioOutput(8, GPIOE);
    auto ledRed = mcu::gpio::gpioOutput(2, GPIOB);

    while (true)
    {
        ledRed.on();
        delayMe(10);

        ledGreen.off();
        ledRed.off();
        delayMe(40);

        ledGreen.on();
        ledRed.on();
        delayMe(10);

    }
    return 0;
}