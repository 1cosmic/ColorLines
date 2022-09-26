#include "headers/gui.hpp"
#include "headers/logic.hpp"
#include "headers/processor.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

using namespace std;

int setInputLevel() {
    int UI = -1;

    cout << "ColorLines Alfa Version." << endl;
    cout << "Created by Michael Kolobakhin, 26 September of 2022." << endl;
    SDL_Delay(2000);

    while (UI > 2 || UI < 0) {
        cout << endl << "Please, select Hard Level, who you like." << endl;
        cout << "Input ONLY number of level!" << endl << endl;
        cout << "0 - Easy (3 Star)." << endl;
        cout << "1 - Middle (5 Star)." << endl;
        cout << "2 - It`s so Hard! (7 Star)." << endl;

        cin >> UI;
    }

    switch (UI) {
        case 0:
            cout << "Setting Easy mode." << endl;
            return 3;
        case 1:
            cout << "Setting Middle mode." << endl;
            return 5;
        case 2:
            cout << "Setting Hard mode." << endl;
            return 7;
    }

    cout << "Okay. You don`t understand of me. Setting Middle mode." << endl;
    return 5;
}

int main() {

  bool run = true;              // for main circle.
  SDL_Event event;              // user event.
  const Uint32 FPS = 1000 / 30; // FPS.
  Uint32 _FPS_Timer;            // for control of frame rate.

  bool addMove = true;
  bool isCleaned;
  int score = 0;
  int hardLevel = setInputLevel();

  // Main func. block.
  initGame();
  initField();

  if (showMain()) {
      cout << "Show window..." << endl;
  }
  //==============================

    if (checkFreeSpace()) {
        randomColors();  // create list random colors.
        randomPutStar(); // put color from random color-list.
    }

  // Main circle.
  while (run) {

      isMove = false;

      if (addMove)

          // Processor user input // event.
          while (SDL_PollEvent(&event) != 0) {
              run = processor(event);

              if (!run)
                  break;
          }

      isCleaned = clearMultiLine(hardLevel, &score);

      if (isMove && isCleaned) {
          addMove = true;
          cout << "New score: " << score << endl;
      }

      else if (isMove && !isCleaned) {
          addMove = true;
          isMove = false;

          // Check free space in field.
          if (checkFreeSpace()) {
              randomColors();  // create list random colors.
              randomPutStar(); // put color from random color-list.


          } else {
              cout << "Field is full." << endl;
              break;
          }
      }


      // Cycle animate.
      showMain();
      display_stars();

      // Frame Rate controls.
      if (SDL_GetTicks() - _FPS_Timer < FPS) {
          SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
      }
      _FPS_Timer = SDL_GetTicks();




    /* TODO:
     * ДОДЕЛАТЬ ВСЁ ЗА ПОНЕДЕЛЬНИК 26!
     *
     * +++ 1. Доделать возможность пропуска генерации след. 3 звёзд, если игрок выбил мультизвёзды.
     * +++ 2. Автоматизировать счёт, его вывод в консоль.
     * 3. Прокачать алгоритм очистки поля от звёзд, добавив поиск по диагонали.
     * 4. Добавить отображение текущего счёта и следующих 3х звёзд.
     * 5. Кнопка "Завершить игру", а также вызов этой же функции, если поле заполнено.
     * */

  }

  cout << endl << "===== YOU`R SCORE: " << score << " =====" << endl << endl;

  destroyGame();  // destroy SDL object.
  destroyLogic(); // destroy dynamic object (logic.cpp).

  return 0;
}
