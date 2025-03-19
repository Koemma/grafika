#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PALETTE_HEIGHT 50
#define COLOR_COUNT 5
#define MAX_RECT_COUNT 10

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
} ColoredRect;

SDL_Color palette[COLOR_COUNT] = {
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 255, 0, 255},
    {0,255, 255, 255}
};

int get_selected_color_index(int mouse_x, int mouse_y) {
    if (mouse_y >= WINDOW_HEIGHT - PALETTE_HEIGHT) {
        int box_width = WINDOW_WIDTH / COLOR_COUNT;
        return mouse_x / box_width;
    }
    return -1;
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("teglalaprajzolo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ColoredRect rects[MAX_RECT_COUNT];
    int rect_count = 0;
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
                        int mx = event.button.x;
                        int my = event.button.y;

                        int selected = get_selected_color_index(mx, my);
                        if (selected >= 0 && selected < COLOR_COUNT) {
                            current_color_index = selected;
                        } else {
                            if (!waiting_for_second_click) {
                                temp_x = mx;
                                temp_y = my;
                                waiting_for_second_click = true;
                            } else {
                                if (rect_count < MAX_RECT_COUNT) {
                                    int x1 = min(temp_x, mx);
                                    int y1 = min(temp_y, my);
                                    int w = abs(mx - temp_x);
                                    int h = abs(my - temp_y);
                                    rects[rect_count].rect.x = x1;
                                    rects[rect_count].rect.y = y1;
                                    rects[rect_count].rect.w = w;
                                    rects[rect_count].rect.h = h;
                                    rects[rect_count].color = palette[current_color_index];
                                    rect_count++;
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

        for (int i = 0; i < rect_count; i++) {
            SDL_SetRenderDrawColor(renderer,
                rects[i].color.r,
                rects[i].color.g,
                rects[i].color.b,
                rects[i].color.a);
            SDL_RenderFillRect(renderer, &rects[i].rect);
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
