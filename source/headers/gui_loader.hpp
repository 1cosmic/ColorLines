#pragma once

#ifndef _H_GUI_LOADER
#define _H_GUI_LOADER

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

// Block of texture.
SDL_Texture *get_bgd();
SDL_Texture *get_star(int ID);

// Load texture from FS in RAM.
// Optimizing.
bool initTexture(SDL_Renderer *render);

// Clean texture from RAM.
bool cleanTexture();

#endif // !_H_GUI_LOADER
