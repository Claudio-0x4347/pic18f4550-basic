/*
 * C�digo em C99
 * Arquivo: serial.h
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * Descri��o: Conjunto de fun��es para trabalhar com a serial do
 * microcontrolador PIC18F4550
 */

// Defi��es para o TRIS
#define SAIDA           0
#define ENTRADA         1

// Modos de opera��o da serial
#define HIGH_BOUND_RATE 1
#define LOW_BOUND_RATE  0


/*  Entradas:   Taxa de dados, modo UART
 *  Sa�das:
 *  Descri��o:  Define as portas Tx e Rx como sa�da e inicializa o modo UART
 *              para transmiss�o e recep��o.
 */
void inicializarUART(long bound_rate, unsigned char modo);

/*  Entradas:   caracter
 *  Sa�das:
 *  Descri��o:  Carrega o registrador TXREG com o registrador a ser enviado e
 *              aguarda a transmiss�o.
 */
void enviarCaracter(const char c);

/*  Entradas:   ponteiro para string constante
 *  Sa�das:
 *  Descri��o:  Percorre a string eviando os caracteres para serial at�
 *              encontrar o caracter nulo.
 */
void enviarString(const char *mensagem);