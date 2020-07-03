#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libLCD.h"

#define MotorDerechaPH1    7
#define MotorDerechaPH2    6
#define MotorIzquierdaPH1  5
#define MotorIzquierdaPH2  4
//#define Motor_Derecha PORTC7
//#define Motor_Izquierda PORTC6

/*
 ________  ___  ___  _____ ______   ________          ________  ________   ________  ________
|\   ____\|\  \|\  \|\   _ \  _   \|\   __  \        |\   ____\|\   ___  \|\   ___ \|\   __  \
\ \  \___|\ \  \\\  \ \  \\\__\ \  \ \  \|\  \       \ \  \___|\ \  \\ \  \ \  \_|\ \ \  \|\  \
 \ \_____  \ \  \\\  \ \  \\|__| \  \ \  \\\  \       \ \  \    \ \  \\ \  \ \  \ \\ \ \   _  _\
  \|____|\  \ \  \\\  \ \  \    \ \  \ \  \\\  \       \ \  \____\ \  \\ \  \ \  \_\\ \ \  \\  \
    ____\_\  \ \_______\ \__\    \ \__\ \_______\       \ \_______\ \__\\ \__\ \_______\ \__\\ _\
    \_________\|_______|\|__|     \|__|\|_______|        \|_______|\|__| \|__|\|_______|\|__|\|__|
 
 
 PUENTEH1 ---> Motor Hacia Adelante ---> PORTC7, PORTC5
 PUENTEH2 ---> Motor Hacia Atras    ---> PORTC6, PORTC4
 
 Sensores CNY70 --> PINA ---> ADCH ---> ADMUX ---> pin: 4,5,6,7
 
 Sensores Sharp ---> PINA ---> ADCH ---> ADMUX ---> pin: 0,1,2,3
 
 IF LCD, PORTC: 0,1,2 --> RS,RW,EN
         DDRD: Data
 
*/

void initIO(void) {
	
}

int sensor1, sensor2, sensor3, sensor4, sensorcn1, sensorcn2, sensorcn3, sensorcn4;

int main(void) {
	initIO();
    
    //_delay_ms(5000);       //Retardo de Inicializacion, REGLA
    
    LCD_init();
    LCD_wait();
    LCD_write("Sumo CNDR");
    
    //Pin Switch
    DDRB |= 1<<5;
    
    //Pines Sensores CNY70
    DDRB |= 1<<0;
    DDRB |= 1<<1;
    DDRB |= 1<<2;
    DDRB |= 1<<3;
    
    //Pines Motores
    DDRC |= 1<<MotorDerechaPH1;
    DDRC |= 1<<MotorDerechaPH2;
    DDRC |= 1<<MotorIzquierdaPH1;
    DDRC |= 1<<MotorIzquierdaPH2;
    
    //Configure the ADC
    ADCSRA |= 1 <<ADPS2;
    ADMUX |= 1 <<ADLAR;
    ADMUX |= 1 <<REFS0;
    ADCSRA |= 1 <<ADIE;
    ADCSRA |= 1 <<ADEN;
    
    sei();
    
    

	while (1)
    {
        sensorcn1 = PINB0;
        sensorcn2 = PINB1;
        sensorcn3 = PINB2;
        sensorcn4 = PINB3;
        
        int switchon = PINB5;
        
        /*
                                Logica de Movimiento
         
            MotorDerecha | MotorIzquierda = HIGH --> Mover Hacia Adelante
            MotorDerecha | MotorIzquierda = LOW  --> STOP
            MotorDerecha = HIGH, MotorIzquierda = LOW  --> Mover Hacia Izquierda
            MotorDerecha = LOW,  MotorIzquierda = HIGH --> Mover Hacia Derecha
         
            El sumo solo se movera para atacar, cuando este detectando unicamente por
            delante. En mediciones hibridas, retrocedera. En mediciones nulas, se quedara
            estatico
        */
        
        //Variables de Movimiento
        int Mover_Derecho = 0;
        int Mover_Izq = 0;
        int Mover_Der = 0;
        int Parar = 0;
        int Reversa = 0;
        
        
        while (switchon == 1)
        {
            
        //Solamente se movera, cuando el sensor este detectando negro
        while ((sensorcn1 != 0) | (sensorcn2 != 0) | (sensorcn3 !=0) | (sensorcn4 != 0))
        {
            //Sensores cny70 detectando
            while (sensorcn1 == 1 )
            {
                Reversa = 1;
                Mover_Der = 1;
                
            }
            
            while (sensorcn2 == 1)
            {
                Reversa = 1;
                Mover_Izq = 1;
            }
            
            while (sensorcn3 == 1)
            {
                Mover_Derecho = 1;
                Mover_Der = 1;
            }
            
            while (sensorcn4 == 1)
            {
                Mover_Derecho = 1;
                Mover_Izq = 1;
            }
            
            //Seguros de Parada por banda blanca
            while ((sensorcn1 == 1)&&(sensorcn2 == 1))
            {
                Parar = 1;
            }
        
            while ((sensorcn1 == 1)&&(sensorcn3 == 1))
            {
                Parar = 1;
            }
            
            while ((sensorcn2 == 1)&&(sensorcn4 == 1))
            {
                Parar = 1;
            }
            
            while ((sensorcn4 == 1)&&(sensorcn3 == 1))
            {
                Parar = 1;
            }
            
            if (Parar == 1)
            {
                PORTC |= 0<<MotorIzquierdaPH1;
                PORTC |= 0<<MotorIzquierdaPH2;
                PORTC |= 0<<MotorDerechaPH1;
                PORTC |= 0<<MotorDerechaPH2;
            }
                else
                {
                    Parar = 0;
                }
            
            //Sentencias de Movimiento, Condicionadas al valor de sensor CNY70
            if (sensor1=="Cierta Distancia")
            {
                Mover_Derecho=1;
            }
                   else
                   {
                       Mover_Derecho = 0;
                   }
            
            if (sensor1="Cierta Distancia no permitida")
            {
                Parar = 1;
            }
                   else
                   {
                       Parar = 0;
                   }
            
            if (sensor1="Cierta Distancia Variable" | sensor2)
            {
                Mover_Derecho = 12;
            }
            
            
            
            //While, para Movimietnos relativo a sensores IR
            //PH1, Motor hacia adelante, PH2, motor hacia atras
            while (Mover_Derecho == 1)
            {
                PORTC |= 1<<MotorIzquierdaPH1;
                PORTC |= 0<<MotorIzquierdaPH2;
                PORTC |= 1<<MotorDerechaPH1;
                PORTC |= 0<<MotorDerechaPH2;
            }
            
            while (Parar == 1)
            {
                PORTC |= 0<<MotorIzquierdaPH1;
                PORTC |= 0<<MotorIzquierdaPH2;
                PORTC |= 0<<MotorDerechaPH1;
                PORTC |= 0<<MotorDerechaPH2;
            }
            
            //CNY70 #1 Activado
             
             while ((Reversa == 1) | (Mover_Der == 1))
             {
                for (int girodiagderr=1; girodiagderr<=10; girodiagderr++)
                {
                //Reversa
                PORTC |= 1<<MotorIzquierdaPH2;
                PORTC |= 1<<MotorDerechaPH2;
                PORTC |= 0<<MotorIzquierdaPH1;
                PORTC |= 0<<MotorDerechaPH1;
                _delay_us(1000);
                //Giro Diagonal
                PORTC |= 0<<MotorDerechaPH1;
                PORTC |= 0<<MotorDerechaPH2;
                PORTC |= 1<<MotorIzquierdaPH2;
                PORTC |= 0<<MotorIzquierdaPH1;
                Reversa = 0;
                Mover_Der = 0;
             
                }
             }
            
            //CNY70 #2 Activado
            while ((Reversa == 1) | (Mover_Izq == 1))
            {
                for (int girodiagizqr=1; girodiagizqr<=10; girodiagizqr++)
                {
                    //Reversa
                    PORTC |= 1<<MotorIzquierdaPH2;
                    PORTC |= 1<<MotorDerechaPH2;
                    PORTC |= 0<<MotorIzquierdaPH1;
                    PORTC |= 0<<MotorDerechaPH1;
                    _delay_us(1000);
                    //Giro Diagonal
                    PORTC |= 0<<MotorDerechaPH1;
                    PORTC |= 1<<MotorDerechaPH2;
                    PORTC |= 0<<MotorIzquierdaPH2;
                    PORTC |= 0<<MotorIzquierdaPH1;
                    Reversa = 0;
                    Mover_Izq = 0;
                    
                }
            }
            
            //CNY70 #3 Activado
            while ((Mover_Derecho == 1) | (Mover_Der == 1))
            {
                for (int girodiagderd=1; girodiagderd<=10; girodiagderd++)
                {
                    //Adelante
                    PORTC |= 0<<MotorIzquierdaPH2;
                    PORTC |= 0<<MotorDerechaPH2;
                    PORTC |= 1<<MotorIzquierdaPH1;
                    PORTC |= 1<<MotorDerechaPH1;
                    _delay_us(1000);
                    //Giro Diagonal
                    PORTC |= 0<<MotorDerechaPH1;
                    PORTC |= 0<<MotorDerechaPH2;
                    PORTC |= 0<<MotorIzquierdaPH2;
                    PORTC |= 1<<MotorIzquierdaPH1;
                    Mover_Derecho = 0;
                    Mover_Der = 0;
                    
                }
            }
            
            //CNY70 #4 Activado
            while ((Mover_Derecho == 1) | (Mover_Izq == 1))
            {
                for (int girodiagizqd=1; girodiagizqd<=10; girodiagizqd++)
                {
                    //Adelante
                    PORTC |= 0<<MotorIzquierdaPH2;
                    PORTC |= 0<<MotorDerechaPH2;
                    PORTC |= 1<<MotorIzquierdaPH1;
                    PORTC |= 1<<MotorDerechaPH1;
                    _delay_us(1000);
                    //Giro Diagonal
                    PORTC |= 1<<MotorDerechaPH1;
                    PORTC |= 0<<MotorDerechaPH2;
                    PORTC |= 0<<MotorIzquierdaPH2;
                    PORTC |= 0<<MotorIzquierdaPH1;
                    Mover_Derecho = 0;
                    Mover_Izq = 0;
                    
                }
            }
            
            
            
            /*
            //Switch-Case, para Movimientos relativo a sensores IR
            switch (Mover_Derecho)
            {
                case 1:
                {
                    PORTC |= 1<<MotorIzquierda;
                    PORTC |= 1<<MotorDerecha;
                    //Motor_Izquierda = 0xFF;
                    //Motor_Derecha = 0xFF;
                }
                
                case 12:
                {
                    PORTC |= 0<<MotorIzquierda;
                    PORTC |= 0<<MotorDerecha;
                    //Motor_Izquierda = 0x00;
                    //Motor_Derecha = 0xFF;
                }
                    
            }
            */
        }
        
        }
        
	}
}


//Lectura ADC
ISR(ADC_vect)
{
    
    //Dependiendo del pin, guardar ADCH en variable
    switch (ADMUX)
    {
        //Sensores IR
        case 0b00000000:
        {
            int sensor1 = 0;
            ADCSRA |= 1 <<ADSC;
            sensor1 = ADCH;
            char sensor1char[4];
            itoa(ADCH, sensor1char, 10);
            LCD_goTo(1, 1);
            LCD_write("S1 ");
            LCD_goTo(1, 1);
            LCD_write(sensor1char);
            LCD_goTo(1, 1);
            LCD_write("   ");
            ADMUX = 0b00000001;
            break;
        }
        
        /*
        case 0b00000001:
        {
            int sensor2 = 0;
            ADCSRA |= 1 <<ADSC;
            sensor2 = ADCH;
            char sensor2char[4];
            itoa(ADCH, sensor2char, 10);
            LCD_goTo(1, 2);
            LCD_write("S2 ");
            LCD_goTo(1, 2);
            LCD_write(sensor2char);
            LCD_goTo(1, 2);
            LCD_write("   ");
            ADMUX = 0b00000010;
            break;
        }
        
        case 0b00000010:
        {
            int sensor3 = 0;
            ADCSRA |= 1 <<ADSC;
            sensor3 = ADCH;
            char sensor3char[4];
            itoa(ADCH, sensor3char, 10);
            LCD_goTo(8, 1);
            LCD_write("S3 ");
            LCD_goTo(8, 1);
            LCD_write(sensor3char);
            LCD_goTo(8, 1);
            LCD_write("   ");
            ADMUX = 0b00000011;
            break;
        }
            
        case 0b00000011:
        {
            int sensor4 = 0;
            ADCSRA |= 1 <<ADSC;
            sensor4 = ADCH;
            char sensor4char[4];
            itoa(ADCH, sensor4char, 10);
            LCD_goTo(8, 2);
            LCD_write("S4 ");
            LCD_goTo(8, 2);
            LCD_write(sensor4char);
            LCD_goTo(8, 2);
            LCD_write("   ");
            ADMUX = 0b00000000;
            break;
        }
        */
          
        
        //Sensores CNY70
        case 0b00000100:
        {
            ADCSRA |= 1 <<ADSC;
            if (ADCH == 255){sensorcn1=1;}
            else {sensorcn1=0;}
            ADMUX = 0b00000101;
            break;
        }
            
        case 0b00000101:
        {
            ADCSRA |= 1 <<ADSC;
            if (ADCH == 255){sensorcn2=1;}
            else {sensorcn2=0;}
            ADMUX = 0b00000110;
            break;
        }
            
        case 0b00000110:
        {
            ADCSRA |= 1 <<ADSC;
            if (ADCH == 255){sensorcn3=1;}
            else {sensorcn3=0;}
            ADMUX = 0b00000111;
            break;
        }
            
        case 0b00000111:
        {
            ADCSRA |= 1 <<ADSC;
            if (ADCH == 255){sensorcn4=1;}
            else {sensorcn4=0;}
            ADMUX = 0b00000000;
            break;
        }
        
            
            
        default:
        {
            ADCSRA |= 1 <<ADSC;
        }
           
    }
}
