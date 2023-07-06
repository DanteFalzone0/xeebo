#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include "include/Xeebo.h"

// pass -DEBUG for debugging output
#ifdef EBUG
  #define Dbg_Msg(x) std::cout << "Debug message: " << x << std::endl
#else
  #warning Runtime debugging messages are disabled; pass `-DEBUG` to enable.
  #define Dbg_Msg(x)
#endif

int main(int argc, char *argv[]) {
  try {
    Dbg_Msg("Entering main");
    Xeebo::Game game("Xeebo Demo", 600, 600);
    Dbg_Msg("Created game window");
    auto spaceship_texture = new Xeebo::Texture(
      "C:\\Users\\clair\\xeebo\\src\\spaceship.bmp"
    );
    Dbg_Msg("Loaded spacehip texture; pointer value: " << spaceship_texture);
    auto spaceship = new Xeebo::Game_Object(spaceship_texture, { 100, 100 });
    Dbg_Msg("Created spaceship object; pointer value: " << spaceship);
    auto id = game.add_game_object(spaceship);
    Dbg_Msg("Spaceship added to objects with id " << id);
    Dbg_Msg("Entering Xeebo::Game::main_loop");
    game.main_loop();
    Dbg_Msg("Returned from Xeebo::Game::main_loop");
  } catch (std::runtime_error& error) {
    std::printf("An exception was raised. Details:\n%s\n", error.what());
  }
  return 0;
}
