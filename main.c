
#include "stm32f4xx.h"


void adc_configure();
int adc_convert();

void LED_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_On(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void LED_Off(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void flip() {
	static int i;
	if (i&1)
		LED_On();
	else
		LED_Off();
	i++;
}
/*
 * connect a potentiometer over 3V3 and 0V and connect the wiper to A5 on STMF446RE board
 * and use the value read from ADC to alter the flashing rate of LED2!
 */
int main(void)
{
	unsigned int i, adcr;
	i = adcr = 0;
	LED_Init ();

	adc_configure();

A:
	for (i=0; i < (adcr * 1000); i++) {
		asm ("\t nop");
	}
	adcr = adc_convert();
	flip ();
	goto A;
}
