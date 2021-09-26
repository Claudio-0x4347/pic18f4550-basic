/*
 * Arquivo: questao_01.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * OBS: COMPILAR O ARQUIVO EM C99 E HABILITAR APENAS OS MODULOS LM35 E QUESTAO1
 */      
#include <pic18f4550.h>
// Ajusta a frequ�ncia do oscilador para a fun��o_delay())
#define _XTAL_FREQ 4000000

// defini��o para as portas
#define ENTRADA     1
#define SAIDA       0

// cria um alias para o led na porta D0
#define LED LATD0

// Bibliotecas utilizadas
#include <xc.h>
#include "lcd.h"
#include "Temperatura/LM35.h"

// Configura��es de pr�-compila��o
#pragma config FOSC = INTOSC_EC     // habilita o oscilador interno
#pragma config WDT = OFF            // desabilita o watchdog timer
#pragma config MCLRE = OFF          // desabilita o pino de reset(Circuito)

// prototipo de fun��es
void configurarInterrupcoes(void);
void imprimirTemperatura(double temperatura);

void main(void)
{
    // configura o oscilador interno em 4MHz
    OSCCON = 0b01100010;

    // configura a interrup��o do timer 2 que controla o piscar do LED
    configurarInterrupcoes();
    
    // configura o LCD
    TRISD = SAIDA;
    Lcd_Init();
    Lcd_Set_Cursor(1,1);                    // coloca o cursor na linha1
    
    // configura o conversor adc
    configuraLM35();
    
    // configura o motor cc e o LED
    TRISC = SAIDA;
    TRISD = SAIDA;
    LED = 0;    // desliga o LED
    
    // inicializa a variavel de temperatura
    double temperatura;
    
    /* Loop infinito*/
    while(1)
    {       
        temperatura = lerLM35();
        imprimirTemperatura(temperatura);
        
        // posiciona o cursor para a mensagem que ser� escolhida
        Lcd_Set_Cursor(2,1);
        
        // verifica o valor da temperatura lida
        if(temperatura>=80)
        {
            LATC = 0b00010010;          // liga o motor cc em velocidade m�xima
            Lcd_Write_String("      Muito Alta");
        }else if(temperatura>20)
        {
            LATC = 0;                   // desliga o motor cc
            Lcd_Write_String("  Valor Adequado");
        }else
        {
            TMR2ON = 1;     // dispara a contagem
            Lcd_Write_String("     Muito Baixa");
            continue;       // impede que a interrup��o do led desabilite
                            // retornando o fluxo para o inicio do loop
        }
        
        // desabilita a interrup��o do timer 2
        TMR2ON = 0;     // dispara a contagem
        LED = 0;
    }
    
}

void __interrupt() myIsr(void)
{
    static uint8_t segundos = 0;
    if(TMR2IF)
    {
        if(++segundos>=100)
        {
            LED = !LED;             // inverte o estado do LED
            segundos = 0;
        }
        TMR2IF = 0;  // limpa a flag da interrup��o
    }
}

/*  Entrada:
 *  Sa�da:
 *  Descri��o:  Habilita a interrup��o do timer 2 em um intervalo de tempo 1ms.
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
    TMR2IE = 1;                 // habilita a interrup��o por timer 2, pisca o LED
}

/*  Entrada: temperatura retornada do LM35.
 *  Sa�da:
 *  Descri��o: Imprime na primeira linha do LCD a mensagem com a temperatura.
 */
void imprimirTemperatura(double temperatura)
{
    static char mensagem[16];
    sprintf(mensagem, "%16.2f", temperatura);
    Lcd_Set_Cursor(1, 1);                   // coloca o cursor na primeira linha
    Lcd_Write_String(mensagem);
}
