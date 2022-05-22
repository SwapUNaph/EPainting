#include <stdio.h>
#include "e_paper/e_paper.h"
#include "file_io/file_io.h"

static const char *MAIN = "EPainting";

void app_main(void)
{
    // Initialize SPIFFS
    if(init_spiffs() != ESP_OK) {
        ESP_LOGE(MAIN, "Error initializing SPIFFS!");
        return;
    }

    // Initialize Epaper Display
    e_paper_handle_t e_paper_disp;
    e_paper_disp.height = 448;
    e_paper_disp.width = 600;
    ESP_LOGI(MAIN, "Initializing E paper");
    e_paper_init(&e_paper_disp);
    ESP_LOGI(MAIN, "E paper initialized");

    // Read image from SPIFFS
    image_handle_t image;
    image.height = e_paper_disp.height;
    image.width = e_paper_disp.width;
    esp_err_t ret = read_image_from("/spiffs/image.bin", &image);
    if(ret != ESP_OK) {
        ESP_LOGE(MAIN, "Failed to load image.");
        return;
    }

    // Display image
    ESP_LOGI(MAIN, "Drawing image ...");
    e_paper_draw(&e_paper_disp, &image);
    ESP_LOGI(MAIN, "Done drawing");

    while(1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}
