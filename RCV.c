#include<pic.h>
#define LCD PORTB
#define EN RD6
#define RS RD7
void cmd();
void latch();
void data();
void delay(int);
void main()
{	TRISC=0X80;
	PORTC=0X00;
	
		TRISD=0X00;
	PORTD=0X00;
	
	TRISB=0X00;
	LCD=0X00;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=25;
		
	char ch[40];

	LCD=0X38;
	cmd();
	LCD=0X0E;
	cmd();
	LCD=0X01;
	cmd();
	LCD=0X80;
	cmd();
	
	while(1)
	{	
		RCIF=0;
			
		for(unsigned int i=0;i<10;i++)
		{	
			while(RCIF==0);
			ch[i]=RCREG;
			
		}
		for(unsigned int i=0;i<10;i++)
		{
			LCD=ch[i];
			data();
		}
		while(1);
	}
}		
		
void cmd()
{	RS=0;
	latch();
}

void data()
{	RS=1;
	latch();
}

void latch()
{	EN=1;
	delay(2000);
	EN=0;
	delay(2000);
}

void delay(int x)
{	while(x>0)
	x--;
}