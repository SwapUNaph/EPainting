#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "e_paper/e_paper.h"

esp_err_t init_spiffs(void);

esp_err_t read_image_from(const char* filepath, image_handle_t* image);


#endif // _FILE_IO_H_