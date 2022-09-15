#include "headers/gui_drawing.hpp"
#include "headers/gui_loader.hpp"
#include "headers/mainStruts.h"

#include <SDL2/SDL.h>

#include <SDL2/SDL_render.h>
#include <exception>
#include <iostream>
#include <vector>

#define SCR_W 1280
#define SCR_H 720

using namespace std;

SDL_Window *window = NULL;       // Main window of the window window
SDL_Renderer *render = NULL;     // Renderer of the drawing.
SDL_Surface *mainSurface = NULL; // Surface contained by the window.

SDL_Rect Rect_backbround;  // rect of background.
SDL_Rect Rect_field;       // rect of field.
SDL_Rect Rect_cells[9][9]; // rect of cells (in grid).

extern int field[9][9]; // from logic.cpp.

// ============================================================
int center[2] = {1280 / 2, 720 / 2}; // create XY of center screen.

pair<int, int> centerObj(int w, int h) {
  // Return center of object.

  return {center[0] - w / 2, center[1] - w / 2};
}

pointField coordsStarUnderCursor(int coordX, int coordY) {

  // Return coords of start pos. star.

  int string, cell;
  pointField coordsStar;
  coordsStar.string = -1;

  if ((coordX >= Rect_field.x) && (coordX <= Rect_field.x + Rect_field.w) &&
      (coordY >= Rect_field.y) && (coordY <= Rect_field.y + Rect_field.h)) {

    string = (coordY - Rect_field.y) / 60;
    cell = (coordX - Rect_field.x) / 60;

    coordsStar.string = string;
    coordsStar.column = cell;
    coordsStar.color = field[string][cell];

//    cout << "String / cell: " << string << " / " << cell << endl;

  } else
        cout << "Mouse point not in field." << endl;

    return coordsStar;
}

void getXY(int coordX, int coordY) {


}

// ============================================================

bool initGame(void) {
  // Initialization chesks.

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize. Error: %s\n", SDL_GetError());
    exit(1);

  } else {

    // Create main window:
    SDL_CreateWindowAndRenderer(SCR_W, SCR_H, 0, &window, &render);

    if (window == NULL) {
      printf("Main window could not be created. Error: %s\n", SDL_GetError());

      exit(1);

    } else

      mainSurface = SDL_GetWindowSurface(window);
  }

  //====================
  // Initialize RECTS.
  //====================

  // Init background rect.
  Rect_backbround.x = 0;
  Rect_backbround.y = 0;
  Rect_backbround.w = 1280;
  Rect_backbround.h = 720;

  // Init field rect.
  Rect_field.x = centerObj(9 * 60, 9 * 60).first;
  Rect_field.y = centerObj(9 * 60, 9 * 60).second;
  Rect_field.w = 9 * 60;
  Rect_field.h = 9 * 60;

  // Generate all rects of cells for field.
  int column, cell;

  for (column = 0; column < 9; ++column) {
    for (cell = 0; cell < 9; ++cell) {

      Rect_cells[column][cell].x = 60 * cell + Rect_field.x;
      Rect_cells[column][cell].y = 60 * column + Rect_field.y;
      Rect_cells[column][cell].h = 60;
      Rect_cells[column][cell].w = 60;
    }
  }

  //====================
  // Initialization star images from system.
  //====================

  initTexture(render); // load & convert to texture.

  return true;
  //====================
}

void destroyGame(void) {
  // Destroy all objects & close window.

  if (cleanTexture())
    cout << "All texture was delete." << endl;
  else
    cout << "Texture don`t removed!" << endl;

  try {
    if (mainSurface)
      SDL_FreeSurface(mainSurface); // Destroy main (window) surface.
    if (render)
      SDL_DestroyRenderer(render); // Destroy renderer.
    if (window)
      SDL_DestroyWindow(window); // Destroy window.

    cout << "All surface & windows was closed." << endl;
  }

  catch (exception &e) {
    cout << "Coudn`t close window. Error: " << e.what() << endl;
  }
}

bool showMain(void) {
  // Set up default option of main screen & window. Show is its.

  // Clear & set main options.
  SDL_RenderClear(render); // clear render (nahui?..)
  SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);

  // Input backgroud texture.
  SDL_RenderCopy(render, get_bgd(), NULL, &Rect_backbround);

  // Draw grid.
  draw_grid(60); // draw grid.

  // Display all it.
  // SDL_RenderPresent(render);

  return true;
}

void display_stars() {
  // Display all changes from RAM (logic.cpp).

  int x, y; // column & cell of field.
  int color;

  // Run for all cells.
  for (y = 0; y < 9; ++y)
    for (x = 0; x < 9; ++x)
      if (field[y][x]) {

        color = field[y][x];
        SDL_RenderCopy(render, get_star(color), NULL, &Rect_cells[y][x]);
      }

  SDL_RenderPresent(render);
}
