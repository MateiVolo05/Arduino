#include <Arduino.h>
#include "I2Cfunc.h"
#include "USART.h"

void i2c_setup(){
  //set prescaler to 4
  TWSR |= (1<<TWPS0);
  TWBR = 18;
  TWCR = (1<<TWEN); //enable TWI
}

void i2c_send(unsigned int address, unsigned int reg, unsigned int data){
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