#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "image.h"


Image initialiser_image(char path[20], int x, int y)
{	
	SDL_Surface* img=NULL;
	Image image;

	if((img = IMG_Load(path))==NULL)
		printf("ERROR:%s \n", SDL_GetError());
	
	image.img = img;
	image.pos1.x = x;
	image.pos1.y = y;
        
	return image;
} 


void liberer_image(Image image)
{
	SDL_FreeSurface(image.img);
}

void initialiser_logo(logo* anim, char path[20])
{
	int i=0;
	FILE *f;
	char temp[30];
	f = fopen(path, "r");
	if (f != NULL)
	{
		while(fscanf(f, "%s \n", temp) != EOF)
		{
			(*anim).img[i] = IMG_Load(temp);
			if ((*anim).img[i] == NULL)
				printf("Erreur: initialiser_animation()\n");
			else
				{
				printf("%s initialisé \n", temp);
				i++;
				}
		}
		(*anim).current = 0;	
		(*anim).time = 0;
		(*anim).pos.x = 0;
		(*anim).pos.y = 0;

		printf("%d images initialisé\n", i);
	}
	else printf("Erreur d'ouverture fichier \n");
		
	fclose(f);
}

void liberer_logo(logo* anim)
{
	int i;
	for (i=0; i<196; i++)
	{
		SDL_FreeSurface((*anim).img[i]);
	}

}


void afficher_logo(logo* anim, SDL_Surface *screen)
{
	SDL_Delay(1000);
	do
	{
		SDL_BlitSurface((*anim).img[(*anim).current],  NULL, screen,   &anim->pos);
		if((SDL_GetTicks() - (*anim).time) >= 33)
		{
			(*anim).current++;
			(*anim).time = SDL_GetTicks();
		}
		SDL_Flip(screen);
	}
	while((*anim).current<196);
	SDL_Delay(1500);

}



