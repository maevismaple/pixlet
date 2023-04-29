#include <editor.h>

Editor* createEditor(int sw, int sh)
{
  Editor* ed = (Editor*) malloc(sizeof(Editor));
  ed->window = SDL_CreateWindow("pixlet!",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      900, 600, 0);
  ed->renderer = SDL_CreateRenderer(ed->window, -1, SDL_RENDERER_ACCELERATED);
  ed->layers = createLayers(sw, sh);
  ed->sprite_width = sw;
  ed->sprite_height = sh;

  ed->pixel_size = 15.f;

  ed->selector = createSelector(ed->renderer, 500, 0);

  return ed;
}

void destroyEditor(Editor* editor)
{
  SDL_DestroyWindow(editor->window);
  SDL_DestroyRenderer(editor->renderer);
  
  destroyLayers(editor->layers);
  destroySelector(editor->selector);

  free(editor);
}
