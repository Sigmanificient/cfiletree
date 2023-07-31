#ifndef GUI_H
    #define GUI_H

    #include <SFML/Graphics/Types.h>
    #include <SFML/Window/Event.h>

typedef struct {
    bool is_running;
    sfRenderWindow *window;
} gui_t;

bool gui_init(gui_t *gui);
bool gui_run(gui_t *gui);
void gui_handlle_event(gui_t *gui, sfEvent *eventp);
void gui_finalize(gui_t *gui);

#endif

