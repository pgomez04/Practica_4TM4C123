#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    //Paso 1 Enceder el periferico Run Clock Gate Control GPIO
    SYSCTL->RCGCGPIO |= (1<<5);
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR = 0x1F;           // allow changes to PF4-0
    GPIOF->AMSEL = 0x00;        // 3) disable analog on PF
    GPIOF->PCTL = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIOF->DIR = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
    GPIOF->AFSEL = 0x00;        // 6) disable alt funct on PF7-0
    GPIOF->PUR = 0x11;          // enable pull-up on PF0 and PF4
    GPIOF->DEN = 0x1F;          // 7) enable digital I/O on PF4-0
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
