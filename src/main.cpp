#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include "include/Xeebo.h"
#include "include/Event.h"

int main(int argc, char *argv[]) {
  try {
    Xeebo::Game game("Xeebo Demo", 600, 600);
    auto spaceship_texture = new Xeebo::Texture(
      "C:\\Users\\clair\\xeebo\\src\\spaceship.bmp"
    );
    auto spaceship = new Xeebo::Game_Object(spaceship_texture, { 100, 100 });
    spaceship->on_event(Xeebo::Event::Frame_Refresh, [](Xeebo::Game_Object *self) {
      self->transform_angle(+1.0);
    });
    auto id = game.add_game_object(spaceship);
    game.main_loop();
  } catch (std::runtime_error& error) {
    std::printf("An exception was raised. Details:\n%s\n", error.what());
  }
  return 0;
}
