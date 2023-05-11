#ifndef TEXTE_H
#define TEXTE_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
  TTF_Font *police;
  SDL_Rect pos;
  SDL_Colour color;
  SDL_Surface *txt;
}texte;

void initialiser_texte(texte *txte, int x, int y);
void afficher_texte(SDL_Surface *screen,texte txte);
void liberer_texte(texte txte);
#endif
