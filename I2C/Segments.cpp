#include <Arduino.h>
#include "Segments.h"
#include "USART.h"

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

void segments_setup(){
  i2c(0, 0x09, 0xFF); //decode mode
  Print("OK1\n");
  i2c(0, 0x0A, 0x0F); //brightness=max
  Print("OK2\n");
  i2c(0, 0x0B, 0x03); //scan limit: display digits 0-3
  Print("OK3\n");
  i2c(0, 0x0C, 0x01);  //shutdown: normal operation
  Print("OK4\n");
  i2c(0, 0x01, 0);
  i2c(0, 0x02, 0);
  i2c(0, 0x03, 0);
  i2c(0, 0x04, 0);
}