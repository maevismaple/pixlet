#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <layers.h>
#include <selector.h>

typedef struct editor
{
  SDL_Renderer* renderer;
  SDL_Window* window;

  Layers* layers;
  int sprite_width, sprite_height;
  float pixel_size;

  Selector* selector;
} Editor;

Editor* createEditor(int sw, int sh);
void destroyEditor(Editor* editor);

#endif // EDITOR_H
