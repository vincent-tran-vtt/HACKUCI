/*
Engineers: Vincent Tran
Purpose: Cool looking LED matrix
*/

#include <stdint.h>

//Pre-processor Directives Section
//Constant declarations to access port registers using:
//DATA (read/write data): 3FC
//DIR (digital I/O direction): 400
//AFSEL (alternate function select): 420
//PUR (pull up select): 510
//DEN (digital enable):51C
//AMSEL (analog mode select): 528
//PCTL (port control): 52C

// PORT A register definitions
//PORT A Base: 0x 4000 4000
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))

// PORT B register definitions
// PORT B Base: 0x 4000 5000
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

// PORT E register definitions
// PORT E Base: 0x 4002 5000
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
// system control register RCGC2 definition
//run mode clock running control
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) //base: 400F E000, 400F E000 + 108 = 400F E108
	
//constants
#define LED_COLUMN_1						(*((volatile unsigned long *)0x400040FC)) //PA7-2: 0x 1111 1100
#define LED_COLUMN_2						(*((volatile unsigned long *)0x400050FE)) //PB7-1: 0x 1111 1110
#define LED_ROW									(*((volatile unsigned long *)0x4002401F)) //PE4-0: 0x 0001 1111
	
#define A									0x04 //PA2: 0000 0100
#define B 								0x08 //PA3: 0000 1000
#define C 								0x10 //PA4: 0001 0000
#define D 								0x20 //PA5: 0010 0000
#define E 								0x40 //PA6: 0100 0000
#define F 								0x80 //PA7: 1000 0000

#define G									0x02 //PB1: 0000 0010
#define H									0x04 //PB2: 0000 0100
#define I 								0x08 //PB3: 0000 1000
#define J 								0x10 //PB4: 0001 0000
#define K 								0x20 //PB5: 0010 0000
#define L 								0x40 //PB6: 0100 0000
#define M 								0x80 //PB7: 1000 0000

#define one								0x01 //PE0: 0000 0001
#define two								0x02 //PE1: 0000 0010
#define three							0x04 //PE2: 0000 0100
#define four 							0x08 //PE3: 0000 1000
#define five 							0x10 //PE4: 0001 0000

//Function Prototypes
void PortA_Init(void);
void PortB_Init(void);
void PortE_Init(void);
void display_HI(void);
void Delay(uint8_t n_25ms);
void test(void);

int main(void){
	PortA_Init();
	PortB_Init();
	PortE_Init();
	while(1){
		test();
		//display_HI();
	}
}

/*LED MATRIX 13x5 
column 1: [A-F]
column 2: [G-M])
Row: [1-5]
Display refreshes by row, top to bottom
		Column 1  |   Column 2
	A B C D E F | G H I J K L M
1
2
3
4
5
*/
//test
void test(void){
	LED_COLUMN_1 |= A;
	Delay(1);
	LED_COLUMN_1 |= B;
	Delay(1);
	LED_COLUMN_1 |= C;
	Delay(1);
	LED_COLUMN_1 |= D;
	Delay(1);
	LED_COLUMN_1 |= E;
	Delay(1);
	LED_COLUMN_1 |= F;
	
	LED_COLUMN_2 |= G;
	Delay(1);
	LED_COLUMN_2 |= H;
	Delay(1);
	LED_COLUMN_2 |= I;
	Delay(1);
	LED_COLUMN_2 |= J;
	Delay(1);
	LED_COLUMN_2 |= K;
	Delay(1);
	LED_COLUMN_2 |= L;
	Delay(1);
	LED_COLUMN_2 |= M;
	Delay(1);
	//row two off
	//LED_ROW = three;
}

//Display: "HI"
void display_HI(void){
	//turns all rows off
	LED_ROW |= one;
	LED_ROW |= two;
	LED_ROW |= three;
	LED_ROW |= four;
	LED_ROW |= five;
	Delay(1);
	Delay(1);
	
	//Row 1
	//Letter H
	LED_COLUMN_1 |= B;
	LED_COLUMN_2 |= E;
	//Letter I
	LED_COLUMN_2 |= G;
	LED_COLUMN_2 |= H;
	LED_COLUMN_2 |= I;
	//row one on
	LED_ROW &= ~0x01;
	//LED_ROW &= ~one;
	//delay
	Delay(1);
	Delay(1);
	//row off
	//LED_ROW |= one;
	//column off
	//LED_COLUMN_1 = 0x00;
	//LED_COLUMN_2 = 0x00;

/*
	//updates row 2
	//Letter H
	LED_COLUMN_1 |= B;
	LED_COLUMN_2 |= E;
	//Letter I
	LED_COLUMN_2 |= H;
	//row on
	LED_ROW &= ~two;
	//delay
	Delay(1);
	//row off
	LED_ROW |= two;
	//column off
	LED_COLUMN_1 = 0x00;
	LED_COLUMN_2 = 0x00;
	
	//updates row 3
	//Letter H
	LED_COLUMN_1 |= B;
	LED_COLUMN_1 |= C;
	LED_COLUMN_1 |= D;
	//Letter I
	LED_COLUMN_2 |= H;
	//row on
	LED_ROW &= ~three;
	//delay
	Delay(1);
	//row off
	LED_ROW |= three;
	//column off
	LED_COLUMN_1 = 0x00;
	LED_COLUMN_2 = 0x00;
	
	//updates row 4
	//Letter H
	LED_COLUMN_1 |= B;
	LED_COLUMN_1 |= E;
	//Letter I
	LED_COLUMN_2 |= H;
	//row on
	LED_ROW &= ~four;
	//delay
	Delay(1);
	//row off
	LED_ROW |= four;
	//column off
	LED_COLUMN_1 = 0x00;
	LED_COLUMN_2 = 0x00;
	
	//updates row 5
	//Letter H
	LED_COLUMN_1 |= B;
	LED_COLUMN_1 |= E;
	//Letter I
	LED_COLUMN_2 |= G;
	LED_COLUMN_2 |= H;
	LED_COLUMN_2 |= I;
	//row on
	LED_ROW &= ~five;
	//delay
	Delay(1);
	//row off
	LED_ROW |= five;
	//column off
	LED_COLUMN_1 = 0x00;
	LED_COLUMN_2 = 0x00;
	*/
}


// Subroutine to initialize port A pins PA7-2
// PA2-7: 1111 1100
void PortA_Init(void){
	SYSCTL_RCGC2_R |= 0x00000001; //enable A clock
	while ((SYSCTL_RCGC2_R&0x00000001)!=0x00000001){} // wait for the clock to be ready

	GPIO_PORTA_AMSEL_R &= ~0xFC; //disable anlog funtion for PA7-2
	GPIO_PORTA_PCTL_R &= ~0xFFFFFF00; //GPIO clear PCTL bits for PA7-2
	GPIO_PORTA_DIR_R |= 0xFC; //PA7-2 output
	GPIO_PORTA_AFSEL_R &= ~0xFC; //no alternate function for PA7-2
	GPIO_PORTA_DEN_R |= 0xFC; //enable digital pins PA7-2
}

// Subroutine to initialize port B pins PB7-1
// PB1-7: 1111 1110
void PortB_Init(void){
	SYSCTL_RCGC2_R |= 0x00000002; //enable B clock
	while ((SYSCTL_RCGC2_R&0x00000002)!=0x00000002){} // wait for the clock to be ready

	GPIO_PORTB_AMSEL_R &= ~0xFE; //disable anlog funtion for PB7-1
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFF0; //GPIO clear PCTL bits for PB7-1
	GPIO_PORTB_DIR_R |= 0xFE; //PB7-1 output
	GPIO_PORTB_AFSEL_R &= ~0xFE; //no alternate function for PB7-1
	GPIO_PORTB_DEN_R |= 0xFE; //enable digital pins PB7-1
}

// Subroutine to initialize port E pins PE4-0 for input
void PortE_Init(void){
	SYSCTL_RCGC2_R |= 0x00000010; //enable E clock
	while ((SYSCTL_RCGC2_R&0x00000010)!=0x00000010){} // wait for the clock to be ready

	GPIO_PORTE_AMSEL_R &= ~0x1F; //disable anlog funtion for PE4-0
	GPIO_PORTE_PCTL_R &= ~0x000FFFFF; //GPIO clear PCTL bits for PE4-0
	GPIO_PORTE_DIR_R |= 0x1F; //PE4-0 output
	GPIO_PORTE_AFSEL_R &= ~0x1F; //no alternate function for PE4-0
	GPIO_PORTE_DEN_R |= 0x1F; //enable digital pins PE4-0
}

//busy wait delay
void Delay(uint8_t n_25ms){
	unsigned long time;
	unsigned int i;
	time = 2*727240*100/91;  // 0.25 sec
	for(i = 0; i < n_25ms; i++){
		while(time){
			time--;
		}
	}
	for (time=0;time<1000;time=time+10) {
	}
}