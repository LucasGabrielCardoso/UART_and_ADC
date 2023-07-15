/*
 * File:   interrupt_manager.c
 * Author: LucasGabriel
 *
 * Created on 12 de Julho de 2023, 21:25
 */


#include <xc.h>
#include <stdio.h>
#include "adc.h"
#include "interrupt_manager.h"
#include "system_config.h"

volatile uint8_t dta[20]        =   {0};
volatile uint8_t *pot           =   NULL;
volatile uint8_t _aux           =   0;   

static void Decodifica_Protocolo(void);
static void ReEnviaDados(void);


__interrupt() void Interrupt_High_Priority(void)
{
    uint8_t sdata   =   0x00;
    if(0b1  ==  PIR1bits.RC1IF && 0b1   ==  PIE1bits.RC1IE)
    {
        /*Tratamento de overflow*/
        if(1 == RCSTAbits.OERR)
        {
            RCSTAbits.CREN  =   0b0;
            RCSTAbits.CREN  =   0b1;
        }
        sdata   =   RCREG;
        TXREG1  =   sdata;
        while(0b0   ==  TXSTAbits.TRMT1);
        
        if('['  ==  sdata)
        {
            pot     =   dta;
            _aux    =   0x01;
        }
        else if(']' ==  sdata && 0x01 == _aux)
        {
            _aux    =   0x00;
            //Buffer cheio
            //Decodificar o pacote
            Decodifica_Protocolo();
        }
        else if(0x01    ==  _aux)
        {
            if((pot - dta) < 6)
            {
                *pot    =   sdata;
                ++pot;
            }
            else
                _aux    =   0x00;
            //nao podemos incrementar pot alem do comprimento de dta
        }
        
        PIR1bits.RC1IF  =   0b0;
    }
}

static void Decodifica_Protocolo(void)
{
    if('L'  ==  dta[0]  &&  'E'  ==  dta[1] &&  'D'  ==  dta[2])
    {
        if('B'   ==  dta[3])
        {
            switch(dta[4])
            {
                case '0':
                    PORTBbits.RB0   =   (dta[5] - '0');
                    __delay_ms(1);
                    dta[5]  =   (LATBbits.LATB0 + '0');
                    ReEnviaDados();
                    break;
                case '1':
                    PORTBbits.RB1   =   (dta[5] - '0');
                    __delay_ms(1);
                    dta[5]  =   (LATBbits.LATB1 + '0');
                    ReEnviaDados(); 
                    break;
            }
        }
    }
    else if('L'  ==  dta[0]  &&  'E'  ==  dta[1] &&  'A'  ==  dta[2] &&  'D'  ==  dta[3] &&  'C'  ==  dta[4])
    {
        uint16_t leitura_adc   =   0; 
        char     varADC[15]    =   {0};
        switch(dta[5])
        {
            case '0':
                leitura_adc    =   ADC_Get_Value(0);
                sprintf(varADC, "[AN0:%hu]", leitura_adc);
                for(uint8_t i   =   0x00; varADC[i] != '\0'; i++)
                {
                    TXREG1  =   varADC[i];
                    while(0b0   ==  TXSTAbits.TRMT1);
                }
                break;
        }
    }
}

static void ReEnviaDados(void)
{
        TXREG1  =   '[';
        while(0b0   ==  TXSTAbits.TRMT1);
        
        TXREG1  =   dta[0];
        while(0b0   ==  TXSTAbits.TRMT1);
        TXREG1  =   dta[1];
        while(0b0   ==  TXSTAbits.TRMT1);
        TXREG1  =   dta[2];
        while(0b0   ==  TXSTAbits.TRMT1);
        TXREG1  =   dta[3];
        while(0b0   ==  TXSTAbits.TRMT1);
        TXREG1  =   dta[4];
        while(0b0   ==  TXSTAbits.TRMT1);
        TXREG1  =   dta[5];
        while(0b0   ==  TXSTAbits.TRMT1);
        
        TXREG1  =   ']';
        while(0b0   ==  TXSTAbits.TRMT1);
}
