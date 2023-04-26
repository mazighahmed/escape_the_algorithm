#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigme.h"
#include <time.h>

void genererEnigme(Enigme *e, char nomfichier[])
{
	int alea;
	FILE *f;
	int i;

	srand(time(NULL));
	alea = rand() % 4; //de 0 a 3	
	f = fopen(nomfichier, "r");
	if (f != NULL)
	{	
		i = 0;
		while(fscanf(f, "%s %d \n", e->qst, &e->repj) != EOF && i<alea)
		{
			i++;
		}
		if( (e->image = IMG_Load(e->qst)) == NULL)
			printf("ERROR:%s \n", SDL_GetError());	
	}
	else printf("Erreur d'ouverture fichier \n");

	e->etat = 0;	
	fclose(f);


}

void afficherEnigme(Enigme *e, SDL_Surface *screen)
{
	SDL_BlitSurface(e->image, NULL, screen, NULL);
}




