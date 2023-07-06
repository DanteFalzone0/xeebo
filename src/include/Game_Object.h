#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <functional>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "Event.h"

namespace Xeebo {

class Game_Object;
struct Action {
  std::function<void(Game_Object *)> execute = [](Game_Object *) { return; };
  Action(void);
  Action(std::function<void(Game_Object *)> execute);
};

/**
 * Wrapper class for SDL_Surface. Not hardware-accelerated. Won't be hardware-
 * accelerated unless this proves to be insufficient and hardware-acceleration
 * fixes it. 
 */
struct Texture {
  /**
   * Xeebo::Texture::sdl_surface is an owning pointer freed in Xeebo::Texture::~Texture.
   */
  SDL_Surface *sdl_surface = nullptr;
  double angle = 0.0;
  Texture(void);
  Texture(const char *file_path);
  ~Texture();
};

class Game_Object {
private:
  SDL_Point position;
  Texture *texture;
  /**
   * This will map events to actions. In the `Xeebo::Action` struct, a default
   * value for the `execute` method is provided that does nothing, so that any
   * events which this Game_Object isn't listening for will effectively be
   * ignored.
   */
  std::unordered_map<Event, Action> event_actions;
public:
  Game_Object(void);
  /**
   * The constructor takes ownership of the texture pointer. It is freed in
   * the destructor. 
   */
  Game_Object(Texture *texture, SDL_Point initial_position);
  ~Game_Object();
  void on_event(Event event, std::function<void(Game_Object *)> action);
  void render_self(SDL_Renderer *renderer) const;
  void set_position(SDL_Point new_position);
  void transform_position(int x_axis_amount, int y_axis_amount);
  //void transform_angle(int amount);
};

} // namespace Xeebo

#endif // GAME_OBJECT_H
