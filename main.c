

#include "mcc_generated_files/mcc.h"
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define uint16_t unsigned short

typedef enum {
     byteint,
     length,
     data, 
     cost,
     enviar, 
     labview,        
    }Estados_t;
           
char cadena[20];    
char prt;    
float byte; 
float chk;
float si;
uint16_t len; 
int count = 0;
int i = 0;
uint16_t len;
uint16_t res;
float array[30];
int oro=13;
float toto =16.3;
/*
                       Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
     PORTBbits.RB1 = 0;
     PORTBbits.RB2 = 0;
    while (1)
    {
       byte = EUSART2_Read();
       
     static Estados_t Estado = byteint;
     
     switch (Estado){
         case byteint: 
              if(byte==0X7E){
              PORTBbits.RB1 = 1;
              EUSART2_Puts("\r\n estado byteint\r\n");
             __delay_ms(500);
              Estado = length; 
              }
              break;
         case length:
              len =(short)byte;
              ++count;
              if(count==2){
                 res=len|(short)byte<<8; 
                 PORTBbits.RB2 = 1;
                 EUSART2_Puts("\r\n estado length\r\n");
                 Estado = data;
                 count=0;
                  __delay_ms(500);
              }
               break;
         case data:
             if (i<1){
                  array[i++]=byte;
                  PORTBbits.RB3 = 1;
                 
                 __delay_ms(500);}
              Estado = cost;
               break;
         case cost:
             if (i==1){
                  EUSART2_Puts("\r\n lista la data\r\n");
                  Estado = enviar;
                 EUSART1_Write("hola");
             }
              else {Estado = byteint;}
             break;
         case enviar:
             for (int j=0;j<=2;j+=1){
                 prt=array[j];
                 EUSART1_Puts("\r\n41826666;\r\n");
                 EUSART1_Puts("\r\n42820666;\r\n");
                
                 }
             Estado = labview; 
             break;
             
         case labview:
                 EUSART2_Puts("\r\n estado labview;\r\n");
                 EUSART1_Rx_String(cadena,20);
                 if (strstr(cadena,"J")){
                     PORTAbits.RA1 = 1;
                     PORTBbits.RB4 = 1;
                       __delay_ms(500);
                                }
                 if (strstr(cadena,"U")){
                     PORTAbits.RA2 = 1;
                     PORTBbits.RB5 = 1;
                       __delay_ms(500);
                                }
                 if (strstr(cadena,"JUAN")){
                     PORTAbits.RA3 = 1;
                     PORTBbits.RB2 = 1;
                       __delay_ms(500);
                                }
                 if (strstr(cadena,"DAVID")){
                     PORTAbits.RA4 = 1;
                     PORTBbits.RB1 = 1;
                       __delay_ms(500);
                                }
                  if (strstr(cadena,"G")){
                     PORTAbits.RA5 = 1;
                     PORTBbits.RB3 = 1;
                       __delay_ms(500);
                                }
                 break;
        }     
            
           
               
     
     
     
    }
}
/**
 End of File
*/