#include <pic.h>
#define LCD PORTB
#define RS RD7
#define EN RD6

__CONFIG(0x20F2);

void delay(unsigned int);
void latch(void);
void cmd(void);
void dat(void);
void stdnt1(void);
void stdnt2(void);
void book1(void);
void book2(void);
void write(unsigned char,unsigned char);
unsigned char read(unsigned char);
void rx(char);
void tx(unsigned int,char);

int i,flag1=0,flag2=0,flag3=0,flag4=0,std1_iss=0,std2_iss=0;
unsigned int flag,j;
unsigned char ch,p[11],rc[12],chk1[11],chk2[11],chk3[11],chk4[11];

unsigned char a[23]="WELCOME TO THE LIBRARY";
unsigned char scan[25]="PLEASE SCAN YOUR ID CARD";
unsigned char accept[9]="VALID ID";
unsigned char err[11]="INVALID ID";
unsigned char issue[12]="BOOK ISSUED";
unsigned char rturn[14]="BOOK RETURNED";
unsigned char stdn1[14]="MANAN GULYANI";
unsigned char stdn2[11]="SAGAR RANA";
//unsigned char bk1[20]="APPLIED MATHEMATICS";
//unsigned char bk2[19]="ANALOG ELECTRONICS";
unsigned char sid1[11]="10004AFA2C";
unsigned char sid2[11]="3F001C1CAB";
unsigned char bid1[11]="3F001C1A7B";
unsigned char bid2[11]="3F001C1B3A";
unsigned char sadr1=0x10;
unsigned char sadr2=0x30;
unsigned char sadr3=0x50;
unsigned char sadr4=0x70;

void delay(unsigned int x)
{
	while(x>0)
	x--;
}

void latch(void)
{
	EN=1;
	delay(200);
	EN=0;
	delay(200);
}

void cmd(void)
{
	RS=0;
	latch();
}

void dat(void)
{
	RS=1;
	latch();
}

void stdnt1(void)
{
	for(i=0;i<10;i++)
	{
		write(sadr1,sid1[i]);
		sadr1++;
	}
}

void stdnt2(void)
{
	for(i=0;i<10;i++)
	{
		write(sadr2,sid2[i]);
		sadr2++;
	}
}

void book1(void)
{
	for(i=0;i<10;i++)
	{
		write(sadr3,bid1[i]);
		sadr3++;
	}
}

void book2(void)
{
	for(i=0;i<10;i++)
	{
		write(sadr4,bid2[i]);
		sadr4++;
	}
}

unsigned char read(unsigned char p)
{
	unsigned char d;
	EEPGD=0;
	EEADR=p;
	WREN=0;
	RD=1;
	while(RD==1);
	d=EEDAT;
	return d;
}

void write(unsigned char q,unsigned char s)
{
	again:
	EEPGD=0;
	EEADR=q;
	EEDAT=s;
	WRERR=0;
	WREN=1;
	EECON2=0X55;
	EECON2=0XAA;
	WR=1;
	while(WR==1);
	WREN=0;
	if(WRERR==1)
	{
		goto again;
	}
}


void main(void)
{
	TRISD=0X00;
	TRISB=0X00;
	TRISC=0X80;
	PORTD=0X00;
	LCD=0X00;
	PORTC=0X00;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=25; 
	
	LCD=0X38;
	cmd();
	LCD=0X0C;
	cmd();
	LCD=0X01;
	cmd();
	LCD=0X80;
	cmd();
	
	while(1)
	{
	
		for(i=0;i<11;i++)
		{
			LCD=a[i];
			dat();
		}
		
		LCD=0XC4;
		cmd();
		
		for(i=10;i<22;i++)
		{
			LCD=a[i];
			dat();
		}
		delay(50000);

		stdnt1();
		stdnt2();
		book1();
		book2();

			unsigned char sadr1=0x10;
			unsigned char sadr2=0x30;
			unsigned char sadr3=0x50;
			unsigned char sadr4=0x70;
		for(i=0;i<10;i++)
		{
			chk1[i]=read(sadr1);
			sadr1++;
			chk2[i]=read(sadr2);
			sadr2++;
			chk3[i]=read(sadr3);
			sadr3++;
			chk4[i]=read(sadr4);
			sadr4++;
		}
start:		
		LCD=0X01;
		cmd();
		LCD=0X80;
		cmd();
		for(i=0;i<16;i++)
		{
			LCD=scan[i];
			dat();
		}

		LCD=0XC3;
		cmd();
		for(i=16;i<24;i++)
		{
			LCD=scan[i];
			dat();
		}
		delay(50000);
		
		

		for(i=0;i<12;i++)
		{
			while(RCIF==0);
			rc[i]=RCREG;
		}
		
		delay(60000);
		delay(60000);
		
	//	rx(rc[11]);


		for(int k=0;k<10;k++)
		{
			if(rc[k]!=chk1[k])
			{
				flag1=1;
			}
			if(rc[k]!=chk2[k])
			{
				flag2=1;
			}
		}
		if(flag1==0)
		{
			flag2=0;
			flag1=0;
			LCD=0X01;
			cmd();
			for(i=0;i<13;i++)
			{
				LCD=stdn1[i];
				dat();
			}
			if(std1_iss==1)
			{
				std1_iss==0;
					LCD=0X01;
					cmd();
				for(i=0;i<13;i++)
				{
					LCD=rturn[i];
					dat();
					RD0=0;
				}		
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);
				goto start;
			}
			for(int j=0;j<12;j++)
			{
				while(RCIF==0);
				rc[j]=RCREG;
			}
		
			for(int k=0;k<10;k++)
			{
				if(rc[k]!=chk3[k])
				{
					flag3=1;
				}
				if(rc[k]!=chk4[k])
				{
					flag4=1;
				}
			}	
			if(flag3==0)
			{
					flag4=0;
					LCD=0X01;
					cmd();
				for(i=0;i<11;i++)
				{
					LCD=issue[i];
					dat();
				}
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);	
				std1_iss=1;
			}
			else if(flag4==0)
			{
					flag3=0;
					LCD=0X01;
					cmd();
				for(i=0;i<11;i++)
				{

					LCD=issue[i];
					dat();
				}
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);	
				std1_iss=1;
			}
			goto start;
		}

		else if(flag2==0)
		{
			flag1=0;
			flag2=0;
			LCD=0X01;
			cmd();
			for(i=0;i<10;i++)
			{
				LCD=stdn2[i];
				dat();
			}
			if(std2_iss==1)
			{
				std2_iss==0;
					LCD=0X01;
					cmd();
				for(i=0;i<13;i++)
				{
					LCD=rturn[i];
					dat();
				}		
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);
				goto start;
			}
			for(int j=0;j<12;j++)
			{
				while(RCIF==0);
				rc[j]=RCREG;
			}
		
			for(int k=0;k<10;k++)
			{
				if(rc[k]!=chk3[k])
				{
					flag3=1;
				}
				else if(rc[k]!=chk4[k])
				{
					flag4=1;
				}
			}	
			if(flag3==0)
			{
					flag4=0;
					LCD=0X01;
					cmd();
				for(i=0;i<11;i++)
				{
					LCD=issue[i];
					dat();
				}
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);	
				std2_iss=1;
			}
			else if(flag4==0)
			{
					flag3=0;
					LCD=0X01;
					cmd();
				for(i=0;i<11;i++)
				{

					LCD=issue[i];
					dat();
					RD0=0;
				}
					RD0=1;
					delay(20000);
					RD0=0;
				delay(60000);	
				std2_iss=1;
			}
			goto start;
		}

		else
		LCD=0X01;
		cmd();
		LCD=0X80;
		cmd();
		for(i=0;i<11;i++)
		{
			LCD=err[i];
			dat();
		}
					RD0=1;
					delay(60000);
					RD0=0;
		delay(50000);
	}
}