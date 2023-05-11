#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "image.h"
#include "texte.h"
#include "player.h"

void initialiser_joueur(Player* joueur, char path[])
{
	joueur->pos.x = 500;
	joueur->pos.y = 500;
	joueur->dir = 0;
	joueur->speed = 0.2;
	joueur->acc = 0;
	joueur->vie = 3;
	joueur->score = 0;
	joueur->dx = 0;
	joueur->move = 1;
	
	joueur->saut.state = 0;
	joueur->saut.gravite = 0;
	
	if((joueur->anim.image.img = IMG_Load(path)) == NULL)
		printf("ERROR:%s \n", SDL_GetError());
	if((joueur->shadow.img = IMG_Load("shadow.png")) == NULL)
		printf("ERROR:%s \n", SDL_GetError());
	if((joueur->img_vie.img = IMG_Load("vie.png")) == NULL)
		printf("ERROR:%s \n", SDL_GetError());

	joueur->img_vie.pos1.x = 163;
	joueur->img_vie.pos1.y = 10;
	joueur->img_vie.pos2.x = 0;
	joueur->img_vie.pos2.y = 0;
	joueur->img_vie.pos2.w = 303;
	joueur->img_vie.pos2.h = 22;

	joueur->anim.image.pos2.w = 64;
	joueur->anim.image.pos2.h = 128;
	joueur->anim.image.pos2.x = 0;
	joueur->anim.image.pos2.y = 0;
	joueur->anim.frame = 0;
	joueur->anim.time = 0;
}


void afficher_joueur(Player joueur, SDL_Surface* screen)
{
	SDL_BlitSurface(joueur.shadow.img, NULL, screen,  &joueur.shadow.pos1);	
	SDL_BlitSurface(joueur.anim.image.img,  &joueur.anim.image.pos2, screen,   &joueur.pos);	
}

void afficher_stats(Player joueur, SDL_Surface *screen, texte txte)
{
	char str[20];
	char txt[] = "score:";
	sprintf(str, "%d", joueur.score); 
	strcat(txt, str);
	txte.txt = TTF_RenderText_Blended(txte.police, txt, txte.color);
	SDL_BlitSurface (txte.txt, NULL, screen, &txte.pos);

	joueur.img_vie.pos2.x = 101*(3-joueur.vie);
	SDL_BlitSurface (joueur.img_vie.img, &joueur.img_vie.pos2, screen, &joueur.img_vie.pos1);
}

void animer_joueur(Player* joueur)
{
	if (joueur->dir != -1)
	{
		joueur->anim.image.pos2.y = 128*joueur->dir;
		if((SDL_GetTicks() - joueur->anim.time) >= 100)
			{
				joueur->anim.frame++;
				joueur->anim.image.pos2.x += 64;
				if (joueur->anim.frame >= 4)
				{
					joueur->anim.frame = 0;
					joueur->anim.image.pos2.x = 0;
				}
				joueur->anim.time = SDL_GetTicks();
			}
	}
	else
	{
		joueur->anim.image.pos2.y = 0;
		joueur->anim.image.pos2.x = 0;
		joueur->anim.frame = 0;
	}
}

void move_joueur(Player* joueur, Uint32 dt)
{	
	joueur->acc -= 0.001;
	if (joueur->acc <= 0)
		joueur->acc = 0;
	else if (joueur->acc > 0.1)
		joueur->acc = 0.1;

	joueur->dx = 0.5*(joueur->acc)*(dt*dt)+(joueur->speed)*(dt);
	if (joueur->dir != -1 && joueur->move == 1)
	{	
		if (joueur->dir == 0)//DOWN		
			joueur->pos.y += joueur->dx;
		else if (joueur->dir == 1)//UP
			joueur->pos.y -= joueur->dx;
		else if (joueur->dir == 2)//RIGHT
			joueur->pos.x += joueur->dx;
		else if (joueur->dir == 3)//LEFT
			joueur->pos.x -= joueur->dx;
	}
	
	joueur->shadow.pos1.x = joueur->pos.x - 21;
	joueur->shadow.pos1.y = joueur->pos.y + 110;
	
	
}

void saut(Player* joueur)
{
	if(joueur->saut.state == 1)
	{
		joueur->pos.y -= (joueur->saut.dy - joueur->saut.gravite);	
		joueur->saut.gravite += 0.5;
		joueur->shadow.pos1.y = joueur->saut.y0 + 110;
		if (joueur->pos.y >= joueur->saut.y0)
		{
			joueur->saut.state = 0;
			joueur->saut.gravite = 0;
		}
	}
}


