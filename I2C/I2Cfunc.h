#ifndef I2C_FUNC_H_
#define I2C_FUNC_H_

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28

void i2c_setup();
void i2c_send(unsigned int address, unsigned int reg, unsigned int data);

#endif