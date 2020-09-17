#define F_CPU 1000000

#include <stdint.h>
#include <util/delay.h>	 //header containing delay functions
#include "functions.h"

int main(void)
{
	uint8_t i = 1;												//iterator
	Button numberOnKeypad = Button::NO_BUTTON_PRESSED;									//value read from keypad
	uint8_t digitsOnDisplay[4] = {'-', '-', '-', '-'};          //table of values currently shown on 7-segment display
	uint8_t code[4];											//table storing code set by admin
	uint8_t enteredCode[4];										//table storing code entered by user

	init_ports();

	//UserSetsCode();

	while (1)
	{
		numberOnKeypad = GetPressedKey();							//poll for value on keypad

		if(numberOnKeypad != Button::NO_BUTTON_PRESSED)				//if input changed
		{
			if(numberOnKeypad == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				setValueOnWholeDisplay('-', digitsOnDisplay);
				i = 1;
				continue;
			}
			
			if(i == 5 && numberOnKeypad == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				code[0] = digitsOnDisplay[0];
				code[1] = digitsOnDisplay[1];
				code[2] = digitsOnDisplay[2];
				code[3] = digitsOnDisplay[3];
				break;
			}
			
			digitsOnDisplay[i-1] = static_cast<uint8_t>(numberOnKeypad);
			i++;
		}

		if(i < 6)
		{
			setDigit(digitsOnDisplay[0], 1);
			setDigit(digitsOnDisplay[1], 2);
			setDigit(digitsOnDisplay[2], 3);
			setDigit(digitsOnDisplay[3], 4);
		}
		else
		{
			setValueOnWholeDisplay('-', digitsOnDisplay);
			i = 1;
		}
	}
	
	setValueOnWholeDisplay(13, digitsOnDisplay);										//set display to '-.' in locked state

	i=1;															//reset iterator
	
	long int del=0;

	//COMPARING ENTERED CODE WITH CODE SET BEFORE
	while (1)
	{
		numberOnKeypad = GetPressedKey();							//poll for value on keypad

		if(numberOnKeypad != Button::NO_BUTTON_PRESSED)									//if input changed
		{
			if(numberOnKeypad == Button::BUTTON_CANCEL)								//if cancel button was pressed
			{
				setValueOnWholeDisplay(13, digitsOnDisplay);
				i=1;
				continue;
			}
			
			if(i==5 && numberOnKeypad == Button::BUTTON_OK)						//if 4 digits were entered and OK button was pressed
			{
				enteredCode[0] = digitsOnDisplay[0];
				enteredCode[1] = digitsOnDisplay[1];
				enteredCode[2] = digitsOnDisplay[2];
				enteredCode[3] = digitsOnDisplay[3];
				
				if(enteredCode[0]==code[0] && enteredCode[1]==code[1] && enteredCode[2]==code[2] && enteredCode[3]==code[3]) //check if code is correct
				{
					digitsOnDisplay[0] = 0; //O
					digitsOnDisplay[1] = 14;//P
					digitsOnDisplay[2] = 15;//E
					digitsOnDisplay[3] = 16;//N
					break;
				}
				
				else
				{
					digitsOnDisplay[0] = 8;   //B
					digitsOnDisplay[1] = 17;  //A
					digitsOnDisplay[2] = 0;   //D
					digitsOnDisplay[3] = 18;  //nothing
					
					while(1)
					{
						setDigit(digitsOnDisplay[0], 1);
						setDigit(digitsOnDisplay[1], 2);
						setDigit(digitsOnDisplay[2], 3);
						setDigit(digitsOnDisplay[3], 4);
						
						_delay_ms(5);
						del++;

						if(del >= 200) //if about 1 second passed
						{
							del = 0;	 //reset delay cycles counter
							setValueOnWholeDisplay(13, digitsOnDisplay);
							i = 1;	 //reset iterator
							break;
						}
					}
					continue;
				}
			}
			digitsOnDisplay[i-1] = static_cast<uint8_t>(numberOnKeypad);
			i++;
		}

		if(i<6)
		{
			setDigit(digitsOnDisplay[0],1);
			setDigit(digitsOnDisplay[1],2);
			setDigit(digitsOnDisplay[2],3);
			setDigit(digitsOnDisplay[3],4);
		}

		else
		{
			setValueOnWholeDisplay('-', digitsOnDisplay);
			i = 1;
		}
	}
	
	while(1)
	{
		setDigit(digitsOnDisplay[0], 1);
		setDigit(digitsOnDisplay[1], 2);
		setDigit(digitsOnDisplay[2], 3);
		setDigit(digitsOnDisplay[3], 4);
	}
}