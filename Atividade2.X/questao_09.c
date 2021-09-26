/*
 * Arquivo: questao_09.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      

// Ajusta a frequência do oscilador para a função_delay())
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>
#include <stdio.h>
#include "Serial/serial.h"

// Configurações de pré-compilação
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // habilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)
#pragma config PBADEN = OFF         // desabilita o ADC da porta B para utilizar a INT0

// Definição de protótipos de funções
void configuraInterrupcao(void);
void configuraCCP(void);
void configurarTimer2(void);

void main(void)
{
    // Configura o oscilador interono em 4MHz
    OSCCON = 0b01100010;
    
    // configura a serial
    inicializarUART(9600, 1);
    enviarString("Comunicacao Serial inicializada!\n\r");
    
    // confiruação das interrupções externas
    configuraInterrupcao();
    enviarString("Interrupcoes Habilitadas!\n\r");
    
    // configuração do modulo CCP
    configuraCCP();
    enviarString("Modulo CCP configurado!\n\r");
    
    // Libera as chaves
    TRISC = SAIDA;
    RC4 = 1;
    RC5 = 0;
    /* Loop infinito*/
    while(1);
    
}

/*  Entrada:
 *  Saída:
 *  Descrição:  Configura as interrupções externa 0 e 2 por borda crescente.
 */
void configuraInterrupcao(void)
{
    // habilita interrupção global
    GIE = 1;
    // INTERRUPÇÃO EXTERNA 0
    TRISB0 = ENTRADA;
    INT0IE = 1;                 // habilita interrupção
    INT0IF = 0;                 // limpa a flag da interrupção
    INTEDG0 = 0;                // habilita interrupção por borda crescente
    // INTERRUPÇÃO EXTERNA 2
    TRISB2 = ENTRADA;
    INT2IE = 1;                 // habilita interrupção
    INT2IF = 0;                 // limpa a flag da interrupção
    INTEDG2 = 0;                // habilita interrupção por borda crescente
    
}


void __interrupt() interrupcoes(void)
{
    char mensagem[] = "Duty Cicle: 00.00%\n\r";
    // interrupção externa 0 e duty cicly menor que 90%?
    if(INT0IF)              
    {
        if(CCPR2L<216)              // 216 = 86.75% ~= 90%
            CCPR2L = CCPR2L + 24;   // incrementa 10%
        INT0IF = 0;                 // limpa a flag da interrupção externa 0
    }
    // interrupção externa 2 e duty cicly maior que 10% aproximadamente?
    if(INT2IF)
    {
        if(CCPR2L>24)               // 24 = 9.64% ~= 10%
            CCPR2L = CCPR2L - 24;   // decrementa 10%
        INT2IF = 0;                 // limpa a flag da interrupção externa 2
    }
    
    // informa na serial o duty cicle
    sprintf(mensagem, "Duty Cicle: %2.2f\n\r", ((float)CCPR2L/PR2)*100);
    enviarString((mensagem));
}


/*  Entradas: 
 *  Saídas:
 *  Descrição: Configura os registradores de controle do módulo CCP e os 
 *             respectivos timers associados para gerar uma onda de Período
 *             4MHz.
 */
void configuraCCP(void)
{
    /*  Configura o periodo do PWM
     *  PWM Periodo = [(PR2) + 1] * 4 * TOSC *(TMR2 Valor Pre-escala)
     *  PR2 = PWM Periodo/(4*TOSC*(TMR2 Valor Pre-escala)) - 1
     *  PR2 = FOSC/(4*PWM Frequencia*TMR2 Valor Pre-escala) - 1 
     *  FOSC = 4MHz, TMR2 Valor Pre-escala = 4, PWM Frequencia = 1kHz(duty cicly = 100%)
     *  PR2 = 249
     */
    PR2 = 249;
    /* Configura o duty cycle inicial(motor parado)
     * PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) * TOSC * (TMR2 Prescale Value)
     */
    CCPR2L = 0;                 // configura o duty cycle inicial em 0%
    TRISC1 = 0;                 // coloca o pino do CCP como sáida
    configurarTimer2();
    CCP2CON = 0b1100;           // configura o CCP como modo PWM
    //CCP2CONbits.DC2B = 0b00;  // configura a parte decimal em 0%
}

/*  Entrada:
 *  Saída:
 *  Descrição: Configura a pré-escala, limpa o registrador do timer 2 e dispara
 *             a contagem.
 */
void configurarTimer2(void)
{
    T2CONbits.T2CKPS = 0b01;    // configura a pré-escala do timer2 em 4
    TMR2 = 0;                   // limpa o registrador do timer 2
    TMR2ON = 1;                 // dispara o timer 2
}