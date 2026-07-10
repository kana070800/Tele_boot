#ifndef __I2C__
#define __I2C__

void I2C1_init(void);

void I2C1_write(int sensor,uint8_t reg,uint16_t data);
int16_t I2C1_read(int sensor, uint8_t reg);
void __I2C1_read(int sensor);
void I2C1_Read_Polling(uint8_t reg, uint8_t *data_h, uint8_t *data_l);
void init_ina3221(void);
void init_ina226(void);

#endif
