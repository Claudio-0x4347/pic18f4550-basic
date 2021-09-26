/*
 * Código em C99
 * Arquivo: serial.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */ 

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif
#include <xc.h>
#include "serial.h"


/*  Entradas:   Taxa de dados, modo UART
 *  Saídas:
 *  Descrição:  Define as portas Tx e Rx como saída e inicializa o modo UART
 *              para transmissão e recepção.
 */
void inicializarUART(long bound_rate, unsigned char modo)
{
    // Configura os pinos Tx e Rx
    TRISC6 = SAIDA;
    TRISC7 = ENTRADA; 
    
    // Habilita e escolhe o modo da taxa de transmissão
    switch(modo)
    {
        /*  Ciclo de Maquina: Fosc/ 4
         *  UART: Ciclo de Maquina/4
         */
        case HIGH_BOUND_RATE: TXSTA = 0x24;
            SPBRG = ((_XTAL_FREQ /(16*bound_rate)) -1);
            break;
        /*  Ciclo de Maquina: Fosc/ 4
         *  UART: Ciclo de Maquina/16
         */
        default: TXSTA = 0x20;
            SPBRG = ((_XTAL_FREQ /(64*bound_rate)) -1);
            break;
    }
    
    // Habilita a recepção
    RCSTA = 0x90;
    
}

/*  Entradas:   caracter
 *  Saídas:
 *  Descrição:  Carrega o registrador TXREG com o registrador a ser enviado e
 *              aguarda a transmissão.
 */
void enviarCaracter(const char c)
{
    TXREG = c;      // carrega o registrador de envio com o caracter
    while(!TXIF);   // Espera a confirmação do envio
}

/*  Entradas:   ponteiro para string constante
 *  Saídas:
 *  Descrição:  Percorre a string eviando os caracteres para serial até
 *              encontrar o caracter nulo.
 */
void enviarString(const char * mensagem)
{
    if(mensagem!=NULL)
        while(*mensagem!='\0')                // verificia o final da string
            enviarCaracter(*mensagem++);      // envia o caracter e incrementa o contador
}
