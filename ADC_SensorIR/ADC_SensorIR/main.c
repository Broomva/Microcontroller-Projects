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

 
                                          ADC Sensor IR
                                        Calibracion Manual
                                Datos Calibracion y Curva .xls en la
                                     carpeta de este archivo
 
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


//int e = 2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901157383418793070215408914993488416750924476146066808226480016847741185374234544243710753907774499206955170276183860626133138458300075204493382656029760673711320070932870912744374704723069697720931014169283681902551510865746377211125238978442505695369677078544996996794686445490598793163688923009879312773617821542499922957635148220826989519366803318252886939849646510582093923982948879332036250944311730123819706841614039701983767932068328237646480429531180232878250981945581530175671736133206981125099618188159304169035159888851934580727386673858942287922849989208680582574927961048419844436346324496848756023362482704197862320900216099023530436994184914631409343173814364054625315209618369088870701676839642437814059271456354906130310720851038375051011574770417189861068739696552126715468895703503540212340784981933432106817012100562788023519303322474501585390473041995777709350366041699732972508868769664035557071622684471625607988265178713419512466520103059212366771943252786753985589448969709640975459185695638023637016211204774272283648961342251644507818244235294863637214174023889344124796357437026375529444833799801612549227850925778256209262264832627793338656648162772516401910590049164499828931505660472580277863186415519565324425869829469593080191529872117255634754639644791014590409058629849679128740687050489585867174798546677575732056812884592054133405392200011378630094556068816674001698420558040336379537645203040243225661352783695117788386387443966253224985065499588623428189970773327617178392803494650143455889707194258639877275471096295374152111513683506275260232648472870392076431005958411661205452970302364725492966693811513732275364509888903136020572481765851180630364428123149655070475102544650117272115551948668508003685322818;


ISR(ADC_vect)
{
    _delay_ms(100);
    //int sensor1 = (128000-sqrt(10)*sqrt(1560980213-3570200*sensor))/178510;//(sensor-3)/128; //e^(-(2*(50*sensor-12833))/6623);//(4641+250*sensor)/286100;//(sensor-18.564)/1144.4; //(sensor-0.0283)/2;//(10000*sensor-1649)/220170;
    char adcResult[4];
    itoa(ADCH, adcResult, 10);
    
    /*
    
    switch (ADCH)
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



