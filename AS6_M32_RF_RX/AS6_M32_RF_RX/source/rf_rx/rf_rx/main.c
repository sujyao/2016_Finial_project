/******************************************************************************

Receive  8 bit data over serial line at 2400 bits per second and latch this
8 bit data to PORTC. The 8 bit data is encapsulated in a simple
packet to discriminate from a junk data. This type of packet is good for sending
over radio frequency using low cost ASK RF module.

Written By
 Avinash Gupta
Contact
 gmail@avinashgupta.com

For more interesting microcontroller tutorials and projects. Please visit
http://www.extremeelectronics.co.in

NOTICE:
PROGRAM SAMPLE PROVIDED FOR SELF LEARNING PURPOSE ONLY!
NO PART OF THIS WORK SHOULD BE USED IN ANY COMMERCIAL PROJECTS OR IN ANY 
TEACHING INSTITUTES FOR TEACHING THEIR STUDENTS
NO PART OF THIS WORK SHOULD BE PUBLISHED IN ANY FORM LIKE PRINTED OR ELECTRONIC
MEDIA

COPYRIGHT (C) 2008-2015 EXTREME ELECTRONICS, INDIA
******************************************************************************/


#include <avr/io.h>
#include "lib/usart/usart_avr.h"

int main()
{

	uint8_t i; //Classical loop variable
	
	uint8_t packet[5],data=0;
	
	DDRC|=0xFF;	//All Output

	//Initialize the USART with Baud rate = 2400bps
	USARTInit(416);

	/*
	Get data from the remote Tx Station
	The data is the value of PORTC on Remote Tx Board
	So we will copy it to the PORTC of this board.
	*/

	while(1)
	{
		//Wait for a packet
		while(!UDataAvailable());
		if(UReadData()!='A') continue;
		while(!UDataAvailable());
		if(UReadData()!='A') continue;
		
		while(UDataAvailable()!=3);

		//Get the packet
		for(i=2;i<5;i++)
		{
			packet[i]=UReadData();
		}

		//Is it ok?
		if(packet[2]!=((uint8_t)~packet[3])) continue;

		if(packet[4]!='Z') continue;

		//The packet is ok
		data=packet[2];

		//Now we have data put it to PORTC
		PORTC=data;
	}
		

}