/*
 * Sercom.c
 *
 * Created: 1/31/2020 9:16:35 AM 
 *  Author: VKaiser
 * 
 * SERCOM2: I2C
 * SERCOM0: USART  //Pending
 */ 
 
 #include "DC_sercom.h"
 
 /* Timeout counter. */
 uint16_t timeout = 0;


  /**********************************************************************
 * @fn					- configure_i2c_master
 * @brief				- Set up the I2C Master Module
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
  void configure_i2c_master(void)
  {
	  /* Initialize config structure and software module. */
	  i2c_master_get_config_defaults(&config_i2c_master);

	  /* Change buffer timeout to something longer. */
	  config_i2c_master.buffer_timeout = 10000;

	  /* Initialize and enable device with config. */
	  // SERCOM0 PAD[0] PA08 - SDA
	  // SERCOM0 PAD[1] PA09 - SCL
	  config_i2c_master.pinmux_pad0    = PINMUX_PA08D_SERCOM2_PAD0;
	  config_i2c_master.pinmux_pad1    = PINMUX_PA09D_SERCOM2_PAD1;
	  
	  i2c_master_init(&i2c_master_instance, SERCOM2, &config_i2c_master);
	  i2c_master_enable(&i2c_master_instance);

  }// configure_i2c_master

  /**********************************************************************
 * @fn					- i2c_write_complete_callback
 * @brief				- write to slave until success, overrides weak definition
 *
 * @param[in]			- struct i2c_master_module
 * @param[in]			-  *const module					
 * @return				- void
 *
 * @note				- 
 **********************************************************************/ 
 void i2c_write_complete_callback(struct i2c_master_module *const module)
{
	/* Initiate new packet read */
	i2c_master_read_packet_job(&i2c_master_instance, &read_packet);

} // i2c_write_complete_callback

 /**********************************************************************
 * @fn					- configure_i2c_callbacks
 * @brief				- Write buffer to slave until success.
 *
 * @param[in]			- 
 *
 * @return				- void
 *
 * @note				- called from main
 **********************************************************************/
 void configure_i2c_callbacks(void)
{
	/* Register callback function. */

	i2c_master_register_callback(&i2c_master_instance, i2c_write_complete_callback, I2C_MASTER_CALLBACK_WRITE_COMPLETE);
	i2c_master_enable_callback(&i2c_master_instance, I2C_MASTER_CALLBACK_WRITE_COMPLETE);

	/*
	i2c_master_register_callback(&i2c_master_instance, i2c_read_complete_callback, I2C_MASTER_CALLBACK_READ_COMPLETE);
	i2c_master_enable_callback(&i2c_master_instance, I2C_MASTER_CALLBACK_READ_COMPLETE);
	*/
} //configure_i2c_callbacks


/**********************************************************************
 * @fn					- i2c_Write
 * @brief				- Write buffer to slave until success.
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len)
 {

	// Merge Device Register and data to TX
 	uint8_t merged_packet[len + 1];
 	merged_packet[0] = reg_addr;
 	
 	for(uint16_t i = 0; i < len; i++)
 	merged_packet[i + 1] = write_buffer[i];

	write_packet.address = i2c_addr;
	write_packet.data = merged_packet;
	write_packet.data_length = len + 1;
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;

	while (i2c_master_write_packet_wait(&i2c_master_instance, &write_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
		return -1;
			break;
		}
	}

	return 0;
 } //i2c_Write


/**********************************************************************
 * @fn					- i2c_slWrite
 * @brief				- Write buffer to slave until success, without register.
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_slWrite(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t len)
 {

	// Merge Device Register and data to TX
 	uint8_t merged_packet[len];
	//uint8_t merged_packet[len + 1];
 	//merged_packet[0] = reg_addr;
 	
 	for(uint16_t i = 0; i < len; i++)
 	//merged_packet[i + 1] = write_buffer[i];
	merged_packet[i] = write_buffer[i];

	write_packet.address = i2c_addr;
	write_packet.data = merged_packet;
	//write_packet.data_length = len + 1;
	write_packet.data_length = len;
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;

	while (i2c_master_write_packet_wait(&i2c_master_instance, &write_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
		return -1;
			break;
		}
	}

	return 0;
 } //i2c_Write

   /**********************************************************************
 * @fn					- i2c_Read
 * @brief				- Read from slave until success.
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};						
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len)
 {
	//Write to Address, Register
	read_packet.address = i2c_addr;
	read_packet.data = &reg_addr;
	read_packet.data_length = 1;
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;
	
	while (i2c_master_write_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	// Read from Address, register
	read_packet.data = read_buffer;
	read_packet.data_length = len;

	while (i2c_master_read_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK)
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	
	return 0;

 } // i2c_Read

    /**********************************************************************
 * @fn					- i2c_slRead
 * @brief				- Read from slave until success, without register
 *
 * @param[in]			- i2c_addr: Address of Slave device
 * @param[in]			- *read_buffer: buffer eg uint8_t buffer[I2C_DATA_LENGTTH] = {0xAA, 0xBB};						
 * @param[in]			- size: sizeof(buffer)
 *
 * @return				- 0
 *
 * @note				- called from main
 **********************************************************************/
int8_t i2c_slRead(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t len)
 {
	//Write to Address, Register
	read_packet.address = i2c_addr;
	//read_packet.data = &reg_addr;
	//read_packet.data = read_buffer;
	read_packet.data_length = 0;	
	read_packet.ten_bit_address = FALSE;
	read_packet.high_speed = FALSE;
	
	while (i2c_master_write_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK) 
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	// Read from Address, register
	read_packet.data = read_buffer;
	read_packet.data_length = len;

	while (i2c_master_read_packet_wait(&i2c_master_instance, &read_packet) != STATUS_OK)
	{
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == I2C_TIMEOUT) {
			return -1;
			break;
		}
	}

	return 0;

 }// i2c_slRead