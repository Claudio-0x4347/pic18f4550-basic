/*
 * Código em C99
 * Arquivo: serial.h
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * Descrição: Conjunto de funções para trabalhar com a serial do
 * microcontrolador PIC18F4550
 */

// Defições para o TRIS
#define SAIDA           0
#define ENTRADA         1

// Modos de operação da serial
#define HIGH_BOUND_RATE 1
#define LOW_BOUND_RATE  0


/*  Entradas:   Taxa de dados, modo UART
 *  Saídas:
 *  Descrição:  Define as portas Tx e Rx como saída e inicializa o modo UART
 *              para transmissão e recepção.
 */
void inicializarUART(long bound_rate, unsigned char modo);

/*  Entradas:   caracter
 *  Saídas:
 *  Descrição:  Carrega o registrador TXREG com o registrador a ser enviado e
 *              aguarda a transmissão.
 */
void enviarCaracter(const char c);

/*  Entradas:   ponteiro para string constante
 *  Saídas:
 *  Descrição:  Percorre a string eviando os caracteres para serial até
 *              encontrar o caracter nulo.
 */
void enviarString(const char *mensagem);