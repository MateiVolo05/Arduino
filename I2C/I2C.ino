#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28
#define Fcpu 16000000//16MHZ
#define Fscl 100000  //100kHZ
#define BAUD 9600
#define MYUBRR ((Fcpu/16/BAUD)-1)

void USART_Init(unsigned int ubrr){
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

unsigned char USART_Receive(void){
  /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)));
  /* Get and return received data from buffer */
  return UDR0;
}

void USART_Transmit(unsigned char data){
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void Print(char msg[]){
  for(int i=0;msg[i];i++)
    USART_Transmit(msg[i]);
    USART_Transmit('\r');
}

void ERROR(char err[]){
  Print(err);
}

void i2c(unsigned int address, unsigned int reg, unsigned int data){
  Print("Start\n");
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN); //send START condition
  while (!(TWCR & (1<<TWINT))); //wait for START condition to be sent
  if((TWSR & 0xF8) != START) //check value of TWI status
    ERROR("START ERR\n");

  Print("Load address\n");
  TWDR = address << 1; //load address
  TWCR = (1<<TWINT) | (1<<TWEN); //start transmission of address
  while(!(TWCR & (1<<TWINT))); //wait for TWINT flag set
  if ((TWSR & 0xF8) != MT_SLA_ACK) //check value of TWI status
    ERROR("ADDRESS ERR\n");

  Print("Load reg\n");
  TWDR = reg; //load register
  TWCR = (1<<TWINT)|(1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
  if((TWSR & 0xF8) != MT_DATA_ACK) 
    ERROR("REG ERR\n");

  Print("Load data\n");
  TWDR = data; //load data
  TWCR = (1<<TWINT) | (1<<TWEN); //start transmission of data
  while(!(TWCR & (1<<TWINT))); //wait for TWINT flag set
  if((TWSR & 0xF8)!= MT_DATA_ACK) //check value of TWI status
    ERROR("DATA ERR\n");

  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); //send STOP condition
  Print("Stop\n");
}

void i2c_setup(){
  i2c(0, 0x09, 0xFF); //decode mode
  Print("OK1\n");
  i2c(0, 0x0A, 0x0F); //brightness=max
  Print("OK2\n");
  i2c(0, 0x0B, 0x01); //scan limit: display digits 0-1
  Print("OK3\n");
  i2c(0, 0x0C, 0x01);  //shutdown: normal operation
  Print("OK4\n");
}

void setup() {
  USART_Init(MYUBRR);
  Print("TOP\n");
  //set prescaler to 4
  TWSR |= (1<<TWPS0);
  TWBR = 18;
  TWCR = (1<<TWEN); //enable TWI
  i2c_setup();
  Print("SETUP\n");
  Print("END\n");
  i2c(0, 0x01, 0);
  i2c(0, 0x02, 0);
}

int cnt = 0; //nr cate cifre modulo nr_displays apar
int nr1 = 0;
int nr2 = 0;

void loop() {
  unsigned char input=USART_Receive();
  if(input>='0' && input<='9'){
    if(cnt==0)
      nr2 = input - '0';
    else
      nr1 = input - '0';
    cnt = (cnt + 1) % 2;
  }
  if(input=='\n' && cnt){
    nr1 = nr2;
    nr2 = 0;
  }
  if(input=='\n'){
    i2c(0, 0x01, nr1);
    i2c(0, 0x02, nr2);
    cnt = 0;
  }
}
