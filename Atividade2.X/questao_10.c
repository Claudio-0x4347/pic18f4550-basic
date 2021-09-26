/*
 * Arquivo: questao_10.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      

// Ajusta a frequ�ncia do oscilador para a fun��o_delay())
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>

// Configura��es de pr�-compila��o
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = ON             // habilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Defini��o de prot�tipos de estruturas de dados


void main(void)
{
    
    /* Loop infinito*/
    while(1)
    {
        // Reinicia a contagem do whatchdog timer
        ClrWdt();
        
        
    }
    
}
