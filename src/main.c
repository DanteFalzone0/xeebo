#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

struct xeebo_point {
  unsigned int x, y;
};

enum xeebo_direction {
  up, down, left, right
};

void xeebo_example_line(
  SDL_Window *window,
  SDL_Renderer *renderer,
  struct xeebo_point *point_a,
  struct xeebo_point *point_b,
  enum xeebo_direction *dir
) {
  switch (*dir) {
    case up:
      if (point_a->y == 100) {
        *dir = left;
      } else {
        point_a->y--;
        point_b->y++;
      }
    break;
    case down:
      if (point_a->y == 500) {
        *dir = right;
      } else {
        point_a->y++;
        point_b->y--;
      }
    break;
    case left:
      if (point_a->x == 100) {
        *dir = down;
      } else {
        point_a->x--;
        point_b->x++;
      }
    break;
    case right:
      if (point_a->x == 500) {
        *dir = up;
      } else {
        point_a->x++;
        point_b->x--;
      }
    break;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, point_a->x, point_a->y, point_b->x, point_b->y);
  SDL_RenderPresent(renderer);
}

void xeebo_main_loop(SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Event event;

  const int fps = 60;
  const int frame_delay = 1000 / fps;
  Uint32 frame_start;
  int frame_time;

  enum xeebo_direction dir = left;
  struct xeebo_point point_a = { 500, 100 };
  struct xeebo_point point_b = { 100, 500 };

  bool playing = true;
  while (playing) {
    // Stores the number of ticks at the start of the loop
    frame_start = SDL_GetTicks();

    xeebo_example_line(window, renderer, &point_a, &point_b, &dir);

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      playing = false;
    }

    // This measures how long this iteration of the loop took
    frame_time = SDL_GetTicks() - frame_start;

    // This keeps us from displaying more frames than 60/Second
    if (frame_delay > frame_time) {
      SDL_Delay(frame_delay - frame_time);
    }
  }
}

int main(int argc, char *argv[]) {
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(
    "Xeebo",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    600, 600, 0
  );
  if (window == NULL) {
    printf("Error in `main()`: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, 0, 0);
  if (renderer == NULL) {
    printf("Error in `main()`: %s\n", SDL_GetError());
    return 1;
  }

  xeebo_main_loop(window, renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
