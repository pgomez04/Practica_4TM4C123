#include "lib/include.h"

int main(void)
{
    uint16_t valor =0;
    char c = '5', caracter =','gp;
    int p_i, p_f;

     Configurar_PLL(_25MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART5();//Yo FCLK 25MHZ Baudrate 57600
    Configurar_GPIO();
    printChar(c);
    printString("\n");

    
   while(1)
    {
         c = readChar();
         switch(c)
         {
             case 'r':
                 //GPIODATA port F 662
                 printChar('a');
                 GPIOF->DATA = (1<<1);
                 break;
             case 'b':
                 //GPIODATA port F 662
                 printChar('b');
                 GPIOF->DATA = (1<<2);
                 break;
             case 'g':
                 //GPIODATA port F 662
                 printChar('c');
                 GPIOF->DATA = (1<<3);
                 break;
             case 'y':
                 //GPIODATA port F 662
                 printChar('d');
                 GPIOF->DATA = (1<<3) | (1<<2);
                 break;
             default:
                 printChar((char)valor);
                 GPIOF->DATA = (0<<1) | (0<<2) | (0<<3);
                 break;
         }

        char *invertir(char delim ,int *ptm);
         {
            

        }
       
    }

}
