#ifndef USART_H_
#define USART_H_

#define Fcpu 16000000//16MHZ
#define Fscl 100000  //100kHZ
#define BAUD 9600
#define MYUBRR ((Fcpu/16/BAUD)-1)

void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);

#endif