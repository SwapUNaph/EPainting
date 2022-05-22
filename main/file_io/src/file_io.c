#include "file_io/file_io.h"

static const char* FILE_IO = "File_IO";

esp_err_t init_spiffs(void) {
    ESP_LOGI(FILE_IO, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(FILE_IO, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(FILE_IO, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(FILE_IO, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ret;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(FILE_IO, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(FILE_IO, "Partition size: total: %d, used: %d", total, used);
    }

    return ret;
}

esp_err_t read_image_from(const char* filepath, image_handle_t* image) {
    // Check if file exists before reading
    struct stat st;
    if (stat(filepath, &st)) {
        ESP_LOGE(FILE_IO, "File doesn't exists: %s", filepath);
        return ESP_FAIL;
    }

    // Open and read the image file
    FILE* f = fopen(filepath, "r");
    if (f == NULL) {
        ESP_LOGE(FILE_IO, "Failed to open file for reading: %s", filepath);
        return ESP_FAIL;
    }

    // Read image data from file
    image->data = malloc(st.st_size);
    size_t res = fread(image->data, st.st_size, 1, f);
    fclose(f);
   
    if(res != 1) {
        ESP_LOGE(FILE_IO, "Read error: %u", res);
        return ESP_FAIL;
    } 

    return ESP_OK;
}