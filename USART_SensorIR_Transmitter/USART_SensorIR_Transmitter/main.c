#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
 
 MCU Transmitter Code
 Lee Valor en ADC-Sensor IR
 Send data to slave

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
    UBRRH = (BAUDRATE>>8);                          // shift the register right by 8 bits
    UBRRL = BAUDRATE;                               // set baud rate
    UCSRB|= (1<<TXEN);                              // enable transmitter
    UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);       // 8bit data format
}



/*
 Funcion Para Enviar Datos
 */

void uart_transmit (unsigned char data)
{
    while (!( UCSRA & (1<<UDRE)));                // wait while register is free
    UDR = data;                                   // load data in the register
}


/*
 Funcion Para Recibir Datos --- Not USE HERE
 
 unsigned char uart_recieve (void)
 {
 while(!(UCSRA) & (1<<RXC));                   // wait while data is being received
 return UDR;                                   // return 8-bit data
 }
 */



/*
 Fin Inicializaciones
 */




int main(void) {
    initIO();
    
    uart_init();
    
    /*
    //Configure the ADC
    ADCSRA |= 1 <<ADPS2;
    ADMUX |= 1 <<ADLAR;
    ADMUX |= 1 <<REFS0;
    ADCSRA |= 1 <<ADIE;
    ADCSRA |= 1 <<ADEN;
    
    sei();
    
    ADCSRA |= 1 <<ADSC;
    */
    
    while (1)
    {
        int Transfer = 5;
        uart_transmit(Transfer);
        _delay_ms(5000);
        Transfer = 230;
        uart_transmit(Transfer);
    }
}

/*

ISR(ADC_vect)
{
    _delay_ms(150);
    unsigned char adcResult[10];
    itoa(ADCH, adcResult, 2);
    int Transfer = 10;
    uart_transmit(Transfer);
    ADCSRA |= 1 <<ADSC;
}

*/