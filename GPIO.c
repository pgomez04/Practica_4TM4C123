#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    //Paso 1 Enceder el periferico Run Clock Gate Control GPIO
    SYSCTL->RCGCGPIO |= (1<<5);//enable GPIOF,GPION,GPIOJ
    //Paso 2
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR= 0x1F;
    GPIOF->AMSEL = 0x00;
    //Salidas y entradas
    GPIOF->DIR |= 0x0E;
    //Paso 3
    GPIOF->AFSEL |= 0x00;

    GPIOF->PCTL|= 0x00;
    GPIOF->PUR |= 0x11;
    GPIOF->DEN |= 0x1F;
}

extern void Delay(void)
{
    unsigned long volatile time;
    time = 1600000;
    while(time)
    {
        time--;
    }
}

