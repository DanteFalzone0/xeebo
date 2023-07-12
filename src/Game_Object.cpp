#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include "include/Game_Object.h"
#include "include/Event.h"

namespace Xeebo {

Action::Action(void) { }

Action::Action(std::function<void(Game_Object *)> execute): execute(execute) { }

Texture::Texture(void) { }

Texture::Texture(const char *file_path) {
  this->sdl_surface = SDL_LoadBMP(file_path);
  if (this->sdl_surface == nullptr) {
    auto error_message =
      std::string("Error in `Texture::Texture`: ") + SDL_GetError();
    throw std::runtime_error(error_message);
  }
}

Texture::~Texture() {
  if (this->sdl_surface != nullptr) {
    SDL_FreeSurface(this->sdl_surface);
  }
}

Game_Object::Game_Object(void): texture{nullptr} { }

Game_Object::Game_Object(
  Texture *texture,
  SDL_Point initial_position
) : texture{texture}
  , position{initial_position}
{
  this->event_actions = std::unordered_map<Event, Action>();
}

Game_Object::~Game_Object() {
  delete this->texture;
}

void Game_Object::on_event(
  Event event,
  std::function<void(Game_Object *)> action
) {
  this->event_actions[event] = Action(action);
}

void Game_Object::handle_event(Event event) {
  if (this->event_actions.count(event)) {
    this->event_actions[event].execute(this);
  }
}

void Xeebo::Game_Object::render_self(SDL_Renderer *renderer) const {
  if (renderer == nullptr) {
    throw std::runtime_error("Error in `Game_Object::render_self`: renderer is null");
  }

  //if (this->texture == nullptr) return;

  // Set the destination rectangle for rendering
  SDL_Rect dest_rect = {
    this->position.x, this->position.y,
    this->texture->sdl_surface->w, this->texture->sdl_surface->h
  };
  
  // Set the rotation center
  SDL_Point center = {
    this->texture->sdl_surface->w / 2, this->texture->sdl_surface->h / 2
  };

  auto sdl_texture = SDL_CreateTextureFromSurface(
    renderer, this->texture->sdl_surface
  );

  // Render the texture on the renderer
  SDL_RenderCopyEx(
    renderer,
    sdl_texture, nullptr, &dest_rect,
    this->texture->angle, &center, SDL_FLIP_NONE
  );
  
  // Destroy the temporary texture
  SDL_DestroyTexture(sdl_texture);
}

void Game_Object::set_position(SDL_Point new_position) {
  this->position = new_position;
}

void Game_Object::transform_position(int x_axis_amount, int y_axis_amount) {
  this->position.x += x_axis_amount;
  this->position.y += y_axis_amount;
}

void Game_Object::transform_angle(double amount) {
  this->texture->angle += amount;
  // Clamp to within 360 degrees
  while (this->texture->angle > 360.0) {
    this->texture->angle -= 360.0;
  }
  while (this->texture->angle < 0.0) {
    this->texture->angle += 360.0;
  }
}

} // namespace Xeebo
