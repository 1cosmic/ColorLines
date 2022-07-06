#include <SDL2/SDL.h>

using namespace std;
extern SDL_Renderer *render;

pair<int, int> centerObj(int w, int h);

void draw_grid(int indent) {
  // Draw grid (for separate of stars).

  static bool animated = false;

  const pair<int, int> start_pos = centerObj(indent * 9, indent * 9);

  int x = start_pos.first;
  int y = start_pos.second;

  int endLine = start_pos.first + (9 * indent);
  int line; // index of line.

  if (!animated) {
    animated = true;

    int speed = (endLine - start_pos.first) / 30;
    int draw = start_pos.second; // cursor for drawing.


    for (draw = 0; draw < endLine - start_pos.first; draw += speed) {
      for (line = 1; line < 9; ++line) {

        // Draw vertical line.
        SDL_RenderDrawLine(render, start_pos.first + (indent * line),
                           start_pos.second, x + (indent * line), y + draw);

        // Draw horisontal line.
        SDL_RenderDrawLine(render, start_pos.first,
                           start_pos.second + (indent * line), x + draw,
                           y + (indent * line));
      }

      SDL_RenderPresent(render);
      // speed *= 0.8;

      SDL_Delay(20);
   }
 }
  else {

    for (line = 1; line < 9; ++line) {

      // Draw vertical line.
      SDL_RenderDrawLine(render, start_pos.first + (indent * line),
                         start_pos.second, x + (indent * line), y + (indent * 9));

      // Draw horisontal line.
      SDL_RenderDrawLine(render, start_pos.first,
                         start_pos.second + (indent * line), x + (indent * 9),
                         y + (indent * line));
    }

  }

  // Final drawing.
  SDL_RenderPresent(render);
}
