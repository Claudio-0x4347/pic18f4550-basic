#define _XTAL_FREQ 20000000  

#include <xc.h>
#include <stdio.h>
#include <string.h>

#pragma config FOSC = INTOSC_EC         // Osciladorinterno
#pragma configWDT  = OFF               // Watchdog Timer desligado
#pragma config MCLRE = OFF              // Master Clear desabilitado
#pragma config PBADEN = OFF             // Desliga o conversor AD da Porta B

float distancia;
char linha1[32], linha2[32];
int tempo;
char caracter;
bit flag_interrupcao = 0;

void setup_Int(){
GIE = 1;   				// GIE: Global InterruptEnable
    PEIE = 1;   				//  Habilita interrupção de periféricos
    RCIE = 1;			//habilita interrupção de recepção
    TXIE = 0;			//deixa interrupção de transmissão desligado
}

void interrupt Serial(void)			//vetor de interrupção
 {
caracter = RCREG;				// Lê caractere recebido do registrador
flag_interrupcao = 1;			// Habilita variável indicando que houve recepção
     RCIF = 0;					// Limpa flag de interrupção de recepção
 }

void inicializa_Serial(void)
{
	RCSTA = 0X90; 		// Habilita porta serial, recepção de 8 bits em modo contínuo, assíncrono.
    TXSTA = 0X24;
    SPBRG = 25;         // esse registrador, carregado com o ?valor? calculado, define o baud rate
}

void envia_serial (char valor)
{
    TXIF = 0;					// limpa flag que sinaliza envio completo.
    TXREG = valor;				// Envia caractere desejado à porta serial
while(TXIF ==0){       
    }
    __delay_ms(1);
}

void envia_texto_serial (const char frase[])
{
char indice = 0;				// índice da cadeia de caracteres
char tamanho = strlen(frase);			// tamanho total da cadeia a ser impressa

while(indice< tamanho ) {			// verifica se todos foram impressos
	envia_serial (frase[indice]);			// Chama rotina que escreve o caractere
indice++;					// incrementa índice
     }
}

void setupTmr0() {
    T08BIT = 0;             // Modo 16 bits
    T0CS = 0;               // Fonte INTERNA de clock = temporizador
    T0SE = 0;               // Incremento na subida do clock externo    
    PSA = 1;                // Desabilita Prescaler
    TMR0L = 0; 
    TMR0H = 0;                    
    TMR0IF = 0;
    TMR0ON = 0;             // Mantém o Timer0 desligado, inicialmente
}                           

void SuperDelay(long counter) {				
counter = counter / 10;                  
for (long i = 1; i<= counter; i++) {		
        __delay_ms(10);						
    }
}

void main(void) {
	OSCCON = 0b01100000;		// Oscilador a 4 MHz (1 tick do timer = 1 us)
TRISAbits.RA3 = 0;          // Led 2
    TRISBbits.RB3 = 1;          // RB3 é entrada do Echo
    TRISBbits.RB4 = 0;          // RB4 é saída para o Trigger
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;		 // configura RC7 e RC6 como entrada
    TRISD = 0;

setup_Int();
inicializa_Serial();
setupTmr0();				// Função de configurar timer 0

envia_texto_serial("Uso do Sensor Ultrassônico\n\r");

while(1) { 				// Loop infinito    
        TMR0 = 0;
        LATBbits.LATB4 = 1;   	// Sinal para o Trigger do 
        __delay_ms(1);
        LATBbits.LATB4 = 0;   	// Sinal para o Trigger do  

while (RB3 == 0){           
        }
        TMR0ON = 1;
while (RB3 == 1){           		// Aguarda retorno do sinal
}
        TMR0ON = 0; 
tempo = TMR0;
distancia = (340.0/20000.0)*tempo;      // cm

sprintf(linha2,"\n\rDistancia: %3.2f cm", distancia);
envia_texto_serial(linha2);

if (distancia < 10){
	LATA3 = !LATA3;					// Pisca o Led2
	LATD = 1;					// Todos os Leds ligados
        }
else{
	LATA3 = 0;						// Desliga o Led2            
        }
if (distancia >= 10 && distancia < 20){

        }
if (distancia >= 20 && distancia < 30){

        }       
if (distancia >= 30 && distancia < 40){

        }        
if (distancia >= 40){

        }                
SuperDelay(100);
	}
return;
}
