#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdlib.h>

#include <editor.h>
#include <color.h>

#define bool uint8_t
#define true 1
#define false 0

void save_surface(const char* file_name, SDL_Renderer* renderer, SDL_Surface* surface)
{
    IMG_SavePNG(surface, file_name);
}

SDL_Surface* load_surface(const char* file_name)
{
  return IMG_Load(file_name);
}
int main(int argc, const char** argv)
{
  Editor* editor = createEditor(32, 32);

  bool should_quit = false;

  while (!should_quit)
  {
    int pressed_button;

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
        case SDL_QUIT:
          should_quit = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
          {
            if (e.button.button == SDL_BUTTON_RIGHT)
              pressed_button = SDL_BUTTON_RIGHT;
            if (e.button.button == SDL_BUTTON_LEFT)
              pressed_button = SDL_BUTTON_LEFT;
            break;
          }
        case SDL_MOUSEBUTTONUP:
          {
            pressed_button = -1;
            break;
          }
      }
    }
    
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if (pressed_button == SDL_BUTTON_LEFT)
    { 
      if (mx > 0 && mx < editor->sprite_width*editor->pixel_size &&
          my > 0 && my < editor->sprite_height*editor->pixel_size)
      {
        int gmx = mx / editor->pixel_size;
        int gmy = my / editor->pixel_size;
        
        SDL_Color c = RGBAColorToSDL(hsv_to_rgb(editor->selector->selectedColor));

        set_pixel(getLayer(editor->layers, 0), gmx, gmy, c);
      }

      updateSelector(editor->selector, editor->renderer, mx, my);
    }
  
    SDL_SetRenderDrawColor(editor->renderer, 90, 90, 90, 255);
    SDL_RenderClear(editor->renderer);
    
    SDL_Rect background = {0, 0, 
      editor->sprite_width*editor->pixel_size, 
      editor->sprite_height*editor->pixel_size};
    
    SDL_SetRenderDrawColor(editor->renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(editor->renderer, &background);

    for (int i = 0; i < editor->layers->surfaceCount; i++)
    {
      SDL_Surface* surf = getLayer(editor->layers, i);
      SDL_Texture* tex = SDL_CreateTextureFromSurface(editor->renderer, surf);
      
      int w = editor->sprite_width*editor->pixel_size;
      int h = editor->sprite_height*editor->pixel_size;

      SDL_Rect dst = {.x = 0, .y = 0, .w = w, .h = h};

      SDL_RenderCopy(editor->renderer, tex, NULL, &dst);
      SDL_DestroyTexture(tex);
    }
    
    renderSelector(editor->selector, editor->renderer);

    SDL_RenderPresent(editor->renderer);
  }

  destroyEditor(editor);
  return 0;
}
