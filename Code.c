#include <stdio.h>
#include <stm32f4xx.h>

# define a_on GPIOB->BSRRH=(1<<13)
# define b_on GPIOB->BSRRH=(1<<14)
# define c_on GPIOB->BSRRH=(1<<15)
# define d_on GPIOA->BSRRH=(1<<8)
# define e_on GPIOA->BSRRH=(1<<9)
//# define f_on GPIOA->BSRRH=(1<<10)
# define g_on GPIOA->BSRRH=(1<<11)

# define a_off GPIOB->BSRRL=(1<<13)
# define b_off GPIOB->BSRRL=(1<<14)
# define c_off GPIOB->BSRRL=(1<<15)
# define d_off GPIOA->BSRRL=(1<<8)
# define e_off GPIOA->BSRRL=(1<<9)
//# define f_off GPIOA->BSRRL=(1<<10)
# define g_off GPIOA->BSRRL=(1<<11)

#define digit1_on GPIOA->BSRRH=(1<<12)
#define digit1_off GPIOA->BSRRL=(1<<12)

void led_for_3rd(void);
void led_for_2nd(void);
void display(void);
void motor(void);
void lcd_ini(void);
void display_value(unsigned int value);
void lcd_data(char j);
void lcd_cmd(char i);
char keypad(void);
volatile uint32_t msTicks; /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
 SysTick_Handler
----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
 msTicks++;
}
void Delay (uint32_t dlyTicks) { 
uint32_t loop=0,dly=0,loope=0;
dly = dlyTicks ; 
for(loop=0;loop<dly;loop++){
for(loope=0;loope<10000;loope++){
__nop();
}
}
}
unsigned long LCDDATA=0X00000000;
unsigned long op=0;
int main (void) {
 SystemCoreClockUpdate(); // Get Core Clock Frequency
 /*----------------------------------------------------------------------------
 Add your code to enable Ports that can be used for this program.
	port B & E for LCD 
	PORT D for KEYpad
----------------------------------------------------------------------------*/ 
	  RCC->AHB1ENR|=(1<<0);
	  RCC->AHB1ENR|=(1<<1);		//GPIOB IS ENABLE
	  RCC->AHB1ENR|=(1<<2);
	  
	GPIOB->MODER=0X55555555; //
	GPIOB->OTYPER=0x00000000;		//output in push-pull configuration
	GPIOB->OSPEEDR=0xAAAAAAAA;  //to setup the speed
	GPIOB->PUPDR=0x00000000;
	
		GPIOA->MODER = 0x01551540;
    GPIOA->OTYPER = 0x00000000;
    GPIOA->OSPEEDR = 0xAAAAAAAA;
    GPIOA->PUPDR =   0x000040AA; 
    
   
	
	int i=1;
	
while(1){
	

	while(i<2){
		
		display();
		
		i++;
	
	}
	
keypad();

}
}
char keypad(void){
	
char key_pressed=0;
//Row 1 = 1 & scanning of Col 1 , Col 2 , Col 3/
//GPIOA->BSRR = ((1 << 7) )
	
 if((GPIOA->IDR & 0x00000001) == 0x00000001) {//a0
key_pressed = 1 ;
display_value(1);
motor();
Delay(1);	 
GPIOA->IDR = 0x00000000;
}
 else if((GPIOA->IDR & 0x00000002) == 0x00000002) {//a1
key_pressed = 2 ;
	display_value(2);
 led_for_2nd();
Delay(1);
GPIOA->IDR = 0x00000000;
}
else if((GPIOA->IDR & 0x00000004) == 0x00000004) {//a2
key_pressed = 3 ;
	display_value(3);
	led_for_3rd();
Delay(1);
GPIOA->IDR = 0x00000000;
}
}
void display_value(unsigned int value)
{
			
	digit1_off;
	
	
	switch(value){
		
		case 0:
			a_on;
			b_on;
			c_on;
			d_on;
		  e_on;
			//f_on;
			g_off;
			
			break;
		
		case 1:
			a_on;
			b_off;
			c_off;
			d_on;
		  e_on;
			//f_on;
			g_on;
		
			break;
		
		case 2:
		
			a_off;
			b_off;
			c_on;
			d_off;
		  e_off;
			//f_on;
			g_off;
			
			break;
		
		case 3:
			a_off;
			b_off;
			c_off;
			d_off;
		  e_on;
			//f_on;
			g_off;

			break;
		
		case 4:
			a_off;
			b_on;
			c_on;
			d_off;
		  e_off;
			//f_on;
			g_on;

			break;
		
		case 5:
			a_on;
			b_off;
			c_on;
			d_on;
		  e_off;
			//f_on;
			g_on;
			break;
		
		case 6:
			a_on;
			b_off;
			c_on;
			d_on;
		  e_on;
			//f_on;
			g_on;
			break;
		
		case 7:
			a_on;
			b_on;
			c_on;
			d_off;
		  e_off;
			//f_off;
			g_off;
			break;
		
		case 8:
			a_on;
			b_on;
			c_on;
			d_on;
		  e_on;
			//f_on;
			g_on;
			break;
		
		case 9:
			a_on;
			b_on;
			c_on;
			d_off;
		  e_off;
			//f_on;
			g_on;
	}
	
}

void motor(){
	int ENGG;
	
	while(ENGG<53){
GPIOA->BSRRL = ((1 << (3)) );
GPIOA->BSRRH = ((1 << (4)) );
GPIOA->BSRRH = ((1 << (5)) );
GPIOA->BSRRH = ((1 << (6)) );

	//delay

	Delay(5);
	
GPIOA->BSRRH = ((1 << (3)) );
GPIOA->BSRRL = ((1 << (4)) );
GPIOA->BSRRH = ((1 << (5)) );
GPIOA->BSRRH = ((1 << (6)) );
	
	//delay
	Delay(5);
	
GPIOA->BSRRH = ((1 << (3)) );
GPIOA->BSRRH = ((1 << (4)) );
GPIOA->BSRRL = ((1 << (5)) );
GPIOA->BSRRH = ((1 << (6)) );
	
	//delay
	Delay(5);
	
GPIOA->BSRRH = ((1 << (3)) );
GPIOA->BSRRH = ((1 << (4)) );
GPIOA->BSRRH = ((1 << (5)) );
GPIOA->BSRRL = ((1 << (6)) );
Delay(5);
ENGG++;
	

}
	}

void display(){
	lcd_ini();
	lcd_cmd(0x80); // line 1
	
  	lcd_data('P');
	lcd_data('R');
	lcd_data('E');
	lcd_data('S');
	lcd_data('S');
	
	lcd_data(' ');
	
	lcd_data('1');
	lcd_data(' ');
	lcd_data('F');
	lcd_data('O');
	lcd_data('R');
	lcd_data(' ');
	lcd_data('C');
	lcd_data('A');
	lcd_data('K');
	lcd_data('E');
	

  	lcd_cmd(0xC0);
	//lcd_cmd(0x06);	

	lcd_data('P');
	lcd_data('R');
	lcd_data('E');
	lcd_data('S');
	lcd_data('S');
	
	lcd_data(' ');
	
	lcd_data('2');
	lcd_data(' ');
	lcd_data('F');
	lcd_data('O');
	lcd_data('R');
	lcd_data(' ');
	lcd_data('L');
	lcd_data('A');
	lcd_data('Y');
	lcd_data('S');

	lcd_cmd(0xC0);
	//lcd_cmd(0x06);	

	lcd_data('P');
	lcd_data('R');
	lcd_data('E');
	lcd_data('S');
	lcd_data('S');
	
	lcd_data(' ');
	
	lcd_data('3');
	lcd_data(' ');
	lcd_data('F');
	lcd_data('O');
	lcd_data('R');
	lcd_data(' ');
	lcd_data('C');
	lcd_data('O');
	lcd_data('K');
	lcd_data('E');
}

void lcd_ini(void)
{
Delay(10); //10
lcd_cmd(0x38);
lcd_cmd(0x0C);
lcd_cmd(0x01);
Delay(10); //10
}
void lcd_cmd(char i)
{
unsigned long r=0;
char loop=0;
r |= i;
//for(loop=0;loop<=7;loop++)
//{
// r = r << 1;
//}
GPIOB->BSRRH = ((1 << 8) );
LCDDATA = r;
GPIOB->ODR &= 0xFFFFFF00; //0000 0000 0000 0000 0000 0100 0000 0000
GPIOB->ODR |= LCDDATA;
GPIOB->BSRRL = ((1 << 10) );
Delay(50); //100
GPIOB->BSRRH = ((1 << 10) );
}
void lcd_data(char j)
{
unsigned long r=0;
char loop=0;
r |= j;
//for(loop=0;loop<=7;loop++){
// r = r << 1;
//}
GPIOB->BSRRL = ((1 << 8) );
LCDDATA = r;
GPIOB->ODR &= 0xFFFFFF00;
GPIOB->ODR |= LCDDATA;
GPIOB->BSRRL = ((1 << 10) );
Delay(50); //100
GPIOB->BSRRH = ((1 << 10) );
//Delay(50); //10
}

void led_for_2nd()
{
        GPIOA->ODR|=(1<<10);
	Delay(3000);
	GPIOA->ODR &=~(1<<10);
}

void led_for_3rd()
{
	GPIOB->ODR|=(1<<12);
	Delay(3000);
	GPIOB->ODR &=~(1<<12);
}
