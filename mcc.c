/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F23K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB             :  MPLAB X 5.45
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

#include "mcc.h"
#include <stdint.h>
#include <string.h>


void SYSTEM_Initialize(void)
{

    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    EUSART1_Initialize();
    EUSART2_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; IRCF 16MHz_HFINTOSC; IDLEN disabled; 
    OSCCON = 0x70;
    // PRISD enabled; SOSCGO disabled; MFIOSEL disabled; 
    OSCCON2 = 0x04;
    // INTSRC enabled; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x80;
}
#define uint16_t unsigned int
#define uint32_t unsigned int 
typedef enum {
     byteint,
     length,
     data,
     chek,
     oro,
     plata,        
         
 }Estados_t;
uint16_t len;
int count = 0;
int i = 0; 
int buffer[];
int pp=0;
uint32_t datos;
char bu[20];
char dato[4];

//funcion para la trama 
void leer_trama(float byte){
    
     byte= EUSART2_Read();
     //EUSART1_Write(byte);
     EUSART1_Puts("\r\n");
      sprintf(bu,"%d",(int)byte);
      EUSART1_Puts(bu); 
     static Estados_t Estado = byteint;
     switch (Estado){
         case byteint: 
              if(byte==0X7E){
              PORTBbits.RB1 = 1;
              EUSART2_Puts("\r\n estado byteint\r\n");
             // EUSART1_Puts("\r\n");
              // sprintf(bu,"%d",(int)byte);
             // EUSART1_Puts(bu);
             __delay_ms(500);
              Estado = length; 
              }
              break;
         case length:
              len =(int)byte; 
              // EUSART1_Puts("\r\n");
            //  sprintf(bu,"%d",(int)len);
             // EUSART1_Puts(bu);
              pp=1;
               Estado =data;
               break;
        case data:     
            if(i<len){
                buffer[i]=(int)byte;
                //EUSART1_Puts("\r\n");
              // sprintf(bu,"%d",(int)buffer[i]);
              // EUSART1_Puts(bu); 
               i+=1;
            }      
              break; 
     
        
            
     }
           
              
             
   
        
     

}















     

// LIBRERIA 



/**
 End of File
*/
