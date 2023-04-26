#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "enigme.h"
#include <time.h>

void initialiser_texte(texte *txte)
{
	txte->police= TTF_OpenFont("raidercrusader.ttf", 50);
	txte->color.r = 255;
	txte->color.g = 255;
	txte->color.b = 255;
}

void genererEnigme(Enigme *e, char nomfichier[])
{
	int alea;
	FILE *f;
	int i;

	srand(time(NULL));
	alea = rand() % 4;
	f = fopen(nomfichier, "r");
	if (f != NULL)
	{	
		i = 0;
		while(fscanf(f, "%s %s %s %s %d \n", e->qst, e->rep1, e->rep2, e->rep3, &e->repj) != EOF && i<alea)
		{
			i++;
		}	
	}
	else printf("Erreur d'ouverture fichier \n");
	
	fclose(f);
	
	e->bg = IMG_Load("enigme1.jpg");
	e->etat = 0;
	e->pos_rep1.x = 50;
	e->pos_rep2.x = 50;
	e->pos_rep3.x = 50;
	e->pos_qst.x = 200;

	e->pos_qst.y = 150;
	e->pos_rep1.y = 300;
	e->pos_rep2.y = 400;
	e->pos_rep3.y = 500;

	initialiser_texte(&(e->txte));
	
}

void afficherEnigme(Enigme *e, SDL_Surface *screen)
{
	SDL_BlitSurface(e->bg, NULL, screen, NULL);

	e->txte.txt = TTF_RenderText_Blended(e->txte.police, e->qst, e->txte.color);  
	SDL_BlitSurface (e->txte.txt, NULL, screen, &e->pos_qst);

	e->txte.txt = TTF_RenderText_Blended(e->txte.police, e->rep1, e->txte.color);
	SDL_BlitSurface (e->txte.txt, NULL, screen, &e->pos_rep1);

	e->txte.txt = TTF_RenderText_Blended(e->txte.police, e->rep2, e->txte.color);
	SDL_BlitSurface (e->txte.txt, NULL, screen, &e->pos_rep2);

	e->txte.txt = TTF_RenderText_Blended(e->txte.police, e->rep3, e->txte.color);
	SDL_BlitSurface (e->txte.txt, NULL, screen, &e->pos_rep3);
}

