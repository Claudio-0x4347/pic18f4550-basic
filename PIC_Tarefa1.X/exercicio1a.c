/*
 * File:   exercicio1a.c
 * Author: claud
 *
 * Created on 10 de Novembro de 2020, 20:34
 */

#define _XTAL_FREQ 4000000

#include <xc.h>

#pragma config FOSC = INTOSC_EC
#pragma config WDT = OFF        // desabilita o watchdog timer
#pragma config MCLRE = OFF


void main(void) 
{
    
    OSCCON = 0b01100000;    // utiliza o cristal interno de 4MHz
    TRISD = 0b00000000;
    LATD = 1;
    
    while(1) 
    {
        
        while(LATD != 0b00000001) 
        {
            LATD = (LATD >> 1 | LATD << 7);
            __delay_ms(100);
        }
        
        while(LATD != 0b10000000) 
        {
            LATD = (LATD << 1 | LATD >> 7);
            __delay_ms(100);
        }
        
    }
    
}