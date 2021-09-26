/*
 * File:   exercicio4.c
 * Author: claud
 *
 * Created on 12 de Novembro de 2020, 13:13
 */
#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdio.h>

#define RS LATD2
#define EN LATD3
#define D4 LATD4
#define D5 LATD5
#define D6 LATD6
#define D7 LATD7

#include "lcd.h"    // mudei a definição dos pinos do lcd na biblioteca do 
                    // github(nao sei bem se é essa a que o senhor utiliza)

#pragma config FOSC = INTOSC_EC
#pragma config WDT = OFF
#pragma config MCLRE = OFF

char linha1[16];
char linha2[16];
int contador = 0;

void main(void) 
{
    OSCCON = 0b01100000;    // configura oscilador interno em 4MHz
    TRISD = 0;
    
    Lcd_Init();
    sprintf(linha1, "Hello world! ");
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(linha1);
    
    while(1) 
    {
        sprintf(linha2, "Contador: %i ",contador);
        contador ++;
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(linha2);
        LATDbits.LATD0 = !LATDbits.LATD0;
        __delay_ms(500);    // coloquei so pra não travar meu pc na simulação
    }
}