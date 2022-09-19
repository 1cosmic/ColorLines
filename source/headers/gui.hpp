#pragma once

#ifndef _H_GUI
#define _H_GUI

#include <vector>
#include "mainStruts.h"

// init main object SDL.
bool initGame(void);

// Destroy all objects of GUI.
void destroyGame(void);

// Sugar. Run game & show it.
bool showMain(void);

// Display stars & his changes.
void display_stars();

void moveStar(pointField start, pointField end);

// Return star from click of mouse.
pointField coordsStarUnderCursor(int coordX, int coordY);
#endif // !_H_GUI
