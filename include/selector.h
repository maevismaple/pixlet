#ifndef SELECTOR_H
#define SELECTOR_H

#include <SDL2/SDL.h>
#include <color.h>

typedef struct selector
{
  SDL_Texture* slider;
  SDL_Texture* selector;

  HSVColor selectedColor;

  int pos_x, pos_y;
  int last_x, last_y; // last mouse pos
  int last_slide;
} Selector;

Selector* createSelector(SDL_Renderer* renderer, int pos_x, int pos_y);
void updateSelector(Selector* selector, SDL_Renderer* renderer, int mouse_x, int mouse_y);
void renderSelector(Selector* selector, SDL_Renderer* renderer);
void destroySelector(Selector* selector);

#endif // SELECTOR_H
