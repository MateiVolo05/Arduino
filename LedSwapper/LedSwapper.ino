//PORT B
#define led1 1
#define led2 2
//PORTC
#define button 5
typedef enum states{
  r0, r1, g0, g1
};
states currentState=r0;
void setup() {
  DDRB |= (1<<led1); //set to output
  DDRB |= (1<<led2);
  DDRC |= (1<<button);
  PORTC = 0;
}

// the loop function runs over and over again forever
void loop() {
  bool input = PINC & (1<<button);
  switch(currentState){
    case r0:
      if(input)
        currentState=g1;
      break;
    case r1:
    if(!input)
        currentState=r0;
      break;
    case g0:
    if(input)
        currentState=r1;
      break;
    case g1:
    if(!input)
        currentState=g0;
      break;
  }
  
  switch(currentState){
    case r0:
    case r1:
      PORTB=(1<<led1);
      break;
    case g0:
    case g1:
      PORTB=(1<<led2);
      break;
  }

}

//1: r, 0
//2: g, 1
//3: g, 0
//4: r, 1