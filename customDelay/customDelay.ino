//PORT B
#define led 1
#define frec 16000000
//delay<=1s
#define delay 0.5
void setup() {
  DDRB |= (1<<led);

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //ORC1A=t*f/prescaler - 1
  OCR1A = delay*frec/256-1; //TOP

  TCCR1A |= (1<<6); //toggle on match
  TCCR1B |= (1<<3); //set to CTC
  //set prescaler to 256
  TCCR1B |= (1<<2);

  //led-ul sta aprind pt <delay> sec si stins tot atata timp
}

void loop() {
  
}
