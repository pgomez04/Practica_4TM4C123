
#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    /*
    Habilitar el modulo 0 del ADC con dos canales analogicos 
    en el puerto E a una velocidad de conversion de 250ksps
    dandole la mayor prioridad al secuenciador 2 con evento
    de procesador 
    */
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (0<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(0<<0)|(0<<12)|(0<<8);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE->DIR = (0<<2) | (0<<5); //PE2 (1) y PE5(8)
    GPIOD->DIR = (0<<2) | (0<<0) | (0<<1); //PD2(5) , PD0(7) Y PD1(6)
    GPIOB->DIR = (0<<5) ; //PB5 (11)
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE->AFSEL =  (1<<2) | (1<<5 );
    GPIOD->AFSEL =  (1<<2) | (1<<0 ) | (1<<1);
    GPIOB->AFSEL =  (1<<5 );
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE->DEN = (0<<2) | (0<<5 );
    GPIOD->DEN = (0<<2) | (0<<0 ) | (0<<1);
    GPIOB->DEN = (0<<5 );
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
     GPIOE->PCTL = GPIOE->PCTL & (0xFF0FF0FF);//PONER 0 EN LOS PINES CORRESPONDIENTES
    GPIOD->PCTL = GPIOE->PCTL & (0xFFFFF0F0);
    GPIOB->PCTL = GPIOE->PCTL & (0xFF0FFFFF);
    //(GPIOAMSEL) pag.786 habilitar analogico
    GPIOE->AMSEL = (1<<2) | (1<<5 );
    GPIOD->AMSEL = (1<<2) | (1<<0 ) | (1<<1);
    GPIOB->AMSEL = (1<<5 );

    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x7;//1Msps //VELOCIDAD DE MUESTREO
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC0->SSPRI = 0x1230;//establecer prioridades
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<0) | (0x0<<15) ; //evento de muestras
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX0 = (1<<0)|(5<<4)|(7<<8)|(11<<12)|(6<<16);//1,5,7,11,6,8
    ADC0->SSMUX3 = (8<<0);
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL0 = (1<<2) | (1<<1) | (1<<4) | (1<<5) | (1<<10) | (1<<9) | (1<<14) | (1<<13) | (1<<18) | (1<<17) ;
    ADC0->SSCTL3 = (1<<2) | (1<<1) ; //SAMPLES
    /* Enable ADC Interrupt */
    ADC0->IM |= (1<<2); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (1<<3) | (0<<2) | (0<<1) | (1<<0);
    ADC0->PSSI |= (1<<3) | (0<<0) ;
}
extern void ADC0_InSeq2(uint16_t *Result)
{

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
    ADC0->PSSI = 0x00000009;
    while((ADC0->RIS & (1<<0))==0){}; // espera al convertidor
    Result[0] = ADC0->SSFIFO2&0xFFF; //  Leer  el resultado almacenado en la pila2
    Result[1] = ADC0->SSFIFO2&0xFFF;
    Result[2] = ADC0->SSFIFO2&0xFFF;
    Result[3] = ADC0->SSFIFO2&0xFFF;
    Result[4] = ADC0->SSFIFO2&0xFFF;
    while((ADC0->RIS & (1<<3))==0){}; 
    Result[5] = ADC0->SSFIFO2&0xFFF; 
       
    PWM1->_3_CMPB = (int)((1*Result[0])/4095) - 1;
    PWM1->_3_CMPA = (int)((1*Result[1])/4095) - 1;
    PWM1->_2_CMPA = 0;
    ADC0->ISC = 0x0004;  //Conversion finalizada

}


