/*
 * Sercom.h
 *
 * Created: 1/31/2020 9:16:43 AM
 *  Author: VKaiser
 */ 


#ifndef SERCOM_H_
#define SERCOM_H_

#include "main.h"


 /*
  * Global Variables
  */
#define MAX_RX_BUFFER_LENGTH	256
#define I2C_SLAVE_ADDRESS		0x18
#define I2C_DATA_LENGTH			10
#define I2C_TIMEOUT				10

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

struct i2c_master_module i2c_master_instance; 
struct i2c_master_config config_i2c_master;
struct i2c_master_packet write_packet;
struct i2c_master_packet read_packet;


void configure_i2c_master(void);
void i2c_write_complete_callback(struct i2c_master_module *const module);
void configure_i2c_callbacks(void);
/*
int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len);

int8_t i2c_slWrite(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_slRead(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t len);
*/
int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len);

int8_t i2c_slWrite(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_slRead(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t len);



#endif /* SERCOM_H_ */