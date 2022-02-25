/**
  EUSART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart2.c

  @Summary
    This is the generated driver implementation file for the EUSART2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F23K22
        Driver Version    :  2.1.1
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/
#include "eusart2.h"

volatile eusart2_status_t eusart2RxLastError;

/**
  Section: EUSART2 APIs
*/

void (*EUSART2_FramingErrorHandler)(void);
void (*EUSART2_OverrunErrorHandler)(void);
void (*EUSART2_ErrorHandler)(void);

void EUSART2_DefaultFramingErrorHandler(void);
void EUSART2_DefaultOverrunErrorHandler(void);
void EUSART2_DefaultErrorHandler(void);

void EUSART2_Initialize(void)
{
    // Set the EUSART2 module to the options selected in the user interface.

    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON2 = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA2 = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA2 = 0x24;

    // 
    SPBRG2 = 0xA0;

    // 
    SPBRGH2 = 0x01;


    EUSART2_SetFramingErrorHandler(EUSART2_DefaultFramingErrorHandler);
    EUSART2_SetOverrunErrorHandler(EUSART2_DefaultOverrunErrorHandler);
    EUSART2_SetErrorHandler(EUSART2_DefaultErrorHandler);

    eusart2RxLastError.status = 0;

}

bool EUSART2_is_tx_ready(void)
{
    return (bool)(PIR3bits.TX2IF && TXSTA2bits.TXEN);
}

bool EUSART2_is_rx_ready(void)
{
    return (bool)(PIR3bits.RC2IF);
}

bool EUSART2_is_tx_done(void)
{
    return TXSTA2bits.TRMT;
}

eusart2_status_t EUSART2_get_last_status(void){
    return eusart2RxLastError;
}

uint8_t EUSART2_Read(void)
{
    while(!PIR3bits.RC2IF)
    {
    }

    eusart2RxLastError.status = 0;
    
    if(1 == RCSTA2bits.OERR)
    {
        // EUSART2 error - restart

        RCSTA2bits.CREN = 0; 
        RCSTA2bits.CREN = 1; 
    }

    return RCREG2;
}

void EUSART2_Write(uint8_t txData)
{
    while(0 == PIR3bits.TX2IF)
    {
    }

    TXREG2 = txData;    // Write the data byte to the USART.
}




void EUSART2_DefaultFramingErrorHandler(void){}

void EUSART2_DefaultOverrunErrorHandler(void){
    // EUSART2 error - restart

    RCSTA2bits.CREN = 0;
    RCSTA2bits.CREN = 1;

}

void EUSART2_DefaultErrorHandler(void){
}

void EUSART2_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART2_FramingErrorHandler = interruptHandler;
}

void EUSART2_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART2_OverrunErrorHandler = interruptHandler;
}

void EUSART2_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART2_ErrorHandler = interruptHandler;
}

// enviarun char datos para labview
void EUSART2_Puts(char *str){ // "hola\0"
    
    while(*str != '\0'){
        EUSART2_Write(*str++);
    } 
}
// funcion complementaria para RX_String
unsigned char EUSART2_Rx(void)
{
    while(!PIR1bits.RCIF)
    {
    }
    if(1 == RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    return RCREG;
}
// practica 
void EUSART2_Rx_String(char* Buffer, unsigned int tama)
{
    unsigned int con_t=0;
    while(*(Buffer-1)!= '\n')     // Mientras no llegue el caracter deseado
    {
        con_t++;
        *Buffer++=EUSART2_Rx();      // Sigue almacenando en el buffer
        if(con_t>=tama) break;
    }
    *--Buffer=0;                  // Coloca un cero al final para que sea una cadena
}

/**
  End of File
*/