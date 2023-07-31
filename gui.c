#include <stdbool.h>

#include <SFML/Graphics/RenderWindow.h>

#include "gui.h"

bool gui_init(gui_t *gui)
{
    sfVideoMode v_mode = { 1280, 720 };

    gui->window = sfRenderWindow_create(v_mode, "CFileTree", sfClose, NULL);
    gui->is_running = gui->window != NULL;
    return gui->is_running;
}

void gui_handle_events(gui_t *gui, sfEvent *eventp)
{
    if (eventp->type == sfEvtClosed) {
        gui->is_running = false;
        return;
    }
}

bool gui_run(gui_t *gui)
{
    sfBool success;
    sfEvent event;

    sfRenderWindow_clear(gui->window, sfWhite);
    while (gui->is_running) {
        sfRenderWindow_display(gui->window);
        success = sfRenderWindow_waitEvent(gui->window, &event);
        if (!success)
            gui->is_running = false;
        gui_handle_events(gui, &event);
    }
    return success;
}

void gui_finalize(gui_t *gui)
{
    gui->is_running = false;
    if (sfRenderWindow_isOpen(gui->window))
        sfRenderWindow_close(gui->window);
}
