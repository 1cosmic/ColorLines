// Processor of key press, event.

#include "headers/gui.hpp"
#include "headers/logic.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

using namespace std;

pointField lastStar{0, 0, 0};

bool processor(SDL_Event event) {
  // Processor event.

  int x, y;     // for mouse detection.
  pointField curStar; // current selected star.
  bool wayExists;



  switch (event.type) {

  // If game was close:
  case SDL_QUIT:
    return false;

  // case SDL_MOUSEMOTION:
  //   SDL_GetMouseState(&x, &y);

  //   cout << "Mouse motion. X/Y: " << x << " / " << y << endl;
  //   return true;

  // If mouse click:
  case SDL_MOUSEBUTTONDOWN:

    SDL_GetMouseState(&x, &y);
    curStar = coordsStarUnderCursor(x, y);

    // If star is celected:
    if (curStar.string >= 0) {

        // Set up first star:
        if (!lastStar.color)
            lastStar = curStar;

        // If curStar is second star, check of exists the way.
        else {

//          cout << "Target the second star. Color: " << curStar.color << endl;
            wayExists = wayIsExists(lastStar, curStar);
            cout << "Check free way... " << wayExists << endl;

            // If free way - swap stars into the place.
            if (wayExists) {

                // Move star into the field.
                clearStar(lastStar);
                moveStar(lastStar, curStar);
                swapStar(curStar);

                // Check free space in field.
                if (checkFreeSpace()) {
                    randomColors();  // create list random colors.
                    randomPutStar(); // put color from random color-list.
                } else {
                    cout << "Field is full." << endl;
                    return false;
                }
            }

            lastStar.color = 0;
            return true;

            /* TODO:
             * ДОДЕЛАТЬ! 1. Добавить анимацию движения звезды, если путь существует.
             * +++ 2. Добавить перемещение айдишников звёзд в field.
             */
        }

      cout << "Target fist star. Color: " << curStar.color << endl;
    }

    return true;

  // If key was pressed:
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    // Close game by key: SPACE.
    case SDLK_q:
      return false;

    // Display stars.
    case SDLK_SPACE:
      showMain(); // show main surf.
                  // showMain();       // BUG FIX: clear artefacts.

      // Check free space in field.
      if (checkFreeSpace()) {
        randomColors();  // create list random colors.
        randomPutStar(); // put color from random color-list.
//        display_stars(); // display all changes.
      } else {
        cout << "Field is full." << endl;
        return false;
      }

      cout << "Space was pressed." << endl;
    }

  default:
    return true;
  }
}
