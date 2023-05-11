#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "texte.h"

void initialiser_texte(texte *txte, int x, int y)
{
	TTF_Init();
	txte->police= TTF_OpenFont("raidercrusader.ttf", 100);
	txte->color.r = 255;
	txte->color.g = 0;
	txte->color.b = 0;

	txte->pos.x = x;
	txte->pos.y = y;
}
void afficher_texte(SDL_Surface *screen, texte txte)
{
	txte.txt = TTF_RenderText_Blended(txte.police, "Bienvenue", txte.color);
	SDL_BlitSurface (txte.txt, NULL, screen, &txte.pos);
}

void liberer_texte(texte txte)
{
	SDL_FreeSurface(txte.txt);
	TTF_CloseFont (txte.police);
}
