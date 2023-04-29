#include <selector.h>

Selector* createSelector(SDL_Renderer* renderer, int pos_x, int pos_y)
{
  Selector* selector = (Selector*) malloc(sizeof(Selector));

  SDL_Surface* selectorSurface = SDL_CreateRGBSurface(0,
      255, 255, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
  
  for (int y = 0; y < 255; y++)
  {
    for (int x = 0; x < 255; x++)
    {
      HSVColor hsv = {
        0,
        (double) x / 255,
        1.f - ((double) y / 255)
      };

      set_pixel(selectorSurface, x, y, RGBAColorToSDL(hsv_to_rgb(hsv)));
    }
  }

  SDL_Surface* sliderSurface = SDL_CreateRGBSurface(0,
      255, 255, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

  for (int y = 0; y < 255; y++)
  {
    for (int x = 0; x < 255; x++)
    {
      HSVColor hsv = {
        ((double) x / 255) * 360,
        1.f, 1.f
      };

      set_pixel(sliderSurface, x, y, RGBAColorToSDL(hsv_to_rgb(hsv)));
    }
  }  

  selector->slider = SDL_CreateTextureFromSurface(renderer, sliderSurface);
  selector->selector = SDL_CreateTextureFromSurface(renderer, selectorSurface);
  HSVColor dcolor = {0.f,0.f,1.f};
  selector->selectedColor = dcolor;
  selector->pos_x = pos_x;
  selector->pos_y = pos_y;
  selector->last_x = pos_x+3.f, selector->last_y = pos_y+3.f;
  selector->last_slide = selector->pos_x+3.f;
}

void updateSelector(Selector* selector, SDL_Renderer* renderer, int mouse_x, int mouse_y)
{
  // Selector interaction
  if (mouse_x > selector->pos_x && mouse_x < selector->pos_x + 255 &&
      mouse_y > selector->pos_y && mouse_y < selector->pos_y + 255)
  {
    int rx = mouse_x - selector->pos_x, ry = mouse_y - selector->pos_y;
    selector->last_x = mouse_x, selector->last_y = mouse_y;
    selector->selectedColor.s = (double) rx / 255.f;
    selector->selectedColor.v = 1.f - (double) ry / 255.f;
  }
  
  // Slider interaction
  if (mouse_x > selector->pos_x && mouse_x < selector->pos_x + 255 &&
      mouse_y > selector->pos_y+300 && mouse_y < selector->pos_y + 350)
  {
    int rx = mouse_x - selector->pos_x, ry = mouse_y - selector->pos_y;
    selector->selectedColor.h = ((double) rx / 255)*360;
    selector->last_slide = mouse_x-3;
    SDL_Surface* selectorSurface = SDL_CreateRGBSurface(0,
        255, 255, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    for (int y = 0; y < 255; y++)
    {
      for (int x = 0; x < 255; x++)
      {
        HSVColor hsv = {
          selector->selectedColor.h,
          (double) x / 255,
          1.f - ((double) y / 255)
        };

        set_pixel(selectorSurface, x, y, RGBAColorToSDL(hsv_to_rgb(hsv)));
      }
    }
  
    selector->selector = SDL_CreateTextureFromSurface(renderer, selectorSurface);
  }
}

void renderSelector(Selector* selector, SDL_Renderer* renderer)
{
  SDL_Rect dst1 = {selector->pos_x, selector->pos_y, 255, 255};
  SDL_RenderCopy(renderer, selector->selector, NULL, &dst1);
  SDL_Rect dst2 = {selector->pos_x, selector->pos_y+300, 255, 50};
  SDL_RenderCopy(renderer, selector->slider, NULL, &dst2);
  
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 190);
  SDL_Rect lpos = {selector->last_x-3, selector->last_y-3, 6, 6};
  SDL_RenderFillRect(renderer, &lpos);

  SDL_Rect sliderpos = {selector->last_slide-3, selector->pos_y+250+50, 6, 50};
  SDL_RenderFillRect(renderer, &sliderpos);
}

void destroySelector(Selector* selector)
{
  SDL_DestroyTexture(selector->slider);
  SDL_DestroyTexture(selector->selector);

  free(selector);
}
