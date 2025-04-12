#include "app.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    App app;
    int width = 900, height = 600;

    init_app(&app, width, height);
    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}
