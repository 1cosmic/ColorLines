#include <SDL2/SDL.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// Dirs for loading.
const fs::path cur_path =
    filesystem::current_path().parent_path();  // get cur/parent path.
const fs::path src_path = cur_path / "images"; // images path.
const fs::path star_path = src_path / "stars"; // images path.

// My grab texture collector >:))
vector<SDL_Texture *> loadedTexture;

// Block of texture.
SDL_Texture *tx_bgd;              // background of the game.
vector<SDL_Texture *> tx_star(7); // star texture vector.

// For import in other modules.
SDL_Texture *get_bgd() {
  return tx_bgd;
}
//
SDL_Texture *get_star(int ID) {
  return tx_star[ID -1];
}
//////////////////

SDL_Texture *loadTexture(SDL_Renderer *render, string path) {
  // Load in RAM image of texture.

  SDL_Surface *image = nullptr;
  SDL_Texture *texture = nullptr;

  image = SDL_LoadBMP(path.c_str()); // load image.

  if (image) {
    texture =
        SDL_CreateTextureFromSurface(render,
                                     image); // convert imaopL:e -> texture.
    SDL_FreeSurface(image);                  // cleaner.

    loadedTexture.push_back(texture); // mark texture for cleaner.

  } else {
    printf("Texture | %s | is not loaded. Error: %s", path.c_str(),
           SDL_GetError());
  }

  return texture;
}

bool cleanTexture() {
  // Cleaner of texture.

  int i = 0;
  vector<SDL_Texture *>::iterator i_texture;

  // Very very very long cleaner, its perfect iterator!
  for (i_texture = loadedTexture.begin(); i_texture != loadedTexture.end();
       ++i_texture) {

    SDL_DestroyTexture(*i_texture);
    ++i;
  }

  if (!i) {
    printf("Null texture list.");
    return false;

  } else {
    printf("%i texture was delete.", i);
    return true;
  }
}

bool initTexture(SDL_Renderer *render) {
  // Load & convert all image in texture.

  // Load background.
  tx_bgd = loadTexture(render, src_path / "GUI" / "background.bmp");

  // Create array of path list.
  fs::path star_path[] = {"stars/1/", "stars/2/", "stars/3/", "stars/4/",
                          "stars/5/", "stars/6/", "stars/7/"};

  int star_number = 0; // for star_path

  vector<SDL_Texture *>::iterator i; // iterator vector of texture stars.

  // Load all star image in RAM.
  for (i = tx_star.begin(); i != tx_star.end(); ++i, ++star_number)
    *i = loadTexture(render,
                     (src_path / star_path[star_number] / "star.bmp").c_str());

  cout << "All images was loaded." << endl;

  return true;
}
