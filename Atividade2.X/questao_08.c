/*
 * C�digo em C99
 * Arquivo: questao_08.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      
// Defini��o das Macros utilizadas no Programa
#define tensaoParaMeioPeriodo(V)    (450L*(V)/1023.0 + 50)

// Ajusta a frequ�ncia do oscilador para a macro __delay_ms()
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>
#include <inttypes.h>               // biblioteca para trabalhar com inteiros
#include <stdio.h>                  // sprintf()
#include "Serial/serial.h"

// Configura��es de pr�-compila��o
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // desabilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Vari�vel global para o comparador
uint16_t tempo_setado_ms;

// Prot�tipo de fun��es
void configurarInterrupcoes(void);
void configuraADC(void);

void main(void)
{    
    // Configura o oscilador interono em 4MHz
    OSCCON = 0b01100010;
    
    // Coloca a porta D0 como sa�da da onda
    TRISD0 = SAIDA;
    
    // Configura a serial
    inicializarUART(9600, HIGH_BOUND_RATE);
    enviarString("Comunicacao Serial Inicializada!\n\r");
    
    // Configura as interrup��es
    configurarInterrupcoes();
    enviarString("Interrupcao Timer 2 Inicializada!\n\r");
    
    // Configura o conversor AD
    configuraADC();
    enviarString("ADC Inicializado!\n\r");
    
    // Inicializa��o das vari�veis
    char mensagem[] = "Leitura = 1000ms\n\r";    // mensagem a ser exibida serial
    
    // Leitura inicial do comparador
    GODONE = 1;                 // inicia a leitura do ADC
    while(GODONE);              // espera a leitura
    tempo_setado_ms = tensaoParaMeioPeriodo(ADRES);
    
    // dispara a contagem
    TMR2ON = 1;
    
    /* Loop infinito*/
    while(1)
    {
        // L� o ADC e converte o valor para meio per�odo de onda
        GODONE = 1;                 // inicia a leitura do ADC
        while(GODONE);              // espera a leitura
        tempo_setado_ms = tensaoParaMeioPeriodo(ADRES);
        
        // Imprime na serial o valor lido
        sprintf(mensagem,"Periodo = %ums\n\r",2*tempo_setado_ms);
        enviarString(mensagem);
        __delay_ms(200);
    }
    
}

void __interrupt() myIsr(void)
{
    static uint16_t tempo_ms = 0;
    // interrup��o do Timer2?
    if(TMR2IF)
    {
        if(++tempo_ms>=tempo_setado_ms)
        {
            LATD0 = !LATD0;     // inverte o estado da onda
            tempo_ms = 0;       // reiniscina a contagem
        }
        TMR2IF = 0;         // limpa a flag da interrup��o do timer 2
    }
}

/*  Entrada:
 *  Sa�da:
 *  Descri��o:  Habilita a interrup��o do timer 2 em um intervalo de tempo 
 *              calculado.
 */
void configurarInterrupcoes(void)
{
    /* Fosc = 4MHz, Pr�-escala = 4, Pos-escalar = 10, PR2 = 25
     * F = 1kHz, dT = 1ms
     */
    TMR2IF = 0;                 // Limpa a flag da interrup��o do timer 2
    T2CONbits.T2CKPS = 0b01;    // Pr�-escala de 1:4
    PR2 = 24;                   // 25 pulsos
    T2CONbits.TOUTPS = 0b1001;  // Pos-escala = 1:10
    GIE = 1;                    // habilita a interrup��o global
    PEIE = 1;                   // habilita a interrup��o dos perif�ricos
    TMR2IE = 1;                 // habilita a interrup��o por timer 2
}

/*  Entrada:
 *  Sa�da:
 *  Descri��o:  Configura o ADC para leitura sem interrup��o.
 */
void configuraADC(void)
{
    VCFG0 = 0b00;           // configura a refer�ncia em VCC e VSS
    TRISA1 = ENTRADA;       // coloca RA1 como entrada
    CHS0 = 0b0001;          // configura o canal de leitura
    ACQT0 = 0b010;          // seleciona o tempo de aquisi��o em 4Tad
    ADCS0 = 0b101;          // configura a frequencia do oscilador do ADC em Fosc/16
    ADFM = 1;               // resultado justificado a direita
    ADON = 1;               // liga o ADC
}