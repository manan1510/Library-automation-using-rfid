
                 //Check for valid number //

#include<pic.h> 
#include <string.h>
#define LCD PORTD
#define RS RC0  
#define EN RC1  

unsigned char arr5[9]="this code";
unsigned char arr6[13]="this code not";
unsigned char arr7[7]="matched";

unsigned char data[11];
unsigned char mobile1[11]="9811869035";
unsigned char mobile2[11]="9211465678";
unsigned char mobile3[11]="9871456554";
unsigned char mobile4[11]="9211034567";
unsigned char mobile5[11]="9911223344";           

void CMD();
void DAT();
void LATCH();

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

a=strcmp(data,mobile1);
b=strcmp(data,mobile2);
c=strcmp(data,mobile3);
d=strcmp(data,mobile4);
e=strcmp(data,mobile5); 
 
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

	