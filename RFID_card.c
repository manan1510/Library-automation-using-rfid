
                 //Check for valid number //

#include<pic.h> 
#include <string.h>
#define LCD PORTB
#define RS RD6  
#define EN RD7  

char a[11]="  WELCOME! ";
char b[10]="TOUCH CARD";
char arr5[9]="this code";
char arr6[13]="this code not";
char arr7[7]="matched";


char d[10]="15001C2543";
          
void CMD();
void DAT();
void LATCH();

int i=0,l,p,q,m;
bit z=0;
char ch[10];

void delay (unsigned int);//declare delay function//

 
void main()  //START MAIN FUNCTION//
{
ANSELH=0X00;
TRISC=0X80;//trisc is used for portc work as  0x00 means output port//
TRISB=0X00;//trisb is used for portd work as  0x00 means output port//
TRISD=0X00;
PORTD=0x00;
PORTB=0x00;


TXSTA=0X24; //IN TXSTA REG. ONLY TXEN (TX ENABLE BIT)&& TRMT(TRANSMITER SHIFT REG. BIT )IS HIGH)
RCSTA=0X90;//IN RCSTA REG. ONLY SPEN(SERIAL PORT ENABLE BIT)& CREN(CONTINIOUS RECIEVE ENABLE BIT)IS HIGH)
SPBRG=25;//BAUD RATE GENERATER//B.R=FOSC/16(N+1)//

GIE=1;
PEIE=1;
RCIE=1;
RCIF=0;

LCD=0X38;//to initialize the lcd driver (0 for 4 bit,1 for 8 bit),(0 for singal,1 for multi line),(0 f0r 5*7,1 for 5*10(col or row)))//
CMD();   //call cmd function//
LCD=0X0E;//to on lcd with cursor//
CMD();   //call cmd function//
LCD=0X01;//to clear lcd//
CMD();    //call cmd function//


LCD=0X80;
CMD();
for(p=0;p<11;p++)
{
LCD=a[p];
DAT();
}

LCD=0xC0;
CMD();
for(p=0;p<10;p++)
{
LCD=b[p];
DAT();
}
delay(20000);

while(RCIF==0);

//while(1)
//{
//for(i=0;i<10;i++)
//{
//while(RCIF==0);//untill RCIF GO TO HIGH//
//data[i]=RCREG; //ASSIGN VALUE OF RCREG REG. VALUE IN data//
//RCIF=0;
//}
//
//LCD=0X01;//to clear lcd//
//CMD(); 
//
//
//
//data[11]='\0';
//
//a=strcmp(data,card1);
//
// 
//if(a==0)
//{
// RD2=0;
// RD3=1;
//delay(65000);
//
// RD2=0;
// RD3=0;
//delay(30000);
//
// 
// 



if (z==1)
{
z=0;
q=0;
for(m=0;m<10;m++)
{
if(ch[m]==d[m])
{
q++;
}
}

if(q==10)
{
LCD=0X01;
CMD();

LCD=0X80;
CMD();
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
 RD3=0;
 RD2=1;
 delay(65000); 
}
 
 
 //delay(50);
 //RD2=0;
 //RD3=0;
}

else
{ 
 LCD=0X01;
 CMD();

 RD2=0;
 RD3=0;
 delay(200);

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

}
//}

void interrupt isr()
{
static int l=0;
char ch[];
int z=0;
if(RCIF==1)
{

ch[l]=RCREG;
l++;
if(l==10)
{
l=0;
z=1;
}
RCIF=0;
}
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

	