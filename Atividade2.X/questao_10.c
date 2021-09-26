/*
 * Arquivo: questao_10.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      

// Ajusta a frequência do oscilador para a função_delay())
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>

// Configurações de pré-compilação
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = ON             // habilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Definição de protótipos de estruturas de dados


void main(void)
{
    
    /* Loop infinito*/
    while(1)
    {
        // Reinicia a contagem do whatchdog timer
        ClrWdt();
        
        
    }
    
}
