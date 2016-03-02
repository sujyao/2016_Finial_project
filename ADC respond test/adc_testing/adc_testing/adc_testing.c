/*
 * adc_testing.c
 *
 * Created: 2/03/2016 10:28:42 PM
 *  Author: LJ
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>


//Define 2 input channels
#define Voltage_signal 0b00000000 //AVCC with external capacitor at AREF pin,ADC0
#define Current_signal 0b00000001 //AVCC with external capacitor at AREF pin,ADC1


void setup(void);
char readADC(char channel);

int main(void)
{
	char voltage,currents;
	
	setup();
    while(1)
    {
		//read currents first
		currents = readADC(Current_signal);
		if (currents>=853) //bigger than 2.5V
		{
			PORTD = 0b00000000; // turn off gate;
			voltage = readADC(Voltage_signal);
			if (voltage <=10)
			{
				PORTD = 0b00000001;//turn on the gate gain.
			}
			
			
			 
		}
		else
		{
			PORTD = 0b00000001;//turn on gate;
		}
		
    }
}

//ADC function
char readADC(char ch)
{
	 //Select ADC Channel ch must be 0-7
	 ch=ch&0b00000111;
	 ADMUX|=ch;

	 //Start Single conversion
	 ADCSRA|=(1<<ADSC);

	 //Wait for conversion to complete
	 while(!(ADCSRA & (1<<ADIF)));

	 //Clear ADIF by writing one to it
	 ADCSRA|=(1<<ADIF);

	 return(ADC);
}

void setup(void)
{
	DDRD = 0xFF; //PORTD output gate signal
	PORTD = 0xFF; //Initial Port D(11111111)
	
	//InitADC
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
	
}
