#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "circle2.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("korok kezelese", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circles[MAX_CIRCLE_COUNT];
    int circle_count = 0;
    int dragging_index = -1;
    int mouse_x, mouse_y;
    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;

                    dragging_index = -1;
                    for (int i = 0; i < circle_count; ++i) {
                        if (is_point_in_circle(mouse_x, mouse_y, &circles[i])) {
                            dragging_index = i;
                            circles[i].is_dragged = true;
                            break;
                        }
                    }

                    // Ha nem körre kattintottunk, új kör létrehozása
                    if (dragging_index == -1 && circle_count < MAX_CIRCLE_COUNT) {
                        Color new_color = {rand()%256, rand()%256, rand()%256};
                        set_circle_data(&circles[circle_count], mouse_x, mouse_y, 30, new_color);
                        circle_count++;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (dragging_index != -1) {
                        circles[dragging_index].is_dragged = false;
                        dragging_index = -1;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    if (dragging_index != -1 && circles[dragging_index].is_dragged) {
                        circles[dragging_index].x = mouse_x;
                        circles[dragging_index].y = mouse_y;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < circle_count; ++i) {
            draw_circle(renderer, &circles[i]);
            if (is_point_in_circle(mouse_x, mouse_y, &circles[i])) {
                draw_cross(renderer, &circles[i]);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
