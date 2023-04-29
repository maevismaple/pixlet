#include <layers.h>
#include <stdio.h>

Layers* createLayers(int sw, int sh)
{
  Layers* layers = (Layers*) malloc(sizeof(Layers));
  layers->maxSurfaces = 4;
  layers->surfaceCount = 1;
  layers->surfaces = (SDL_Surface**) malloc(sizeof(SDL_Surface*)*layers->maxSurfaces);
  
  layers->surfaces[0] = SDL_CreateRGBSurface(0,
      sw, sh, 32, 
      0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
  layers->sprite_width = sw;
  layers->sprite_height = sh;

  return layers;
}

void destroyLayers(Layers* layers)
{
  for (int i = 0; i < layers->surfaceCount; i++)
  {
    SDL_FreeSurface(layers->surfaces[i]);
  }
  free(layers->surfaces);
  free(layers);
}

SDL_Surface* pushLayer(Layers* layers)
{
  layers->surfaceCount++;
  if (layers->surfaceCount > layers->maxSurfaces)
  {
    layers->maxSurfaces += (int) layers->maxSurfaces/4;
    layers->surfaces = (SDL_Surface**) realloc(
        layers->surfaces, sizeof(SDL_Surface*)*layers->maxSurfaces);
  }

  layers->surfaces[layers->surfaceCount] = SDL_CreateRGBSurface(0,
      layers->sprite_width, layers->sprite_height, 32,
      0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

  return layers->surfaces[layers->surfaceCount];
}

SDL_Surface* getLayer(Layers* layers, int index)
{
  if (index > layers->surfaceCount)
  {
    printf("Surface out of bounds.\n");
    return NULL;
  }

  return layers->surfaces[index];
}
