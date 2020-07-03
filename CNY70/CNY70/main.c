#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libLCD.h"

void initIO(void) {
	
}

char adcResult;

int main(void) {
	initIO();
    
    DDRB |= 0<<0;
    DDRC |= 0<<7;
    
    LCD_init();
    LCD_wait();
    LCD_write("CNY70");
    
    int cn;
    
    //Configure the ADC
    ADCSRA |= 1 <<ADPS2;
    ADMUX |= 1 <<ADLAR;
    ADMUX |= 1 <<REFS0;
    ADCSRA |= 1 <<ADIE;
    ADCSRA |= 1 <<ADEN;
    
    ADCSRA |= 1 <<ADSC;
    sei();
    
    
    while (1)
    {
        /*
        int adccny;
        while (ADCH == 255)
        {
            adccny = 1;
        }
        
        while (ADCH != 255)
        {
            adccny = 0;
        }
        
        char adccnyr [4];
        itoa(adccny, adccnyr, 10);
        LCD_goTo(8, 1);
        LCD_write("ADCH ");
        LCD_goTo(8, 1);
        LCD_write(adccnyr);
        LCD_goTo(8, 1);
        LCD_write("   ");
        */
        
        if (adcResult == "1")
        {
            PORTC |= 1<<7;
        }
        
        if (adcResult == "0")
        {
            PORTC |= 0<<7;
        }
        
    
    }



}

ISR(ADC_vect)
{
    
    
    //itoa(ADCH, adcResult, 10);
    if (ADCH == 255)
    {
        adcResult = "1";
    }
    else
    {
        adcResult = "0";
    }
    
    
    LCD_goTo(1, 2);
    LCD_write("ADCH ");
    LCD_goTo(1, 2);
    LCD_write(adcResult);
    LCD_goTo(1, 2);
    LCD_write("   ");
    
    
    
    ADCSRA |= 1 <<ADSC;
    
    
    
}
