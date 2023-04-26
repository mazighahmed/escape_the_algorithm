#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "enigme.h"


int main()
{

	int jeu = 1;
	SDL_Surface* screen=NULL;
	SDL_Event event;
	Enigme e;

	int choix=0;

	if(IMG_Init(IMG_INIT_PNG)==-1)
		printf("ERROR SDL_IMAGE INIT");	
    	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)==-1)
		printf("ERROR SDL INIT \n");
	TTF_Init();

	screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	genererEnigme(&e, "enigme.txt");
	
	while(jeu)
	{

		afficherEnigme(&e, screen);
		SDL_Flip(screen);

		while(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
				jeu = 0;
			if (e.etat == 0)
			{
				if (event.type==SDL_MOUSEBUTTONDOWN)
				{
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						if (event.motion.y >= 300 && event.motion.y <= (300 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{
							printf("reponse 1\n");
							choix = 1;
						}
						if (event.motion.y >= 400 && event.motion.y <= (400 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{
							printf("reponse 2\n");
							choix = 2;
						}
						if (event.motion.y >= 500 && event.motion.y <= (500 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{
							printf("reponse 3\n");
							choix = 3;
						}
					}
				}
			}
		}
		
		if (choix != 0)
		{
			if (choix == e.repj)
				printf("reponse juste \n");
			else
				printf("reponse fausse \n");
		}
		


	}
	SDL_FreeSurface(e.bg);
	TTF_CloseFont (e.txte.police);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
