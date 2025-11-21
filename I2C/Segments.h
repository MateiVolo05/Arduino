#ifndef SEGMENTS_H_
#define SEGMENTS_H_

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28

void Print(char msg[]);
void ERROR(char err[]);
void i2c(unsigned int address, unsigned int reg, unsigned int data);
void segments_setup();

#endif