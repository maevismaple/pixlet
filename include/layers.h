#ifndef LAYERS_H
#define LAYERS_H

#include <SDL2/SDL.h>

typedef struct layers
{
  SDL_Surface** surfaces;
  int surfaceCount;
  int maxSurfaces;

  int sprite_width, sprite_height;
} Layers;

Layers* createLayers(int sw, int sh);
void destroyLayers(Layers* layers);

SDL_Surface* pushLayer(Layers* layers);
SDL_Surface* getLayer(Layers* layers, int index);

#endif // LAYERS_H
