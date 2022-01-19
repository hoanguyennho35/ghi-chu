#ifndef UART_H_
#define UART_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup_clock();		//khoi tao xung clock
void setup_ADC();		//khoi tao ADC
void setup_ADC();		//lay gia tri cua ADC
void setup_UART(void);         //khoi tao thong so UART
char UART_read(void);     	   //doc 1 byte vao
void UART_write(char byte);   // viet 1 byte ra 
void UART_print(char *str);	  // viet mot chuoi byte
void UART_readBytes(char *str); // doc mot chuoi byte/////////////////////////////////////////////////////////////////////////////////////////////////////
void delayms(int ms);     //delay thoi gian(ms)
void UART_Write_Int(unsigned long n);       //in so
#endif