//PORT B
#define led 1
#define button 5
void setup() {
  DDRB |= (1<<led); //set to output
  DDRC |= (1<<button);
  PORTC = 0;
}

// the loop function runs over and over again forever
void loop() {
  volatile bool input = PINC & (1<<button);
  if(input)
    PORTB |= (1<<led);
  else
    PORTB = 0;
}
