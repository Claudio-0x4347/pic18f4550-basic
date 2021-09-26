/*
 * Código em C99
 * Arquivo: LM35.h
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 * 
 * Descrição: Conjunto de funções para trabalhar com o CI LM35 na porta A0 do
 * microcontrolador PIC18F4550
 */

/*  Entrada:
 *  Saída:
 *  Descrição:  Inicializa o LM35 na porta A01.
 */
void configuraLM35(void);

/*  Entrada:
 *  Saída:
 *  Descrição:  Efetua a leitura do conversor AD e retorna o valor da temperatura
 *              convertida.
 */
double lerLM35(void);