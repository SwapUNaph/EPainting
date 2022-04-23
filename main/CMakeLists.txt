set(srcs 
    "e_paper/src/e_paper.c" 
    "e_paper/src/e_paper_interface.c"
    "main.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." "./e_paper/include/")

