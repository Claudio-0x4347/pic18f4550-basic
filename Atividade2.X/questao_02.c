/*
 * Arquivo: questao_02.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * OBS: COMPILAR O ARQUIVO EM C99 E HABILITAR OS MODULOS LM35, SERIAL E QUESTAO2
 */      

// Ajusta a frequência do oscilador para a função_delay())
#define _XTAL_FREQ 4000000


// Bibliotecas utilizadas
#include <xc.h>
#include "Serial/serial.h"
#include "Temperatura/LM35.h"
// Configurações de pré-compilação
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // desabilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Definição de protótipos de estruturas de dados


void main(void)
{
    // configura o oscilador interno em 4MHz
    OSCCON = 0b01100010;
    
    // inicializa a comunicação serial
    inicializarUART(9600, HIGH_BOUND_RATE);
    enviarString("Serial Inicializada!\n\r");
    
    // inicialia o LM35
    configuraLM35();
    enviarString("LM35 Inicializado!\n\r");
    
    // inicializa o motor cc
    LATC = 0;                   // desliga o motor cc
    TRISC = SAIDA;              // coloca a porta c como saída

    /* Loop infinito*/
    while(1)
    {
        // Lê a temperatura
        double temperatura = lerLM35();
        
        if(temperatura>100)
        {
            LATC = 0b00010010;          // liga o motor cc em velocidade máxima            
            enviarString("Temperatura muito alta\n\r");
            continue;               // desvia o fluxo para o inicio do loop para
                                    // evitar que desligue o motor
        }else if(temperatura>30)
        {
            enviarString("Temperatura Adequada\n\r");
        }else
        {
            enviarString("Temperatura Baixa\n\r");
        }
        
        // desliga o motor cc
        LATC = 0;
        
        // delay para o programa não travar no proteus
        __delay_ms(200);
    }
    
}