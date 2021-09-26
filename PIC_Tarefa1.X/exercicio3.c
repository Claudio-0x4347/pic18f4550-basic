/*
 * File:   exercicio3.c
 * Author: claud
 *
 * Created on 12 de Novembro de 2020, 10:51
 */
#define _XTAL_FREQ 4000000

#include <xc.h>

#pragma config FOSC = INTOSC_EC
#pragma config WDT = OFF
#pragma config MCLRE = OFF
#pragma config PBADEN = OFF // coloca os pinos analógicos como digitais (desliga conversor AD)

void setupInt(void) 
{
    GIE = 1;        // habilita interrupção global
    INT0IE = 1;     // habilita interrupçao 0
    INT0F = 0;      // limpa flag de interrupção 0
    INTEDG0 = 1;    // interrupção por detecção de subida de borda
}

void interrupt interrupcao(void)
{
    if (INT0F) 
    {
        LATDbits.LD0 = !LATDbits.LD0;
        INT0F = 0;
    }
}

void main(void) 
{
    OSCCON = 0b01100000;
    TRISD = 0x00;   // configura porta D como saída
    TRISB = 0x01;   // configura RB0 como entrada
    
    setupInt();
    while(1);   // loop infinito
}
