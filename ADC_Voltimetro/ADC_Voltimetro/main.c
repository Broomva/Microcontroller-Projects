#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libLCD.h"
#include <stdlib.h>

/*
 
 Created By:
 
 .------..------..------..------..------.
 |M.--. ||A.--. ||G.--. ||I.--. ||C.--. |
 | (\/) || (\/) || :/\: || (\/) || :/\: |
 | :\/: || :\/: || :\/: || :\/: || :\/: |
 | '--'M|| '--'A|| '--'G|| '--'I|| '--'C|
 `------'`------'`------'`------'`------'
 
 
 ADC Voltimetro
 Valores 0-255, 0-5V
 
 LCD_Data ---> DDRD
 LCD_RS-RW-EN ---> Pin0-Pin1-Pin2, DDRC
 ADC_SensorIR ---> Pin0, DDRA
 Resolucion ADC = 8bits
 */

void initIO(void) {
    
}

int main(void)
{
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
    LCD_write("Cargando Datos");
    LCD_wait();
    LCD_command(0xC0);
    LCD_wait();
    for (int load=1; load<=16; load++)
    {
        LCD_write("-");
        _delay_ms(50);
        if (load==16)
        {
            LCD_command(0b00000001);
            LCD_write("Carga Completa");
            _delay_ms(1000);
            LCD_command(0b00000001);
            LCD_wait();
        }
    }

    LCD_write("Leyendo:");
    LCD_wait();
    
    
    //Configure the ADC
    ADCSRA |= 1 <<ADPS2;
    ADMUX |= 1 <<ADLAR;
    ADMUX |= 1 <<REFS0;
    ADCSRA |= 1 <<ADIE;
    ADCSRA |= 1 <<ADEN;
    
    sei();
    
    while (1)
    {
        ADCSRA |= 1 <<ADSC;
    }
    
    
}

void printfloat(float a , int precision)
{
    LCD_command(0b00000001);
    int roundoff = a;   // getting rounded integer
    float remainder = 0; // declaring the numbers to the right of the decimal point
    int whole_remainder = 0; // declaring remainder variable
    remainder = a - roundoff; // calculating remainder
    
    char whole[6];
    itoa(roundoff,whole,10);
    
    
    LCD_write(whole);  // writing numbers to the left of the decimal point to the lcd
    LCD_write(".");  // writing a dot
    
    whole_remainder = remainder*(pow(10,precision)); // making the decimals into whole integers by multiplying
    
    char decimals[6];
    itoa(whole_remainder,decimals,10);
    
    
    LCD_write(decimals);  // writing the decimals to the lcd
    
    
    
}





ISR(ADC_vect)
{
    _delay_ms(100);
    char adcResult[4];
    char voltiResult[4];
    itoa(ADCH, adcResult, 10);
    
    /*
    for (int volti = 0; volti<=255; volti=volti+ADCH)
    {
        
    }
    */
    
    int Volti, Voltu;
    char num1[3], num2[3];
    
    Volti = 10*(ADCH*4.47)/255;
    //Volti = 10*(ADCH-2.2)/57.5;
    //float e = 2.718281828459045235360287471352662497757247093699959574966967;
    //Volti = e(pow((250*ADCH-10317)/33030));
    Voltu = Volti/10;
    
    float Acoma = Volti%10;
    float Dcoma = Voltu%10;
    
    
    itoa(Acoma, num1, 10);
    itoa(Dcoma, num2, 10);
    
    
    
    LCD_goTo(1, 2);
    LCD_write(num2);
    LCD_goTo(1, 2);
    LCD_write(".");
    LCD_goTo(1, 2);
    LCD_write(num1);
    LCD_goTo(1, 2);
    LCD_write(" ");
    LCD_goTo(1, 2);
    LCD_write("Vdc ");
    
    LCD_goTo(1, 2);
    LCD_write("ADCH ");
    LCD_goTo(1, 2);
    LCD_write(adcResult);
    LCD_goTo(1, 2);
    LCD_write("   ");
    
    
}


/*
 
 
 
  ____           _             _____               _
 / ___|__ _ _ __| | ___  ___  | ____|___  ___ ___ | |__   __ _ _ __
| |   / _` | '__| |/ _ \/ __| |  _| / __|/ __/ _ \| '_ \ / _` | '__|
| |__| (_| | |  | | (_) \__ \ | |___\__ \ (_| (_) | |_) | (_| | |
 \____\__,_|_|  |_|\___/|___/ |_____|___/\___\___/|_.__/ \__,_|_|
 
 
 
 */
