/*
 * File:   main.c
 * Author: LucasGabriel
 *
 * Created on 26 de Janeiro de 2023, 22:21
 */

/**
 *  -> Sync         =   '['                              (Inicio)
 *  -> EDD          =   'LED'/'LE'                       (Periferico)
 *  -> SubEDD       =   'B'/'ADC'                        (PORT)
 *  -> SubSubEDD    =   0~7                              (PINO)
 *  -> Status       =   '0' -> Desligado
 *                      '1' -> Ligado
 *  -> Finalizador  =   ']'                         (Fim do Pacote)
 * 
 * Exemplo:
 *      Pacote: "[LEDB01]" 
 *      Pacote: "[LEADC0]"
*/

#include "system.h"
#include "interrupt_manager.h"

void main(void) 
{
    System_Initializer();
    while(1)
    {
        
    }
}
