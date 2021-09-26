/*
 * File:   exercicio2d.c
 * Author: claud
 *
 * Created on 12 de Novembro de 2020, 10:30
 */

#define _XTAL_FREQ 1000000

#include <xc.h>

#pragma config FOSC = INTOSC_EC
#pragma config WDT = OFF
#pragma config MCLRE = OFF

void main(void) 
{
    OSCCON = 0b01000000;            // coloca a frequencia do oscilador em 1 MHz
    TRISDbits.TRISD0 = 0b00000000;

    while(1) 
    {
        LATDbits.LATD0 = !LATDbits.LATD0;
        __delay_ms(100);
    }
}