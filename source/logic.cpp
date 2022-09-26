#include "headers/mainStruts.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <time.h>
#include <valarray>

using namespace std;

int field[9][9];           // main field.
int localColorStar = 0;    // last saved color of star.
vector<int> freeSpace[9];  // field of free space.
vector<int[4]> multiStars; // safe y,x, color, count of multiplie stars.

int colors[3]; // next color list.

void destroyLogic() {

  freeSpace->clear();
  multiStars.clear();
}

void initField(void) {
  // Create & return * bx field (arrax 9x9).

  int x, y;

  // Initialization block (all pos. in field = 0 (color ID)).
  for (y = 0; y < 9; ++y)
    for (x = 0; x < 9; ++x)
      field[x][y] = 0;
}

void randomColors(void) {
  // generate random color.

  int i; // indexcolor.

  /* printf("Random colors: "); */
  // Create randomize color list.
  for (i = 0; i < 3; ++i) {
    colors[i] = (rand() % 7) + 1;
    /* printf("%i ", colors[i]); */
  }
  /* printf("\n"); */
}

int checkFreeSpace(void) {
  // Check of free space in main field.
  // Return 0 if space < 3.

  int x, y;
  int counter = 0; // counter free cells.

  // Pasring field.
  for (y = 0; y < 9; ++y) {
    freeSpace[y].clear(); // clear line.

    /* printf("\nLine %i:", y); */
    // if cell = 0 (free space) -> ++ counter.
for (x = 0; x < 9; ++x)
      if (!field[y][x]) {
        freeSpace[y].push_back(x);
        ++counter;

        /* printf(" %i", freeSpace[y].back()); */
      }
  }
  /* printf("\nFree space: %i\n", counter); */

  if (counter < 3)
    return 0;
  else
    return 1;
}

bool wayIsExists(pointField start, pointField end) {
    // Return true if between points exist linear of way.

    int i;
    int x, y, step;

    x = end.string - start.string;
    y = end.column - start.column;

    if (!x && !y)
        return false;

    if (!x) {

        step = (y > 0) ? -1 : 1;    // setup vector of moving.

        while(y) {

            i = start.column + y;
            if (field[start.string][i])
                return false;

            y += step;
        }
        return true;

    } else if (!y) {

        step = (x > 0) ? -1 : 1;    // setup vector of moving.

        while(x) {

            i = start.string + x;
            if (field[i][end.column])
                return false;

            x += step;
        }
        return true;
    }

    return false;
}

void swapStar(pointField current) {
    // Swap star into new place.

    field[current.string][current.column] = localColorStar;
}

void clearStar(pointField star) {
    localColorStar = field[star.string][star.column];
    field[star.string][star.column] = 0;
}

void randomPutStar(void) {
  // Select randomize line & pos (in line) & put in this color.

  vector<int> freeLines;
  int i_color, i; // for -> for c:

  vector<int> *line;
  vector<int>::iterator iCell; // index cell for cleaning free cell.
  int randLine, randCell;      // for human eyes.

  // For add & display star for screen.
  // star curStar;

  // Clean last three stars.
  // threeStars.clear();

  for (i_color = 0; i_color < 3; ++i_color) {

    // Clear list for search free lines.
    freeLines.clear();

    // Init this list of the number line.
    for (i = 0; i < 9; ++i)
      if (freeSpace[i].size()) // if have free cells in line, write where index.
        freeLines.push_back(i);

    // Get random number of line.
    randLine = freeLines[rand() % freeLines.size()];

    // Get random cell from this line.
    randCell = rand() % freeSpace[randLine].size();
    randCell = freeSpace[randLine][randCell]; // re-write this value.

    // Put color in main field.
    field[randLine][randCell] = colors[i_color]; // put random color from list

    // Put star in the list (for GUI.cpp & draw to screen!).
    // curStar.x = randCell;
    // curStar.y = randLine;
    // curStar.color = colors[i_color];

    // threeStars.push_back(curStar);

    /* printf("Field[%i][%i] = %i\n", randLine, randCell,
     * field[randLine][randCell]); */

    // Search iterator of cell from freeSpace (for free)randomPutStar.
    line = &freeSpace[randLine];

    // Delete this cell from freeSpace.
    iCell = find(line->begin(), line->end(), randCell);
    line->erase(iCell);
  }

  // Cleaning machine >:)
  freeLines.clear();
}

bool clearMultiLine(int multiCount, int *score) {
  // Search of multiplie stars in one line / column / diagonal.

  int i, i2;
  int countStr, countColumn;            // counter of multi color.
  int multiColorStr, multiColorColumn;  // last multi color.
  int *pColorStr, *pColorColumn;        // pointer in field of colors.

  bool isCleaned = false;

  for (i = 0; i < 9; ++i) {

      // Set up first values.
      countStr = 1;
      countColumn = 1;

      // Set first star as last multicolor.
      multiColorStr = field[i][0];
      multiColorColumn = field[0][i];

      // TODO:
      // Удаляется последняя ячейка, в которой может и не быть мультицвета.



      for (i2 = 1; i2 < 9; ++i2) {
          pColorStr = &field[i][i2];
          pColorColumn = &field[i2][i];

          // If multicolor - line:
          if (*pColorStr == multiColorStr && *pColorStr && i2 != 8) {
              ++countStr;

          // If multicolor is break:
          } else {
              int start = i2 -1;

              if (*pColorStr == multiColorStr) {
                  start = i2;
                  ++countStr;
              }

              // If multicolor count is >= main, clear last countStr star:
              if (countStr >= multiCount) {

                  for (int cell = start; cell >= i2 - countStr; --cell) {
                      field[i][cell] = 0;
                  }

                  *score += (countStr > multiCount) ? pow(countStr, 2) : countStr;
                  isCleaned = true;
              }

              // If else, set up current color is multi & refresh here of counter.
              multiColorStr = *pColorStr;
              countStr = 1;
          }

          // If multicolor - column:
          if (*pColorColumn == multiColorColumn && *pColorColumn && i2 != 8) {
              ++countColumn;

          // If multicolor is break:
          } else {
              int start = i2 -1;

              if (*pColorColumn == multiColorColumn) {
                  start = i2;
                  ++countColumn;
              }

              // If multicolor count is >= main, clear last countStr star:
              if (countColumn >= multiCount) {

                  for (int cell = start; cell >= i2 - countColumn; --cell) {
                      field[cell][i] = 0;
                  }

                  *score += (countColumn > multiCount) ? pow(countColumn, 2) : countColumn;
                  isCleaned = true;
              }

              // If else, set up current color is multi & refresh here of counter.
              multiColorColumn = *pColorColumn;
              countColumn = 1;
          }
      }
  }

  return isCleaned;
}
