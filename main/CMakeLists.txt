set(srcs 
    "e_paper/src/e_paper.c" 
    "e_paper/src/e_paper_interface.c"
    "file_io/src/file_io.c"
    "main.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." "./e_paper/include/" "./file_io/include/")

spiffs_create_partition_image(storage storage FLASH_IN_PROJECT)