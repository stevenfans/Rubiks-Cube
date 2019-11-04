// 0.Documentation Section 
// main.c
// CECS 490B UART Communication Protocol
// Authors: Jonic Mecija
// Date: October 31, 2019

#include "tm4c123gh6pm.h"

// Declarations Section
//   Global Variables
unsigned int mode = 0;
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

//   Function Prototypes
void PortF_Init();
void UART_Init(void);
void UART1_Init(void);
void OutCRLF(void);

unsigned char UART_InCharNonBlocking(void);
void push(unsigned char x);
unsigned long charHex(char character);

// UART 0 
void UART0_OutUHex(unsigned long number);
unsigned char UART0_InChar(void);
void UART0_OutString(char *pt);

// UART 1
void UART_OutChar(unsigned char data);
void UART_OutUHex(unsigned long number);
unsigned long UART_InUHex(void);
unsigned char UART_InChar(void);
void UART_OutString(char *pt);


// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
unsigned char n;																		
unsigned char data;
unsigned char hello[100];
unsigned char buffer[100];
char a = 0x0FF;
char checkSum;
int top = -1;
int i,j,k,c;
int sum = 0;
int isValid;

int main(void){    
	UART_Init();
	UART1_Init();
	PortF_Init();	
		
  while(1)
	{
		n = UART_InUHex();
		
		//toggle bit BLUE
		if (n == 0x31)
			{
				// blue
				while(data != 0x26)
				{
					GPIO_PORTF_DATA_R = 0x04;
					//UART_OutString(" Enter data to transmit: ");
					data = UART_InUHex();
					OutCRLF();
					
					// push data to top of stack
					if (data!=0x26){ push(data);}
				}
			}
			
		//stop bit RED
		else if(data == 0x26)
			{
				//UART_OutString(" Not transmitting. Data you entered: ");
				GPIO_PORTF_DATA_R = 0x02;
				
				// output array of data
				for (i = 0; i < top+1; i++)
					{
						UART_OutUHex(hello[i]);
						sum+= hello[i];
					}
				
				checkSum = ~(sum & a);
	
				//UART_OutString("\nthe sum of numbers u entered: ");
				isValid = checkSum + (sum & a);

				UART_OutUHex(sum);
				UART_OutUHex(checkSum);
				
				if(isValid == 0xFF){
					UART0_OutString("data is valid");
				}
				else if (isValid != 0xFF){
					UART0_OutString("data is not valid");
				}

				// add checkSum to instruction word
				top++;
				hello[top] = checkSum;
				
//				for (i = 0; i < top+1; i++)
//					{
//						UART_OutUHex(buffer[i]);
//					}
					
				// reset stack
				data = 0;
				top = -1;
				sum = 0;
			}
		
	}
	
	// output to terminal via UART 0
	for (i = 0; i < 5; i++)
	{
		UART0_OutUHex(hello[i]);
	}
	
}

// push to stack
void push(unsigned char x)
{
	top++;
	hello[top] = x;
	//buffer[top] = x;
}

void PortF_Init()
{
	unsigned long delay;//for LED debugging
	SYSCTL_RCGC2_R 		|= 0x00000020;		//activate Port F
	delay = SYSCTL_RCGC2_R; 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;			//unlock Port F
	GPIO_PORTF_CR_R	  |= 0x1F;					//allow changes to PF4,3,2,1,0
	GPIO_PORTF_AMSEL_R&= 0xE0;					//disable analog for PF4,3,2,1,0
	GPIO_PORTF_PCTL_R &= 0xFFF00000;		//set PF4,3,2,1,0 as GPIO
	GPIO_PORTF_DIR_R  &= 0xEE;					//set PF4,0 as input
	GPIO_PORTF_DIR_R  |= 0x0E;					//set PF3,2,1 as output
	GPIO_PORTF_AFSEL_R&= 0xE0;					//disable alt func PF4,3,2,1,0
	GPIO_PORTF_PUR_R  |= 0x11;					//pull up resistors PF4,0
	GPIO_PORTF_DEN_R  |= 0x1F;					//digital enable PF4,3,2,1,0
}

void UART_Init(void)
{		
	volatile unsigned long delay;
// 96600 baud rate 16Mhz
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A 
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 104;       // IBRD = int(16Mhz / (16 * 96600)) = int(104.166667)
  UART0_FBRD_R = 11;        // FBRD = round(0.166667* 64 +0.5) = 11
                            // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

void UART1_Init(void)
{		
	volatile unsigned long delay;
// 96600 baud rate 16Mhz
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 104;       // IBRD = int(16Mhz / (16 * 96600)) = int(104.166667)
  UART1_FBRD_R = 11;        // FBRD = round(0.166667* 64 +0.5) = 11
                            // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1-0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1-0
                                        // configure PB1-0 as UART
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB
}







// ************************ UART 1 ****************************** //

unsigned char UART_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
	
	//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
}

void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
	
	//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
}

//--------------------------UART_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART_OutUHex(unsigned long number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART_OutUHex(number/0x10);
    UART_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART_OutChar(number+'0');
     }
    else{
      UART_OutChar((number-0x0A)+'A');
    }
  }
}

unsigned long UART_InUHex(void){
unsigned long number=0, digit, length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      UART_OutChar(character);
    }
// Backspace outputted and return value changed if a backspace is inputted
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

// ************************************************************* //




// ************************ UART 0 ****************************** //

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART0_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//--------------------------UART_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART0_OutUHex(unsigned long number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART0_OutUHex(number/0x10);
    UART0_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART0_OutChar(number+'0');
     }
    else{
      UART0_OutChar((number-0x0A)+'A');
    }
  }
}

void UART0_OutString(char *pt){
  while(*pt){
    UART0_OutChar(*pt);
    pt++;
  }
}

// ******************************************************** //




void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}


void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}



unsigned char UART_InCharNonBlocking(void){
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  } else{
    return 0;
  }
//------------UART_InCharNonBlocking------------
// Get oldest serial port input and return immediately
// if there is no data.
// Input: none
// Output: ASCII code for key typed or 0 if no character
}




unsigned long charHex(char character){
unsigned long number=0, digit, length=0;

  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      UART_OutChar(character);
    }
// Backspace outputted and return value changed if a backspace is inputted
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

