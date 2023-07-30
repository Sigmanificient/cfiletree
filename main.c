#include <malloc.h>
#include <string.h>

#include <stdlib.h>
#include <unistd.h>

#include <linux/limits.h>

#include "cfiletree.h"
#include "debug.h"

static
void print_tree(char *path)
{
    char buf[1024];

    if (path == NULL) {
        path = malloc(PATH_MAX * sizeof(char));
        if (path == NULL)
            return;
        if (getcwd(path, PATH_MAX) == NULL)
            return;
    }
    filetree_traverse(path);
}

int main(int argc, char **argv)
{
    bool succeed;
    gui_t gui;

    DEBUG_CALL(print_tree, argv[1]);
    DEBUG_MSG(YELLOW "Running in debug mode" RESET);
    gui_init(&gui);
    if (!gui.is_running)
        return EXIT_FAILURE;
    succeed = gui_run(&gui);
    gui_finalize(&gui);
    return (succeed) ? EXIT_SUCCESS : EXIT_FAILURE;
}
