/*
 * C�digo em C99
 * Arquivo: LM35.h
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * Descri��o: Conjunto de fun��es para trabalhar com o CI LM35 na porta A0 do
 * microcontrolador PIC18F4550
 */

/*  Entrada:
 *  Sa�da:
 *  Descri��o:  Inicializa o LM35 na porta A01.
 */
void configuraLM35(void);

/*  Entrada:
 *  Sa�da:
 *  Descri��o:  Efetua a leitura do conversor AD e retorna o valor da temperatura
 *              convertida.
 */
double lerLM35(void);