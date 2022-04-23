#ifndef _E_PAPER_INT_H_
#define _E_PAPER_INT_H_

#include "driver/spi_master.h"
#include "driver/gpio.h"

#define EP_SPI_HOST VSPI_HOST
#define CS_PIN      GPIO_NUM_5
#define MOSI_PIN    GPIO_NUM_23
#define MISO_PIN    GPIO_NUM_19
#define SCK_PIN     GPIO_NUM_18
#define RST_PIN     GPIO_NUM_2
#define DC_PIN      GPIO_NUM_15
#define BUSY_PIN    GPIO_NUM_4

#define SEND_DATA   1
#define SEND_CMD    0

void e_paper_gpio_initialize();

void e_paper_spi_initialize(spi_device_handle_t* e_paper_spi);

void e_paper_spi_pre_transfer_callback(spi_transaction_t *t);

void e_paper_int_transfer_data(spi_device_handle_t e_paper_spi, uint8_t* data, int size);


#endif // _E_PAPER_INT_H_