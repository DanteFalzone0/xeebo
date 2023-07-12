#include "include/Xeebo.h"
#include "include/Event.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

namespace Xeebo {

Game::Game(const char *title, const int width_px, const int height_px) {
  SDL_Init(SDL_INIT_VIDEO);
  this->window = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    600, 600, 0
  );
  if (this->window == nullptr) {
    auto error_message =
      std::string("Error in `Xeebo::Game` constructor: ") + SDL_GetError();
    throw std::runtime_error(error_message);
  }
  this->renderer = SDL_CreateRenderer(this->window, 0, 0);
  if (this->renderer == nullptr) {
    auto error_message =
      std::string("Error in `Xeebo::Game` constructor: ") + SDL_GetError();
    throw std::runtime_error(error_message);
  }
}

Game::~Game() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Game::main_loop(void) {
  SDL_Event event;

  const int fps = 60;
  const int frame_delay = 1000 / fps;
  Uint32 frame_start;
  int frame_time;

  bool playing = true;
  while (playing) {
    frame_start = SDL_GetTicks();

    // handle events and update state by firing object event handlers
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      playing = false;
    } else switch (event.type) {
      // TODO implement more event types
      default:
        for (const auto game_object : this->game_objects) {
          game_object.second->handle_event(Event::Frame_Refresh);
        }
    }

    // render game objects
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
    for (const auto game_object : this->game_objects) {
      game_object.second->render_self(this->renderer);
    }
    SDL_RenderPresent(this->renderer);

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time) {
      SDL_Delay(frame_delay - frame_time);
    }
  }
}

Game_Object_Id Game::add_game_object(Game_Object *object) {
  const auto game_object_id = this->highest_game_object_id;
  this->game_objects[game_object_id] = object;
  this->highest_game_object_id++;
  return game_object_id;
}

void Game::remove_game_object(Game_Object_Id id) {
  auto pointer = this->game_objects[id];
  this->game_objects.erase(id);
  delete pointer;
}

} // namespace Xeebo
