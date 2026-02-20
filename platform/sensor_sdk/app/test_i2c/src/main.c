#include "platform_info.h"
#include "ervp_printf.h"
#include "orvp_i2c.h"
#include "orvp_i2c_driver.h"
#include <stdint.h>

#define I2C_INDEX   (I2C_INDEX_FOR_READYMADE)
#define I2C_FREQ    (500)

#define MODULE_ADDR         (0x40)
#define NUM_BYTES_OF_DATA   (8)

uint16_t reg_addr_16 = 0x1234;
uint8_t reg_addr_8 = 0x12;
uint8_t data[NUM_BYTES_OF_DATA] = {0};

int main() {
  int i;
	printf("Hello World!\n");

  configure_i2c(I2C_INDEX, I2C_FREQ, I2C_ENABLE, I2C_INTERRUPT_DISABLE);

  /* tx data without reg address */
  start_i2c_transmisstion(I2C_INDEX, MODULE_ADDR);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      write_a_byte_on_i2c(I2C_INDEX, data[i]);
    else
      finish_writing_a_byte_on_i2c(I2C_INDEX, data[i]);
  }

  /* tx data with 1 byte reg address */
  start_i2c_transmisstion(I2C_INDEX, MODULE_ADDR);

  write_a_byte_on_i2c(I2C_INDEX, reg_addr_8);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      write_a_byte_on_i2c(I2C_INDEX, data[i]);
    else
      finish_writing_a_byte_on_i2c(I2C_INDEX, data[i]);
  }

  /* tx data with 2 byte reg address */
  start_i2c_transmisstion(I2C_INDEX, MODULE_ADDR);

  write_a_byte_on_i2c(I2C_INDEX, reg_addr_16>>8);
  write_a_byte_on_i2c(I2C_INDEX, reg_addr_16&0xFF);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      write_a_byte_on_i2c(I2C_INDEX, data[i]);
    else
      finish_writing_a_byte_on_i2c(I2C_INDEX, data[i]);
  }

  /* rx data without reg address */
  start_i2c_reading(I2C_INDEX, MODULE_ADDR);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      data[i] = read_a_byte_on_i2c(I2C_INDEX);
    else
      data[i] = finish_reading_a_byte_on_i2c(I2C_INDEX);
  }

  /* rx data with 1 byte reg address */
  start_i2c_transmisstion(I2C_INDEX, MODULE_ADDR);

  write_a_byte_on_i2c(I2C_INDEX, reg_addr_8);

  start_i2c_reading(I2C_INDEX, MODULE_ADDR);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      data[i] = read_a_byte_on_i2c(I2C_INDEX);
    else
      data[i] = finish_reading_a_byte_on_i2c(I2C_INDEX);
  }


  /* rx data with 2 byte reg address */
  start_i2c_transmisstion(I2C_INDEX, MODULE_ADDR);

  write_a_byte_on_i2c(I2C_INDEX, reg_addr_16>>8);
  write_a_byte_on_i2c(I2C_INDEX, reg_addr_16&0xFF);

  start_i2c_reading(I2C_INDEX, MODULE_ADDR);

  for(i=0; i<NUM_BYTES_OF_DATA; i++) {
    if(i!=(NUM_BYTES_OF_DATA-1))
      data[i] = read_a_byte_on_i2c(I2C_INDEX);
    else
      data[i] = finish_reading_a_byte_on_i2c(I2C_INDEX);
  }

	return 0;
}
