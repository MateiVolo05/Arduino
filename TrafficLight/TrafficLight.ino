// the setup function runs once when you press reset or power the board
#define delay 100000
//PORT B
#define ledR 1
#define ledG 2
#define ledV 3
volatile long long int i=delay;
void setup() {
  DDRB |= (1<<ledR); //set to output
  DDRB |= (1<<ledG);
  DDRB |= (1<<ledV);
}

// the loop function runs over and over again forever
void loop() {
  PORTB |= (1<<ledR); //put bit on high => led ON
  i=delay;
  while(i--);                     // wait for a second
  PORTB |= (1<<ledG);
  i=delay;
  while(i--);                    // wait for a second
  PORTB |= (1<<ledV);
  i=delay;
  while(i--);
  PORTB ^= (1<<ledR);
  i=delay;
  while(i--);
  PORTB ^= (1<<ledG);
  i=delay;
  while(i--);
  PORTB ^= (1<<ledV);
  i=delay;
  while(i--);
}
