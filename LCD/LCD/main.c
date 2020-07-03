#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libLCD.h"


/*
 
 Created By:
 
 .------..------..------..------..------.
 |M.--. ||A.--. ||G.--. ||I.--. ||C.--. |
 | (\/) || (\/) || :/\: || (\/) || :/\: |
 | :\/: || :\/: || :\/: || :\/: || :\/: |
 | '--'M|| '--'A|| '--'G|| '--'I|| '--'C|
 `------'`------'`------'`------'`------'

 LCD_Data ---> DDRD
 LCD_RS-RW-EN ---> Pin0-Pin1-Pin2, DDRC
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
    LCD_write("Digite: ");
    LCD_wait();
    
    
    DDRA = 0b11110000;
    int leer;
    int indicador = 1;
    
    while(1)
    {
        
        
        //Columna 1 Indicadores
        PORTA = 0b10000000;
        _delay_us(10);
        leer = PINA;
        
        if (leer == 0b10001000)
        {
            //LCD_write("D");
            indicador = 4;
            while (leer==0b10001000) {leer=PINA;}
        }
        
        if (leer == 0b10000100)
        {
            //LCD_write("C");
            indicador = 3;
            while (leer==0b10000100) {leer=PINA;}
        }
        
        if (leer == 0b10000010)
        {
            //LCD_write("B");
            indicador = 2;
            while (leer==0b10000010) {leer=PINA;}
        }
        
        if (leer == 0b10000001)
        {
            //LCD_write("A");
            indicador = 1;
            while (leer==0b10000001) {leer=PINA;}
        }
        
        
        
        
        //Columna 2
        PORTA = 0b01000000;
        _delay_us(10);
        leer = PINA;
        
        //--------#@$ --Fila1--
        if (leer == 0b01001000)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("#");
                    while (leer==0b01001000) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("@");
                    while (leer==0b01001000) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("$");
                    while (leer==0b01001000) {leer=PINA;}
                    break;
                }
                
                case 4:
                {
                    LCD_write(" ");
                    while (leer==0b01001000) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------ZQI9--Fila2--
        if (leer == 0b01000100)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("9");
                    while (leer==0b01000100) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("I");
                    while (leer==0b01000100) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("Q");
                    while (leer==0b01000100) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("Z");
                    while (leer==0b01000100) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------WÑF6--Fila3--
        if (leer == 0b01000010)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("6");
                    while (leer==0b01000010) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("F");
                    while (leer==0b01000010) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("ENNE");
                    while (leer==0b01000010) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("W");
                    while (leer==0b01000010) {leer=PINA;}
                    break;
                }
            }
        }
        
        //--------TLC3--Fila4--
        if (leer == 0b01000001)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("3");
                    while (leer==0b01000001) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("C");
                    while (leer==0b01000001) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("L");
                    while (leer==0b01000001) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("T");
                    while (leer==0b01000001) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        
        
        //Columna 3
        PORTA = 0b00100000;
        _delay_us(10);
        leer = PINA;
        
        //--------0   --Fila1--
        if (leer == 0b00101000)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("0");
                    while (leer==0b00101000) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write(" ");
                    while (leer==0b00101000) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write(" ");
                    while (leer==0b00101000) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write(" ");
                    while (leer==0b00101000) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------YPH8--Fila2--
        if (leer == 0b00100100)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("8");
                    while (leer==0b00100100) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("H");
                    while (leer==0b00100100) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("P");
                    while (leer==0b00100100) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("Y");
                    while (leer==0b00100100) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------VNE5--Fila3--
        if (leer == 0b00100010)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("5");
                    while (leer==0b00100010) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("E");
                    while (leer==0b00100010) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("N");
                    while (leer==0b00100010) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("V");
                    while (leer==0b00100010) {leer=PINA;}
                    break;
                }
            }
        }
        
        //--------SKB2--Fila4--
        if (leer == 0b00100001)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("2");
                    while (leer==0b00100001) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("B");
                    while (leer==0b00100001) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("K");
                    while (leer==0b00100001) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("S");
                    while (leer==0b00100001) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //Columna 4
        PORTA = 0b00010000;
        _delay_us(10);
        leer = PINA;
        
        //--------CLC---Fila1--
        if (leer == 0b00011000)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("*");
                    while (leer==0b00011000) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_command(0b00000001);
                    while (leer==0b00011000) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_command(0b00000001);
                    while (leer==0b00011000) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_command(0b00000001);
                    while (leer==0b00011000) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------XOG7--Fila2--
        if (leer == 0b00010100)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("7");
                    while (leer==0b00010100) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("G");
                    while (leer==0b00010100) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("O");
                    while (leer==0b00010100) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("X");
                    while (leer==0b00010100) {leer=PINA;}
                    break;
                }
            }
        }
        
        
        //--------UMD4--Fila3--
        if (leer == 0b00010010)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("4");
                    while (leer==0b00010010) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("D");
                    while (leer==0b00010010) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("M");
                    while (leer==0b00010010) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("U");
                    while (leer==0b00010010) {leer=PINA;}
                    break;
                }
            }
        }
        
        //--------RJA1--Fila4--
        if (leer == 0b00010001)
        {
            switch (indicador)
            {
                case 1:
                {
                    LCD_write("1");
                    while (leer==0b00010001) {leer=PINA;}
                    break;
                }
                    
                case 2:
                {
                    LCD_write("A");
                    while (leer==0b00010001) {leer=PINA;}
                    break;
                }
                    
                case 3:
                {
                    LCD_write("J");
                    while (leer==0b00010001) {leer=PINA;}
                    break;
                }
                    
                case 4:
                {
                    LCD_write("R");
                    while (leer==0b00010001) {leer=PINA;}
                    break;
                }
            }
        }
    }
}




