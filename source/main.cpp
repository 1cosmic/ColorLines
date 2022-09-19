#include "headers/gui.hpp"
#include "headers/logic.hpp"
#include "headers/processor.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

using namespace std;

int main() {

  bool run = true;              // for main circle.
  SDL_Event event;              // user event.
  const Uint32 FPS = 1000 / 30; // FPS.
  Uint32 _FPS_Timer;            // for control of frame rate.

  // Main func. block.
  initGame();
  initField();

  if (showMain())
    cout << "Show window..." << endl;
  //==============================

  // Main circle.
  while (run) {

    // Processor user input // event.
    while (SDL_PollEvent(&event) != 0) {
      run = processor(event);

      if (!run)
        break;
    }

    // Frame Rate controls.
    if (SDL_GetTicks() - _FPS_Timer < FPS) {
      SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
    }
    _FPS_Timer = SDL_GetTicks();

    // Cycle animate.
    showMain();
    display_stars();
  }

  destroyGame();  // destroy SDL object.
  destroyLogic(); // destroy dynamic object (logic.cpp).

  return 0;
}
