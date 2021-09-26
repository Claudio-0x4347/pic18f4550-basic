/*
 * Código em C99
 * Arquivo: LM35.c
 * Autor:   Claudio Gabriel de Lemos Almeida
 * Criado em 9 de Dezembro de 2020, 18:30
 */
#ifndef _PIC18F4550_H_
    #include <pic18f4550.h>
#endif

/*  Entrada:
 *  Saída:
 *  Descrição:  Inicializa o LM35 na porta A01.
 */
void configuraLM35(void)
{
    ADCON1bits.VCFG = 0b01;         // referência no Vss e AN3(1.5V))
    ADCON0 = 0b0000001;             // ADC habilitado, canal 0
    ADCON2 = 0b10010100;            // justificado a direita, 4Tad, Fosc/4
}

/*  Entrada:
 *  Saída:
 *  Descrição:  Efetua a leitura do conversor AD e retorna o valor da temperatura
 *              convertida.
 */
double lerLM35(void)
{
    GODONE = 1;                     // inicia a leitura do ADC
    while(GODONE);                  // espera a leitura
    return (1.5*100*ADRES)/1023.0;  // covnerte para temperatura
}