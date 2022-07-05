// Processor of key press, event.

#include "headers/gui.hpp"
#include "headers/logic.hpp"
#include <SDL2/SDL.h>

bool processor(SDL_Event event) {
  // Processor event.

  switch (event.type) {

  // If game was close:
  case SDL_QUIT:
    return false;

  // If key was pressed:
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    // Close game by key: SPACE.
    case SDLK_q:
      return false;

    // Display stars.
    case SDLK_SPACE:
      /*
        Доделать:
        1. Адекватное отображение сетки после анимации.
        2. Вылеты после 3х циклов.
        3. Артефакты после 1го цикла
        4. Улыбнуться!)
      */
      showMain();       // show main surf.
      checkFreeSpace(); // check free space in field.
      randomColors();   // create list random colors.
      randomPutStar();  // put color from random color-list.
      display_stars();  // display all changes.
    }

  default:
    return true;
  }
}
