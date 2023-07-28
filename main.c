#include <stdlib.h>
#include "cfiletree.h"

int main(void)
{
    bool succeed;
    gui_t gui;

    gui_init(&gui);
    if (!gui.is_running)
        return EXIT_FAILURE;
    succeed = gui_run(&gui);
    gui_finalize(&gui);
    return (succeed) ? EXIT_SUCCESS : EXIT_FAILURE;
}
