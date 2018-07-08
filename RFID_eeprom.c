//read phone no AT ANY LOCTION IN EEPROM//
#include<pic.h> //INCLUDE Header FILE of pic//
#include <string.h>
unsigned char arr5[9]="this code";
unsigned char arr6[13]="this code not";
unsigned char arr7[7]="matched";
#define LCD PORTD//define portD as lcd//
#define RS RC0  //define rC2 as rs (register select)//
#define EN RC1  //define rC3 as en(enable)//
void CMD();//declare the cmd function//
void DAT();//declare the dat function//
void LATCH();//declare the latch function//

unsigned char write (unsigned char,unsigned char );
unsigned char read (unsigned char);
unsigned char addr1=0x00,addr2=0x10,addr3=0x20,addr4=0x30,addr5=0x40;
unsigned char data[11];
unsigned char mobile1[11]="9811869035";
unsigned char mobile2[11]="9211465678";
unsigned char mobile3[11]="9871456554";
unsigned char mobile4[11]="9211034567";
unsigned char mobile5[11]="9911223344";
           
unsigned char mobile6[11],mobile7[11],mobile8[11],mobile9[11],mobile10[11];
unsigned char a,b,c,d,e,i,A,dat1,dat2,dat3,dat4,dat5;
void delay (unsigned int);//declare delay function//

 
void main()  //START MAIN FUNCTION//
{
TRISC=0X80;//trisc is used for portc work as  0x00 means output port//
TRISD=0X00;//trisd is used for portd work as  0x00 means output port//

LCD=0X38;//to initialize the lcd driver (0 for 4 bit,1 for 8 bit),(0 for singal,1 for multi line),(0 f0r 5*7,1 for 5*10(col or row)))//
CMD();   //call cmd function//
LCD=0X0E;//to on lcd with cursor//
CMD();   //call cmd function//
LCD=0X01;//to clear lcd//
CMD();    //call cmd function//
TXSTA=0X24; //IN TXSTA REG. ONLY TXEN (TX ENABLE BIT)&& TRMT(TRANSMITER SHIFT REG. BIT )IS HIGH)
RCSTA=0X90;//IN RCSTA REG. ONLY SPEN(SERIAL PORT ENABLE BIT)& CREN(CONTINIOUS RECIEVE ENABLE BIT)IS HIGH)
SPBRG=25;//BAUD RATE GENERATER//B.R=FOSC/16(N+1)//
RCIF=0;//RECIEVE INTERUPPT FLAG//
A=0X80;  //ASIGN VALUE OF 0X80 IN A//

for(i=0;i<10;i++)
{
dat1=mobile1[i];
write(addr1,dat1);
addr1++;
}

for(i=0;i<10;i++)
{
dat2=mobile2[i];
write(addr2,dat2);
addr2++;
}

for(i=0;i<10;i++)
{
dat3=mobile3[i];
write(addr3,dat3);
addr3++;
}

for(i=0;i<10;i++)
{
dat4=mobile4[i];
write(addr4,dat4);
addr4++;
}

for(i=0;i<10;i++)
{
dat5=mobile5[i];
write(addr5,dat5);
addr5++;
}
while(1)
{
for(i=0;i<10;i++)
{
while(RCIF==0);//untill RCIF GO TO HIGH//
data[i]=RCREG; //ASSIGN VALUE OF RCREG REG. VALUE IN data//
RCIF=0;
}
LCD=0X01;
CMD();     
for(i=0;i<10;i++)
{
mobile6[i]=read(addr1+i); //ASSIGN VALUE OF RCREG REG. VALUE IN data//
} 
for(i=0;i<10;i++)
{
mobile7[i]=read(addr2+i); //ASSIGN VALUE OF RCREG REG. VALUE IN data//
} 
for(i=0;i<10;i++)
{
mobile8[i]=read(addr3+i); //ASSIGN VALUE OF RCREG REG. VALUE IN data//
}
for(i=0;i<10;i++)
{
mobile9[i]=read(addr4+i); //ASSIGN VALUE OF RCREG REG. VALUE IN data//
} 
for(i=0;i<10;i++)
{
mobile10[i]=read(addr5+i); //ASSIGN VALUE OF RCREG REG. VALUE IN data//
}
//mobile1[10]='\0';
//mobile2[10]='\0';
//mobile3[10]='\0';
//mobile4[10]='\0';
//mobile5[10]='\0';
//data[10]='\0';
a=strcmp(data,mobile6);
b=strcmp(data,mobile7);
c=strcmp(data,mobile8);
d=strcmp(data,mobile9);
e=strcmp(data,mobile10);  
if(a==0||b==0||c==0||d==0||e==0)

{
for(i=0;i<9;i++)
{
LCD=arr5[i];// OR ASCII VALUE OF //
DAT();  //call lcd function//
}
LCD=0Xc0;  //0xc0 is the 1st location of the lcd in next line//
CMD();   //call cmd function//
for(i=0;i<7;i++)
{
LCD=arr7[i];// OR ASCII VALUE OF //
DAT();  //call lcd function//
}
}


else
{ 
for(i=0;i<13;i++)
{
LCD=arr6[i];// OR ASCII VALUE OF //
DAT();  //call lcd function//
}
LCD=0Xc0;  //0xc0 is the 1st location of the lcd in next line//
CMD();   //call cmd function//
for(i=0;i<7;i++)
{
LCD=arr7[i];// OR ASCII VALUE OF //
DAT();  //call lcd function//
}
}
//while(1);
}
}

unsigned char write (unsigned char a ,unsigned char d )
{
 again:
 EEPGD=0;
 EEADR=a;
 EEDAT=d;
 WRERR=0;
 WREN=1;
 EECON2=0X55;
 EECON2=0XAA;
 WR=1;
 while(WR==1);
 WREN=0;
 if(WRERR==1)
 goto again;
}

unsigned char read(unsigned char a)//DEFINE READ FUNCTION//
{
unsigned char d;//DECLARE CHAR D//
EEPGD=0;   //IN EECON1 SFR EEPGD 0 IS USED FOR EEPROM AND 1 FOR FLASH MEMORY//
EEADR=a;   //EEADR SFR USED FOR STORE ADDRESS OF DATA//
WREN=0;    //IN EECON1 SFR WREN IS USED FOR WRITE ENABLE //
RD=1;      //IN EECON1 SFR RD IS ASSIGN 1 AND WAIT FOR 0//
while(RD==1);//WHEN RD GOES TO 0 THAN CONTROL TRANFER TO NEXT INSTRUCTION//
d=EEDAT;   //IN EECON1 SFR EEDAT VALUE IS ASSIGN IN D//
return (d); //RETURN VALUE D//
}	

void LATCH() //define the latch//
{
EN=1;      //to generate a clock pulse to store a value  for high 1 is used for EN//
delay(50);  //delay //
EN=0;      //to generate a clock pulse to store a value  for low 0 is used for EN//
delay(100); //delay//
}

void CMD()//define cmd//
{
RS=0; //register select 0 for instruction register//
LATCH();//call latch function//
}

void DAT()//define dat function//
{
RS=1;    //register select 0 for data register//
LATCH();//call latch function//
}

void delay(unsigned int x) //DEFINE DELAY FUNCTION//
{
while(x>0)  //UNTILL X IS GREATER THAN 0//
{
x--;      //DECREMENT IN X//
}
}

	