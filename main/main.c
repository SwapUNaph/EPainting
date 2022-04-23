#include <stdio.h>
#include "e_paper/e_paper.h"

void app_main(void)
{
    e_paper_handle_t e_paper_disp;
    e_paper_disp.height = 448;
    e_paper_disp.width = 600;

    printf("Initializing E paper\n");
    e_paper_init(&e_paper_disp);
    printf("E paper initialized\n");

    printf("Clearing screen with BLUE\n");
    e_paper_clear(&e_paper_disp, COLOR_BLUE);
    printf("Done clearing\n");

}
