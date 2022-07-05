#pragma once

#ifndef _H_GUI
#define _H_GUI

// init main object SDL.
bool initGame(void);

// Destroy all objects of GUI.
void destroyGame(void);

// Sugar. Run game & show it.
bool showMain(void);

// Display stars & his changes.
void display_stars();

#endif // !_H_GUI
