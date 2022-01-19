#include "io430.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
void setup_clock(){
BCSCTL1 = CALBC1_1MHZ; //chon tan so dao dong noi là 1Mhz
DCOCTL = CALDCO_1MHZ; //chon tan so dao dong noi là 1Mhz
}

void setup_ADC(){
ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON +ADC10ON + ADC10IE;
__delay_cycles(10000);
ADC10CTL1 = INCH_7; //chon kenh ngo vao la kenh A7
ADC10AE0 = 0x80; //P1.7 option selectUART_Init();
}12:48 CH 01/07/2021

int value_ADC(){
ADC10CTL0 |= ENC + ADC10SC; //cho phép va bat dau chuyen doi
  __delay_cycles(30);
return ADC10MEM;
}

void setup_UART(void){                    
	// 1. Set UCSWRST and source clocks
	UCA0CTL1 |= UCSWRST + UCSSEL_2;      // USCI logic held in reset state + SMCLK
	// 2. Initializing all USCI registers with UCSWRST = 1
	// DEFAULT: parity disabled - LSB - 8bit data - one stop bit - UART mode - Asynchoronous mode (page 434)
	UCA0CLT0 =0;
	UCA0BR0 = 104;                        // 9600 Baud with 1MHz clock (Refer- 
	UCA0BR1 = 0;                          // 9600 Baud with 1MHz clock -Pg.15-22)
	UCA0MCTL = UCBRS_1 + UCBRF_0;  
	// 3. Configure ports
	P1SEL |= BIT1 + BIT2;
	P1SEL2 |= BIT1 + BIT2;  // (page 43) 
	// 4. Clear UCSWRST via software
	UCA0CTL1 &= ~UCSWRST;
	// 5. Enable interrupts via UCAxRXE or UCAxTXIE
	IE2 |= UCA0RXIE;}

void UART_write(char byte){
	while(! (IFG2 & UCA0TXIFG)); //cho den khi bo dem transmit rong - UCA0TXIFG is set when UCA0TXBUF is empty
	UCA0TXBUF = byte;}


char UART_read(void){
	while(! (IFG2 & UCA0RXIFG)); // cho den khi bo dem receiver tran - UCA0RXIFG is set when UCA0RXBUF  has received a complete character
	return UCA0RXBUF ; }

void UART_print(char *str){
         while(*str)
                  UART_write(*str++);
         UART_write(0x0A);}

void UART_readBytes(char *str){
        while(1){	
              *str=UART_read();
              if (*str == 0x0A)		
                      break;
              str++;}				
        *++str = '\0';}   

void UART_Write_Int(unsigned long n){
        unsigned char buffer[16];
        unsigned char i,j;
           if(n == 0) {
	UART_Write('0');
	return;
              }
           for (i = 15; i > 0 && n > 0; i--) {
      	buffer[i] = (n%10)+'0';
	n /= 10;
           }
           for(j = i+1; j <= 15; j++) {
	UART_Write(buffer[j]);
           }
}

void delayms(int ms)
{
  for(int i = 0; i<ms;i++)
  __delay_cycles(1000);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////