#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "texte.h"
#include "image.h"
#include "player.h"
#include "background.h"
#include "enigme.h"
#include "menu.h"

int main()
{

	int jeu = 1;
	SDL_Surface* screen=NULL;
	SDL_Event event;
        Menu sm;
	int f;
        Player p;
        Background bg;
        char *nomfich;
        Mix_Music *son;
	
	if(IMG_Init(IMG_INIT_PNG)==-1)
		printf("ERROR SDL_IMAGE INIT");	
    	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)==-1)
		printf("ERROR SDL INIT \n");
	

	screen = SDL_SetVideoMode(1200, 800, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        initialiser_son(son);
	sm =  init_SousMenu();
       
	
	while(jeu)
	{
                afficher_sousmenu(sm,screen);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
				jeu = 0;

		}
		f = update_SousMenu(&sm, event, &f);
                if (f==0){
                  sauvegarder ( p, bg, "sauvegarde.txt");
                }
                else{
                  charger ( &p,&bg , "sauvegarde.txt");
                }		
	}

	
	SDL_Quit();
	return 0;
}
