#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libLCD.h"

void initIO(void) {
    
}

/*
 
 Created By:
 
 .------..------..------..------..------.
 |M.--. ||A.--. ||G.--. ||I.--. ||C.--. |
 | (\/) || (\/) || :/\: || (\/) || :/\: |
 | :\/: || :\/: || :\/: || :\/: || :\/: |
 | '--'M|| '--'A|| '--'G|| '--'I|| '--'C|
 `------'`------'`------'`------'`------'
 
 
 ADC Sensor IR
 Calibracion Manual
 Datos Calibracion y Curva .xls en la
 carpeta de este archivo
 
 LCD_Data ---> DDRD
 LCD_RS-RW-EN ---> Pin0-Pin1-Pin2, DDRC
 ADC_SensorIR ---> Pin0, DDRA
 Resolucion ADC = 8bits
 
 MCU Receiver Code
 Receives data from master
 Prints on LCD, Moves DC Motor
 30cm ---> DCM Stand by
 30cm + -> DCM Moves CW
 30cm - -> DCM Moves CCW
 */


/*
 Inicializacion USART
 */

// define some macros
#ifndef F_CPU
#define F_CPU 1000000UL                            // set the CPU clock
#endif
#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

// function to initialize UART
void uart_init (void)
{
    UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRRL = BAUDRATE;                           // set baud rate
    UCSRB|= (1<<TXEN)|(1<<RXEN);                // enable receiver and transmitter
    UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
}



/*
 Funcion Para Enviar Datos -- NOT USE HERE
 

void uart_transmit (unsigned char data)
{
    while (!( UCSRA & (1<<UDRE)));                // wait while register is free
    UDR = data;                                   // load data in the register
}
*/

/*
 Funcion Para Recibir Datos
*/
 unsigned char uart_recieve (void)
 {
 while(!(UCSRA) & (1<<RXC));                   // wait while data is being received
 return UDR;                                   // return 8-bit data
 }


/*
 Fin Inicializaciones
*/




int main(void) {
    initIO();
    
    uart_init();
    LCD_init();
    
    
    
    LCD_wait();
    LCD_write("Created by");
    LCD_wait();
    LCD_command(0xC0);
    LCD_wait();
    LCD_write("Magic");
    _delay_ms(1000);
    LCD_command(0b00000001);
    LCD_wait();
    LCD_write("Cargando Sensor");
    LCD_wait();
    LCD_command(0xC0);
    LCD_wait();
    for (int load=1; load<=16; load++)
    {
        LCD_write("-");
        _delay_ms(100);
        if (load==16)
        {
            LCD_command(0b00000001);
            LCD_write("Carga Completa");
            _delay_ms(1000);
            LCD_command(0b00000001);
            LCD_wait();
        }
    }
    //LCD_write("Leyendo:");
    LCD_wait();
     
    
    
    unsigned char a;
    char buffer[10];
    
    while (1)
    {
        a=uart_recieve();                   // save the received data in a variable
        
        
        _delay_ms(100);
        //char buffer[4];
        //itoa(a, buffer, 10);
        LCD_goTo(1, 2);
        LCD_wait();
        LCD_write(a);
        LCD_wait();
        
        a = 0;
        
        /*
        switch (a)                          // Prints the value
        {
            case 144:
                LCD_goTo(1, 2);
                LCD_write("5");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 143:
                LCD_goTo(1, 2);
                LCD_write("6");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 133 ... 142:
                LCD_goTo(1, 2);
                LCD_write("7");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 125 ... 132:
                LCD_goTo(1, 2);
                LCD_write("8");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 110 ... 124:
                LCD_goTo(1, 2);
                LCD_write("9");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 95 ... 109:
                LCD_goTo(1, 2);
                LCD_write("10");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 85 ... 94:
                LCD_goTo(1, 2);
                LCD_write("11");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 78 ... 84:
                LCD_goTo(1, 2);
                LCD_write("12");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 70 ... 77:
                LCD_goTo(1, 2);
                LCD_write("13");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 62 ... 69:
                LCD_goTo(1, 2);
                LCD_write("14");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 57 ... 61:
                LCD_goTo(1, 2);
                LCD_write("15");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 50 ... 56:
                LCD_goTo(1, 2);
                LCD_write("16");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 46 ... 49:
                LCD_goTo(1, 2);
                LCD_write("17");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 43 ... 45:
                LCD_goTo(1, 2);
                LCD_write("18");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 40 ... 42:
                LCD_goTo(1, 2);
                LCD_write("19");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 38 ... 39:
                LCD_goTo(1, 2);
                LCD_write("20");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 34 ... 37:
                LCD_goTo(1, 2);
                LCD_write("21");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 32 ... 33:
                LCD_goTo(1, 2);
                LCD_write("22");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 29 ... 31:
                LCD_goTo(1, 2);
                LCD_write("23");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 27 ... 28:
                LCD_goTo(1, 2);
                LCD_write("24");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 24 ... 26:
                LCD_goTo(1, 2);
                LCD_write("25");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 22 ... 23:
                LCD_goTo(1, 2);
                LCD_write("26");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 20 ... 21:
                LCD_goTo(1, 2);
                LCD_write("27");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 18 ... 19:
                LCD_goTo(1, 2);
                LCD_write("28");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 16 ... 17:
                LCD_goTo(1, 2);
                LCD_write("29");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 15:
                LCD_goTo(1, 2);
                LCD_write("30");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 14:
                LCD_goTo(1, 2);
                LCD_write("32");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 13:
                LCD_goTo(1, 2);
                LCD_write("35");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 12:
                LCD_goTo(1, 2);
                LCD_write("37");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 11:
                LCD_goTo(1, 2);
                LCD_write("38");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 10:
                LCD_goTo(1, 2);
                LCD_write("40");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 9:
                LCD_goTo(1, 2);
                LCD_write("42");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 8:
                LCD_goTo(1, 2);
                LCD_write("45");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 7:
                LCD_goTo(1, 2);
                LCD_write("46");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 6:
                LCD_goTo(1, 2);
                LCD_write("48");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 5:
                LCD_goTo(1, 2);
                LCD_write("50");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 4:
                LCD_goTo(1, 2);
                LCD_write("53");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 3:
                LCD_goTo(1, 2);
                LCD_write("55");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 2:
                LCD_goTo(1, 2);
                LCD_write("57");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
            case 1:
                LCD_goTo(1, 2);
                LCD_write("58");
                LCD_goTo(1, 2);
                LCD_write("cm");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
                
                
            default:
                LCD_goTo(1, 2);
                LCD_write("Fuera de Rango");
                LCD_goTo(1, 2);
                LCD_write("   ");
                break;
        }
         
        */
        
        /*
        LCD_goTo(1, 2);
        LCD_write("Buffer ");
        LCD_goTo(1, 2);
        LCD_write(buffer);
        LCD_goTo(1, 2);
        LCD_write("   ");                   // display the received value on LCD
        */
        
    }
}

