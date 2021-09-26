/*
 * Arquivo: questao_03.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      

// Ajusta a frequ�ncia do oscilador para a fun��o_delay())
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>
#include "Serial/serial.h"
// Configura��es de pr�-compila��o
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // habilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Defini��o de prot�tipos de estruturas de dados


void main(void)
{
    // configura o oscilador interno em 4MHz
    OSCCON = 0b01100010;
    
    // inicializa a comunica��o serial
    inicializarUART(9600, HIGH_BOUND_RATE);
    enviarString("Comunicacao Serial Inicializada!\n\r");
    
    // 
    /* Loop infinito*/
    while(1)
    {
        
        
        
    }
    
}
