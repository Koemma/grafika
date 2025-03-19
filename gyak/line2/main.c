#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_LINE_COUNT 100
#define PALETTE_HEIGHT 50
#define COLOR_COUNT 5

typedef struct {
    int x1, y1;
    int x2, y2;
    SDL_Color color;
} Line;

SDL_Color palette[COLOR_COUNT] = {
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 255, 0, 255},
    {0, 255, 255, 255}
};

int get_selected_color_index(int mouse_x, int mouse_y) {
    if (mouse_y >= WINDOW_HEIGHT - PALETTE_HEIGHT) {
        int box_width = WINDOW_WIDTH / COLOR_COUNT;
        return mouse_x / box_width;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL init hiba: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("szakaszrajzolo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    bool waiting_for_second_click = false;
    int temp_x, temp_y;

    int current_color_index = 0;

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int cx = event.button.x;
                        int cy = event.button.y;

                        int selected = get_selected_color_index(cx, cy);
                        if (selected >= 0 && selected < COLOR_COUNT) {
                            current_color_index = selected;
                        } else {
                            if (!waiting_for_second_click) {
                                temp_x = cx;
                                temp_y = cy;
                                waiting_for_second_click = true;
                            } else {
                                if (line_count < MAX_LINE_COUNT) {
                                    lines[line_count].x1 = temp_x;
                                    lines[line_count].y1 = temp_y;
                                    lines[line_count].x2 = cx;
                                    lines[line_count].y2 = cy;
                                    lines[line_count].color = palette[current_color_index];
                                    line_count++;
                                }
                                waiting_for_second_click = false;
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < line_count; i++) {
            SDL_SetRenderDrawColor(renderer,
                lines[i].color.r,
                lines[i].color.g,
                lines[i].color.b,
                lines[i].color.a);
            SDL_RenderDrawLine(renderer,
                lines[i].x1, lines[i].y1,
                lines[i].x2, lines[i].y2);
        }

        int box_width = WINDOW_WIDTH / COLOR_COUNT;
        for (int i = 0; i < COLOR_COUNT; i++) {
            SDL_Rect rect = {i * box_width, WINDOW_HEIGHT - PALETTE_HEIGHT, box_width, PALETTE_HEIGHT};
            SDL_SetRenderDrawColor(renderer,
                palette[i].r,
                palette[i].g,
                palette[i].b,
                palette[i].a);
            SDL_RenderFillRect(renderer, &rect);

            if (i == current_color_index) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
