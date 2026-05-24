#include "led.h"

#define GPIOAEN (1U<<17)
#define LED_PIN_ON (1U<<5)
#define LED_PIN_OFF (1U<<21)


void led_init(void)
{
	RCC->AHBENR |= GPIOAEN;

	GPIOA->MODER &= ~(3U << 10);
	GPIOA->MODER |=  (1U << 10);
}

void led_on (void)
{
	//set led HIGH (PA5)
	GPIOA -> BSRR |= LED_PIN_ON;
}


void led_off (void)
{
	//set led LOW (PA5)
	GPIOA -> BSRR |= LED_PIN_OFF;
}
