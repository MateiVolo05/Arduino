#include "USART.h"
#include "Segments.h"
#include "Mode.h"

void setup() {
  USART_Init(MYUBRR);
  Print("TOP\n");
  //set prescaler to 4
  TWSR |= (1<<TWPS0);
  TWBR = 18;
  TWCR = (1<<TWEN); //enable TWI
  segments_setup();
  Print("SETUP\n");
  Print("END\n");
}

int state = 0;

void loop() {
  unsigned char input=USART_Receive();
  if(input=='A'){
    while(USART_Receive()!='\n')
      ;
    state = 1;
  }
  if(input=='B'){
    while(USART_Receive()!='\n')
      ;
    state = 2;
  }

  if(state==1)
    modeA(input);
  if(state==2)
    modeB(input);
}
