#ifndef _E_PAPER_H_
#define _E_PAPER_H_

#include "e_paper/e_paper_interface.h"

// Busy wait 
#define BUSY_HIGH   1
#define BUSY_LOW    0

// Color codes
#define COLOR_BLACK     0x0
#define COLOR_WHITE     0x1
#define COLOR_GREEN     0x2
#define COLOR_BLUE      0x3
#define COLOR_RED       0x4
#define COLOR_YELLOW    0x5
#define COLOR_ORANGE    0x6
#define COLOR_CLEAR     0x7


typedef struct {
    spi_device_handle_t interface;
    int height;
    int width;
} e_paper_handle_t;

typedef struct {
    uint8_t* data;
    int height;
    int width;
} image_handle_t;


// Helper functions

void e_paper_send_cmd(e_paper_handle_t* display, uint8_t command);

void e_paper_send_data(e_paper_handle_t* display, uint8_t data);

void e_paper_wait_busy(uint8_t wait_for_busy);



// Main utility functions

void e_paper_init(e_paper_handle_t* display);

void e_paper_draw(e_paper_handle_t* display, const image_handle_t* image);

void e_paper_draw_at(e_paper_handle_t* display, const image_handle_t* image, int x, int y);

void e_paper_set_resolution(e_paper_handle_t* display);

void e_paper_clear(e_paper_handle_t* display, uint8_t color);

void e_paper_reset();

void e_paper_sleep(e_paper_handle_t* display);


#endif // _E_PAPER_H_