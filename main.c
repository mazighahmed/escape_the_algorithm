#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include "enigme.h"


int main()
{

	int jeu = 1;
	SDL_Surface* screen=NULL;
	SDL_Surface *bad, *good, *good_rot, *bad_rot;
	SDL_Event event;
	Enigme e;
	double rotation =0;
	double zoom =0;
	int choix=0;

	if(IMG_Init(IMG_INIT_PNG)==-1)
		printf("ERROR SDL_IMAGE INIT");	
    	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)==-1)
		printf("ERROR SDL INIT \n");

	screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	if( (good = IMG_Load("good.jpg")) == NULL)
		printf("ERROR:%s \n", SDL_GetError());
	if( (bad = IMG_Load("bad.jpg")) == NULL)
		printf("ERROR:%s \n", SDL_GetError());

	genererEnigme(&e, "enigme.txt");
	
	while(jeu)
	{
		if (e.etat == 0)
			afficherEnigme(&e, screen);
		else if (e.etat == 1)
		{
			good_rot = rotozoomSurface(good, rotation, zoom, 1);
			rotation++;
			zoom += 0.0025;
			SDL_Rect pos = {300,300,0,0};
			pos.x -= good_rot->w/2;
			pos.y -= good_rot->h/2;
			SDL_BlitSurface(good_rot, NULL, screen, &pos);
			SDL_FreeSurface(good_rot);
		}
		else if (e.etat == -1)
		{
			bad_rot = rotozoomSurface(bad, rotation, zoom, 1);
			rotation++;
			zoom += 0.0025;
			SDL_Rect pos = {300,300,0,0};
			pos.x -= bad_rot->w/2;
			pos.y -= bad_rot->h/2;
			SDL_BlitSurface(bad_rot, NULL, screen, &pos);	
			SDL_FreeSurface(bad_rot);
		}

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
							choix = 1;
						if (event.motion.y >= 400 && event.motion.y <= (400 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
							choix = 2;
						if (event.motion.y >= 500 && event.motion.y <= (500 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
							choix = 3;
					}
				}
			}
		}
		
		if(choix != 0)
		{
			if(choix == e.repj)
				e.etat = 1;
			else
				e.etat = -1;
		}


	}
	SDL_FreeSurface(e.image);
	SDL_FreeSurface(good);
	SDL_FreeSurface(bad);
	SDL_Quit();
	return 0;
}
