#include <stdio.h>
#include <string.h>
#include "e_paper/e_paper_interface.h"

void e_paper_gpio_initialize() {
    gpio_reset_pin(CS_PIN);
    gpio_set_direction(CS_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(DC_PIN);
    gpio_set_direction(DC_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(RST_PIN);
    gpio_set_direction(RST_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUSY_PIN);
    gpio_set_direction(BUSY_PIN, GPIO_MODE_INPUT);
}

void e_paper_spi_initialize(spi_device_handle_t* e_paper_spi) {
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=MISO_PIN,
        .mosi_io_num=MOSI_PIN,
        .sclk_io_num=SCK_PIN,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=64
    };

    spi_device_interface_config_t devcfg={
        .clock_speed_hz=2*1000*1000,       //Clock out at 2 MHz
        .mode=0,                            //SPI mode 0
        .spics_io_num=CS_PIN,               //CS pin
        .queue_size=7,                      //We want to be able to queue 7 transactions at a time
    };

    //Initialize the SPI bus
    ret=spi_bus_initialize(EP_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    //Attach the e_paper to the SPI bus
    ret=spi_bus_add_device(EP_SPI_HOST, &devcfg, e_paper_spi);
    ESP_ERROR_CHECK(ret);
}


void e_paper_int_transfer_data(spi_device_handle_t e_paper_spi, uint8_t* data, int size) {
    esp_err_t ret;
    spi_transaction_t t;
    if (size==0) return;             //no need to send anything
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=size*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    ret=spi_device_polling_transmit(e_paper_spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}