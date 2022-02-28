

#include "mcc_generated_files/mcc.h"
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define uint16_t unsigned int
#define uint32_t unsigned int 

typedef enum {
     byteint,
     length,
     data, 
     cost,
     enviar, 
     labview,        
    }Estados_t;
           
char cadena[20];    
char prt[];    
float byte; 
float chk;
float si;
uint16_t len; 
int count = 0;
int i = 0;
uint16_t len;
uint16_t res;
float array[30];
int k=0;
int suma=0;
int valor[];
char bu[20];
uint32_t VRI;
int C1;
int fin;
int  sumaVariable=0;
float ret;
int rr=24;

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
              sprintf(bu,"%d",(int)byte);
             EUSART1_Puts(bu);
             EUSART1_Puts(" INICIO\r");
             __delay_ms(500);
              Estado = length; 
              }
              break;
         case length:
              len =(int)byte;
             sprintf(bu,"%d",(int)len);
             EUSART1_Puts(bu);
              EUSART1_Puts(" LONGITUD\r\n");
             for(int c=0;c<len;c+=1){
               si=EUSART2_Read(); 
               prt[c]=si;;
             }   PORTBbits.RB2 = 1;
                 EUSART2_Puts("\r\n llenado \r\n");
                 Estado = data;
                  __delay_ms(500);
             
               break;
         case data:
             for(int j=0;j<len;j+=1){
                 if(prt[j]==0XC1){
                 C1=j;}
                 if (prt[j]==0X66){
                 fin=j;}
                 if(prt[j]==0X41){
                 sumaVariable= sumaVariable+1;}}
             while(len--){
                 suma+=prt[k];
                 if(suma & 0XFF){
                     suma&=0xFF;
                     suma++;
                 }
                 k+=1;
             }ret=(suma&0XFF); //CHECSUM
             sprintf(bu,"%d",(int)ret);
             EUSART1_Puts(bu);
             EUSART1_Puts(" CHECSUM");
              Estado = cost;
               break;
         case cost:
             EUSART1_Puts("\rDATOS\r");
             for (int caro=C1+1;caro<=fin+1;caro+=1){
                  sprintf(bu,"%d",prt[caro]);
                  EUSART1_Puts(bu);
                  EUSART1_Puts("\r\n"); }
             Estado = enviar;
             break;
         case enviar:
             
                sprintf(bu,"%d",(sumaVariable-1));
                  EUSART1_Puts(bu);
                 EUSART1_Puts("TOTAL DATOS");   
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