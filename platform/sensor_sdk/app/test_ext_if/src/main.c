#include <stdint.h>
#include "ervp_printf.h"
#include "ervp_external_peri_group_api.h"
#include "ervp_mmio_util.h"
#include "ervp_core_id.h"
#include "platform_info.h"
#include "frvp_spi.h"
#include "orvp_i2c.h"
#include "frvp_spi_flash.h"

#define TEST_SPI 1
#define TEST_I2C 1
#define TEST_FLASH 0 // define SIMULATE_SPI_FLASH as True into sim_define in xml

#define SPI_FREQ (8000000)

#define I2C_MODULE_BASEADDR (0x43)
#define I2C_FREQ (100000)

#define NUM_DATA (8)
#define ADDR (0x700000)

static SpiConfig spiconfig = {SPI_DIVSOR(SPI_FREQ), SPI_SCKMODE_0, 1, SPI_CSMODE_OFF, (SPI_FMT_PROTO(SPI_PROTO_S) | SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) | SPI_FMT_LEN(8)), 1};

static void config_spi(int port_id)
{
	spiconfig.select = (1 << port_id);
	spi_configure(&spiconfig);
}

static void test_spi(int port_id)
{
	uint8_t wdata[] = {0x12, 0x34, 0x56, 0x78, 0x98, 0x76, 0x54, 0x32};
	uint8_t rdata[sizeof(wdata)];
	int equal;

	config_spi(port_id);
	spi_start();
	spi_write(sizeof(wdata), wdata);
	spi_end();

	spi_start();
	spi_read(sizeof(wdata), rdata);
	spi_end();

	for (int i = 0; i < sizeof(wdata); i++)
	{
		equal = (wdata[i] == rdata[i]);
		if (equal == 0)
			break;
	}
	if (equal)
		printf("\nSPI %d is Ok!", port_id);
	else
		printf("\nSPI %d is NOT Ok!", port_id);
}

static void config_i2c(int port_id)
{
	configure_i2c(port_id, I2C_FREQ, I2C_ENABLE, I2C_INTERRUPT_DISABLE);
}

static void test_i2c(int port_id)
{
	uint8_t wdata = 0x89;
	uint8_t rdata;

	config_i2c(port_id);
	write_i2c_r1d1(port_id, I2C_MODULE_BASEADDR + port_id - I2C_INDEX_FOR_READYMADE, 0, wdata);
	rdata = read_i2c_r1d1(port_id, I2C_MODULE_BASEADDR + port_id - I2C_INDEX_FOR_READYMADE, 0);
	if (wdata == rdata)
		printf("\nI2C %d is Ok!\n", port_id);
	else
		printf("\nI2C %d is Not Ok!\n", port_id);
}

void test_flash()
{
	uint8_t wdata[NUM_DATA];
	uint8_t rdata[NUM_DATA];
	int equal;

	configure_spi_flash();

	erase_sector(ADDR);
	for (int i = 0; i < NUM_DATA; i++)
		wdata[i] = (NUM_DATA - i - 1) & 0xff;
	write_flash_wo_erase(ADDR, NUM_DATA, wdata);
	read_flash(ADDR, NUM_DATA, rdata);
	for (int i = 0; i < NUM_DATA; i++)
	{
		equal = (wdata[i] == rdata[i]);
		if (equal == 0)
			break;
	}
	if (equal)
		printf("\nFlash is Ok!\n");
	else
		printf("\nFlash is NOT Ok\n");
}

int main()
{
	if (EXCLUSIVE_ID == 0)
	{
		if (TEST_SPI == 1)
		{
			for (int i = 0; i < NUM_SPI_READYMADE; i++)
				test_spi(SPI_INDEX_FOR_READYMADE + i);
		}
		if (TEST_I2C == 1)
		{
			for (int i = 0; i < NUM_I2C_READYMADE; i++)
				test_i2c(I2C_INDEX_FOR_READYMADE + i);
		}
		if (TEST_FLASH == 1)
			test_flash();
	}
	return 0;
}
