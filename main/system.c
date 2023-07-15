/*
 * File:   system.c
 * Author: LucasGabriel
 *
 * Created on 26 de Janeiro de 2023, 22:25
 */

#include "adc.h"
#include "system.h"

static void Oscilator_Initializer(void);
static void Pin_Initializer(void);
static void UART_Initializer(void);
static void Interrupt_Initializer(void);

void System_Initializer(void) 
{
    Oscilator_Initializer();
    Pin_Initializer();
    UART_Initializer();
    Interrupt_Initializer();
    ADC_Initializer();
}

static void Oscilator_Initializer(void)
{
    OSCCON  =   0x00;
}

static void Pin_Initializer(void)
{
    TRISA   = 0xFF;
    TRISB   = 0xFC;
    TRISC   = 0xBF;
    TRISD   = 0xFF;
    TRISE   = 0x07;
    
    LATA    = 0x00;
    LATB    = 0x00;
    LATC    = 0x00;
    LATD    = 0x00;
    LATE    = 0x00;
    
    ADCON1  |= 0x07;       
}

static void UART_Initializer(void)
{
    //Transmition
    TXSTAbits.TXEN          =   0b1;
    RCSTAbits.CREN          =   0b1;
    RCSTAbits.SPEN          =   0b1; //Habilita o periferico serial (valido tanto pra tx quanto para rx)
    
    //Bountrate Calculate****************************************
    uint32_t boundRate = 9600;
    SPBRG                   =   (uint8_t)(((_XTAL_FREQ/boundRate)/64)-1);
    SYNC                    =   0x00;
    BRGH                    =   0x00;
    //***********************************************************
    
    RCREG                   =   0x00;
    TXREG                   =   0x00;
    PIR1bits.TXIF           =   0b0;
    PIR1bits.RCIF           =   0b0;
}

static  void Interrupt_Initializer(void)
{
    INTCON1bits.GIEH        =   0b1;
    INTCON1bits.GIEL        =   0b1;
    RCONbits.IPEN           =   0b1;
    
    PIR1bits.RCIF           =   0b0;
    IPR1bits.RC1IP          =   0b1;
    PIE1bits.RCIE           =   0b1;
}