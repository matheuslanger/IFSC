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
#define BOTAO PB0
#define DISPLAY PORTD

const unsigned char Tabela[] = 

int main(void)
{
	unsigned char valor = 0;
	DDRB 0b11111110;
	DDRD = 0xFF;
    PORTB = 0x01;
	PORTD = 0xFF;
	while(1)
    {
		if(!tst_bit(PINB, BOTAO))
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