/*
 * Arquivo: questao_12.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */      

// Ajusta a frequ�ncia do oscilador para a fun��o_delay())
#define _XTAL_FREQ 4000000

// Bibliotecas utilizadas
#include <xc.h>
#include <stdint.h>
#include "Serial/serial.h"
#include <stdio.h>

// Configura��es de pr�-compila��o
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // habilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// Macro para converter a leitura do ADC para temperatura
#define converterLeitura(x) (1.5*100*(x)/1023.0)

// Configura��es do Registradores de controle
// Tempos de Aquisi��o
#define _Tad_20      111
#define _Tad_16      110
#define _Tad_12      101
#define _Tad_8       100
#define _Tad_6       011
#define _Tad_4       010
#define _Tad_2       001
#define _Tad_0       000

// Clock de convers�o ADC
#define _clock_Frc_1      111
#define _clock_Fosc_64    110
#define _clock_Fosc_16    101
#define _clock_Fosc_4     100
#define _clock_Frc_2      011
#define _clock_Fosc_32    010
#define _clock_Fosc_8     001
#define _clock_Fosc_2     000
// Formata��o
#define DIREITA     1
#define ESQUERDA    0
// Tens�o de refer�ncia
#define _AN2_AN3    11
#define _AN2_Vdd    10
#define _Vss_AN3    01
#define _Vss_Vdd    00
// Defini��o de prot�tipos de estruturas de dados

/*  Entradas:   frequ�ncia do ADC, per�odos de convers�o, 
 *              formata��o direita/esquerda e configura��o das tens�es de refer�ncia.
 *  Sa�da:
 *  Descri��o:  Efetua a configura��o dos registradores de controle.
 */
void inicializarADC(char canal, char clock, char tad, char formatacao, char v_ref)
{   
    ADCON0bits.CHS = canal;             // seleciona o canal de leitura
    ADCON2bits.ADCS = clock;            // clock do conversor AD
    ADCON2bits.ACQT = tad;              // per�dos de convers�o
    ADCON2bits.ADFM = formatacao;       // formata��o direita ou esquera
    ADCON1bits.VCFG = v_ref;            // tens�o de refer�ncia
    ADCON0bits.ADON = 1;                // liga o ADC
}

/*  Entradas:
 *  Sa�da:      
 *  Descri��o:  Retorna a leitura do ADC.
 */
unsigned int lerADC(void)
{
    ADCON0bits.GO = 1;                  // inicia a convers�o
    while(ADCON0bits.DONE);             // aguarda a convers�o
    return ADRES;                       // retorna a leitura
}

void main(void)
{
    // Configura o oscilador interono em 4MHz
    OSCCON = 0b01100010;
    char mensagem[] = "                                   ";
    // inicializa a comunica��o serial
    inicializarUART(9600, HIGH_BOUND_RATE);
    enviarString("Comunicacao Serial inicializada!\n\r");
    
    // Configura o ADC
    TRISA1 = ENTRADA;
    // coloca refer�ncia no AN3 pela sa�da m�xima de 1,5V do LM35
    inicializarADC(0, _clock_Fosc_64, _Tad_4, DIREITA, _Vss_AN3);
    enviarString("Conversor AD inicializado!\n\r");
    
    // Configura os LEDs
    TRISD = SAIDA;
    LATD = 0x00;                // inciializa os leds desligados
   
    /* Loop infinito*/
    while(1)
    {
        // L� o ADC
        uint16_t leitura = lerADC();
        double temperatura = converterLeitura(leitura);
        sprintf(mensagem, "valor lido: %3.2f\n\r", temperatura);
        enviarString(mensagem);
        
        // liga os leds de acordo
        if(temperatura<=20)
            LATD = 0b00000001;            // Liga o led D0
        else if(temperatura<=30)
            LATD = 0b00000011;            // Liga o led D1
        else if(temperatura<=40)
            LATD = 0b00000111;            // Liga o led D2
        else if(temperatura<=50)
            LATD = 0b00001111;            // Liga o led D3
        else if(temperatura<=60)
            LATD = 0b00011111;            // Liga o led D4
        else if(temperatura<=70)
            LATD = 0b00111111;            // Liga o led D5
        else if(temperatura<=80)
            LATD = 0b01111111;            // Liga o led D6
        else if(temperatura<120)
            LATD = 0b11111111;            // Liga o led D7
        else
        {
            LATD = LATD ^ 0xFF;  // inverte o estado dos led
            __delay_ms(5);       // por tentativa e erro foi encontrado que 5ms+serial=100ms
        }
    }
    
}
