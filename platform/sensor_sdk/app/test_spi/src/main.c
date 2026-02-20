#include "platform_info.h"
#include "ervp_printf.h"
#include "frvp_spi.h"

#define SPI_FREQ       (300000)
#define SPI_MODE       (SPI_SCKMODE_0)
#define PORT_ID        (SPI_INDEX_FOR_READYMADE)

#define NUM_BYTES_OF_DATA    (8)

static const SpiConfig spi_config = {SPI_DIVSOR(SPI_FREQ), 
  SPI_MODE, 
  (1<<PORT_ID), 
  SPI_CSMODE_OFF, 
  (SPI_FMT_PROTO(SPI_PROTO_S) | SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) | SPI_FMT_LEN(8)), 
  1};

unsigned char rx_data[NUM_BYTES_OF_DATA];
unsigned char tx_data[NUM_BYTES_OF_DATA]={1, 2, 3, 4, 5, 6, 7, 8};

int main() {
	printf("Test SPI!\n");
  spi_configure(&spi_config);

  /* read */
  spi_start();  // CS low
  spi_read(NUM_BYTES_OF_DATA, rx_data);
  spi_end(); // CS high

  /* write */
  spi_start();  // CS low
  spi_write(NUM_BYTES_OF_DATA, tx_data);
  spi_end(); // CS high

  /* write after read */
  spi_start();  // CS low
  spi_read(NUM_BYTES_OF_DATA, rx_data);
  spi_write(NUM_BYTES_OF_DATA, rx_data);
  spi_end(); // CS high

  /* read after write */
  spi_start();  // CS low
  spi_write(NUM_BYTES_OF_DATA, tx_data);
  spi_read(NUM_BYTES_OF_DATA, rx_data);
  spi_end(); // CS high

  /* write and read */
  spi_start();  // CS low
  spi_read_and_write(NUM_BYTES_OF_DATA, tx_data, rx_data);
  spi_end(); // CS high

	return 0;
}
