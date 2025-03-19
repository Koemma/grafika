#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Color;

typedef struct Line
{
  int x;
  int y;
  Color color;
} Line;

int main(int argc, char *argv[])
{
  //eger pozicio
  SDL_Window *window = NULL;
  SDL_Event event;
  int quit = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL hiba: %s\n", SDL_GetError());
    return 1;
}
window = SDL_CreateWindow("eger esemeny pelda",
  SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED,
  640, 480,
  SDL_WINDOW_SHOWN);

if (!window) {
printf("nem sikerult letrehozni az ablakot: %s\n", SDL_GetError());
SDL_Quit();
return 1;
}

while (!quit) {
while (SDL_PollEvent(&event)) {
switch (event.type) {
case SDL_QUIT:
quit = 1;
break;

case SDL_MOUSEMOTION:

printf("eger pozicio: x=%d, y=%d\n", event.motion.x, event.motion.y);
break;
}
}

SDL_Delay(10);
}

SDL_DestroyWindow(window);
SDL_Quit();

  Color color = {255, 0, 0};
  Line myLine;
  myLine.x = 0;
  myLine.y = 10;
  myLine.color = color;

  printf("szakasz koordinatai: x=%d, y=%d, szin kod: {%d, %d, %d}\n", myLine.x, myLine.y, myLine.color.r, myLine.color.g, myLine.color.b);

  return 0;
}