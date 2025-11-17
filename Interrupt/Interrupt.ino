//PORT B
#define led 0
//PORT D
#define button 2
void setup() {
  DDRB |= (1<<led); //led-output
  DDRD &= ~(1<<button); //button-input
  PORTD |= (1<<button); //pull-up
  EICRA |= (1<<0); // any logical change => interrupt
  EIMSK |= (1<<0); // use INT0(PD2)
}

ISR(INT0_vect){
  if((PIND & (1<<button)))
    PORTB = 0;
  else
   PORTB = (1<<led);
}

void loop() {
  // put your main code here, to run repeatedly:

}
