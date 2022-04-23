#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "e_paper/e_paper.h"


void e_paper_send_cmd(e_paper_handle_t* display, uint8_t command) {
    gpio_set_level(DC_PIN, SEND_CMD);
    e_paper_int_transfer_data(display->interface, &command, 1);
}

void e_paper_send_data(e_paper_handle_t* display, uint8_t data) {
    gpio_set_level(DC_PIN, SEND_DATA);
    e_paper_int_transfer_data(display->interface, &data, 1);
}

void e_paper_wait_busy(uint8_t wait_for_busy) {
    gpio_set_pull_mode(BUSY_PIN, wait_for_busy ? GPIO_PULLDOWN_ONLY : GPIO_PULLUP_ONLY);
    while(gpio_get_level(BUSY_PIN) != wait_for_busy) {
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

void e_paper_set_resolution(e_paper_handle_t* display) {
    e_paper_send_cmd(display, 0x61);
    e_paper_send_data(display, 0x02);
    e_paper_send_data(display, 0x58);
    e_paper_send_data(display, 0x01);
    e_paper_send_data(display, 0xC0);
}

void e_paper_init(e_paper_handle_t* display) {
    e_paper_gpio_initialize();
    e_paper_spi_initialize(&(display->interface));

    e_paper_reset();

    e_paper_wait_busy(BUSY_HIGH);

    e_paper_send_cmd(display, 0x00);
    e_paper_send_data(display, 0xEF);
    e_paper_send_data(display, 0x08);

    e_paper_send_cmd(display, 0x01);
    e_paper_send_data(display, 0x37);
    e_paper_send_data(display, 0x00);
    e_paper_send_data(display, 0x23);
    e_paper_send_data(display, 0x23);

    e_paper_send_cmd(display, 0x03);
    e_paper_send_data(display, 0x00);

    e_paper_send_cmd(display, 0x06);
    e_paper_send_data(display, 0xC7);
    e_paper_send_data(display, 0xC7);
    e_paper_send_data(display, 0x1D);

    e_paper_send_cmd(display, 0x30);
    e_paper_send_data(display, 0x3C);
    
    e_paper_send_cmd(display, 0x41);
    e_paper_send_data(display, 0x00);
    
    e_paper_send_cmd(display, 0x50);
    e_paper_send_data(display, 0x37);
    
    e_paper_send_cmd(display, 0x60);
    e_paper_send_data(display, 0x22);
    
    e_paper_set_resolution(display);
    
    e_paper_send_cmd(display, 0xE3);
    e_paper_send_data(display, 0xAA);
	
    vTaskDelay(100 / portTICK_RATE_MS);
    
    e_paper_send_cmd(display, 0x50);
    e_paper_send_data(display, 0x37);
}

void e_paper_reset() {
    gpio_set_level(RST_PIN, 0);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(RST_PIN, 1);
    vTaskDelay(100 / portTICK_RATE_MS);
}

void e_paper_clear(e_paper_handle_t* display, uint8_t color) {
    e_paper_set_resolution(display);

    e_paper_send_cmd(display, 0x10);
    for(int i=0; i<display->width/2; i++) {
        for(int j=0; j<display->height; j++) {
            e_paper_send_data(display, (color<<4)|color);
		}
	}

    e_paper_send_cmd(display, 0x04);
    e_paper_wait_busy(BUSY_HIGH);
    e_paper_send_cmd(display, 0x12);
    e_paper_wait_busy(BUSY_HIGH);
    e_paper_send_cmd(display, 0x02); 
    e_paper_wait_busy(BUSY_LOW);
    vTaskDelay(500 / portTICK_RATE_MS);
}