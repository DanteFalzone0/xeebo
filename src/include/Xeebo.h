#ifndef XEEBO_H
#define XEEBO_H

#include <map>
#include "Game_Object.h"

struct SDL_Renderer;
struct SDL_Window;

namespace Xeebo {

typedef size_t Game_Object_Id;

class Game {
private:
  std::map<Game_Object_Id, Game_Object *> game_objects;
  SDL_Renderer *renderer;
  SDL_Window *window;

  /**
   * This is incremented by one every time a new game object is added.
   */
  Game_Object_Id highest_game_object_id = 0;

public:
  Game(const char *title, const int width_px, const int height_px);
  ~Game();

  void main_loop(void);

  /**
   * This method will assign a game object to an id and return the id.
  */
  Game_Object_Id add_game_object(Game_Object *object);

  void remove_game_object(Game_Object_Id id);
};

} // end namespace Xeebo

#endif // XEEBO_H
