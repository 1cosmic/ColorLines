#include <algorithm>
#include <iostream>
#include <vector>

#include <time.h>

using namespace std;

int field[9][9];           // main field.
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

int schMultiStars(int count) {
  // Search of multiplie stars in one line.

  // TO-DO: WRITE THIS FUNC. FOR SEARCH MULTIPLIE STAR.

  int line; // index of line.
  int cell; // index of star.

  int lastStar; // last color of star (for "if").
}

void printField(void) {
  // print field in terminal-read-mode.

  int line, cell;

  for (line = 0; line < 9; ++line) {

    printf("Line %i:", line);

    for (cell = 0; cell < 9; ++cell)
      cout << field[line][cell] << " ";

    cout << endl;
  }
}
