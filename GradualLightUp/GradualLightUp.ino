//PORT B
#define led 1
#define delay 5000
void setup() {
  DDRB |= (1<<led);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //Non-Inverting mode
  TCCR1A |= (1<<7);
  //Fast PWM mode 8 bit
  TCCR1A |= (1<<0);
  TCCR1B |= (1<<3);
  //Set presclaer to 256
  TCCR1B |= (1<<2);
}

void loop() {
  for(int i=0;i<255;i++){
    OCR1A = i;
    volatile int j=delay;
    while(j--);
  }
  for(int i=255;i>=0;i--){
    OCR1A = i;
    volatile int j=delay;
    while(j--);
  }
}
