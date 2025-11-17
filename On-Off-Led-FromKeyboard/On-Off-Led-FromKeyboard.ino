#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC/16/BAUD)-1)
//PORT B
#define led 1

void USART_Init(unsigned int ubrr)
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

unsigned char USART_Receive(void)
{
  /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)));
  /* Get and return received data from buffer */
  return UDR0;
}

void USART_Transmit(unsigned char data)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void setup() {
  USART_Init(MYUBRR);
  DDRB |= (1<<led);
}

void loop() {
  char input=USART_Receive();
  if(input){
    PORTB ^= (1<<led);
    if(input=='\n' || input=='\r'){
      USART_Transmit('\r');
      USART_Transmit('\n');
    }
    else
      USART_Transmit(input);
  }
}
