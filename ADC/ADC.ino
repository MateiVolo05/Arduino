#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC/16/BAUD)-1)
//PORT C
#define analog 0
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

void USART_Transmit(unsigned char data)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void setup() {
  USART_Init(MYUBRR);
  ADCSRA |= (1<<ADEN); //Enable ADC
  ADMUX |= (1<<REFS0); //AVCC with external capacitor at AREF pin
  //Set prescaler to 128
  ADCSRA |= (1<<ADPS2);
  ADCSRA |= (1<<ADPS1);
  ADCSRA |= (1<<ADPS0);
  DDRB |= (1<<led);
}

unsigned int ADC_Read(){
  ADCSRA |= (1<<ADSC); //Conversion start
  while(ADCSRA & (1<<ADSC)); //Wait
  return ADC; //Return the value
}

void loop() {
  unsigned int input = ADC_Read();
  unsigned int percentage = (unsigned long)input*100/1023;
  float voltage = (input * 5.0)/1023;
  char voltageStr[10];
  dtostrf(voltage, 4, 2, voltageStr);

  char buffer[50];
  sprintf(buffer, "\rValue: %4u   Percentage: %3u%%   Voltage: %sV", input, percentage, voltageStr);
  for(int i=0;buffer[i]!='\0';i++)
    USART_Transmit(buffer[i]);

  OCR1A = input;
  delay(1000);
}
