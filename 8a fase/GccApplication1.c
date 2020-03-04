/*
 * GccApplication1.c
 *
 * Created: 04/03/2020 13:54:35
 *  Author: Aluno
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))


int main(void)
{
	DDRB 0b11111110;
	DDRB &= ~(1<<PB4);
    PORTB |= (1<<PB4);
	while(1)
    {
		if(!tst_bit(PINB, PB4))
		{
			PORTB |= (1<<PB5);	
			_delay_ms(250);
		}
		else if (tst_bit(PINB, PB5))
		{
			_delay_ms(250);
			PORTB &= ~(1<<PB5);
		}
		
    }
}