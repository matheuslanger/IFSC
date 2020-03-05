#define F_CPU 16000000UL
#include <avr/pgmspace.h>
#include <util/delay.h>
#define DISPLAY PORTD 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))


const unsigned char Tabela[4][4] PROGMEM = {{0x78,0x19,0x79,0x08},
											{0x00,0x12, 0x24,0x40},
											{0x18,0x02,0x30,0x00},
											{0x00,0x00,0x00,0x00}};
int main()
{
	unsigned char valor = 0; 
	DDRB = 0b00001111;
	PORTB= 0xFF;
	DDRD = 0xFF;
	PORTD= 0xFF;
	while(1)
	{
		if(valor>2)
			valor=0;
		else
			valor++;
			
		if(valor>0)
			set_bit(PORTB, valor-1);
		else
			set_bit(PORTB, PB3);
			
			clr_bit(PORTB, valor);
			
		if(!tst_bit(PINB,PB4))
			DISPLAY = pgm_read_byte(&Tabela[0][valor]);
		else if(!tst_bit(PINB,PB5))
			DISPLAY = pgm_read_byte(&Tabela[1][valor]);
		else if(!tst_bit(PINB,PB6))
			DISPLAY = pgm_read_byte(&Tabela[2][valor]);
		else if(!tst_bit(PINB,PB7))
			DISPLAY = pgm_read_byte(&Tabela[3][valor]);
		
		_delay_ms(1); 
			
	}}