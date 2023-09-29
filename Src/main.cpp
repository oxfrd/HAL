//
// Created by oxford on 30.05.23.
//
#include "stm32l476xx.h"
#include "IGpio.h"

hal::gpio::IGpioOutput out;

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

void toggle(cGPIOs pin)
{
    switch (pin)
    {
        case cGPIOs::ledRed:
            GPIOB->ODR ^= GPIO_ODR_OD2;
            break;
        case cGPIOs::ledGreen:
            GPIOE->ODR ^= GPIO_ODR_OD8;
            break;
    };
}

int main()
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

    GPIOB->MODER |= GPIO_MODER_MODE2_0;          //output
    GPIOB->MODER &= ~GPIO_MODER_MODE2_1;          //output
//	    GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;          //push-pull
//	    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_0;  //low speed
//	    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_1;  //low speed

    GPIOE->MODER |= GPIO_MODER_MODE8_0;          //output
    GPIOE->MODER &= ~GPIO_MODER_MODE8_1;
//    GPIOE->OTYPER &= ~GPIO_OTYPER_OT8;          //push-pull
    auto LedRed = hal::gpio::IGpioOutput();
    while (true)
    {
        toggle(cGPIOs::ledRed);
        delayMe(10);

        toggle(cGPIOs::ledGreen);
        delayMe(40);

        toggle(cGPIOs::ledGreen);

        toggle(cGPIOs::ledRed);
        delayMe(10);

    }
    return 0;
}