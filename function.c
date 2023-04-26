
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "robots.h"


void initEnnemi(Ennemi *e)
{ 
    e->url="ennemi.png";
    e->img=IMG_Load(e->url);
    if(e->img == NULL)
    {
        printf("unable to load character image %s \n",SDL_GetError());
        return;
    }
        e->pos1.x=0;
        e->pos1.y=0;
        e->pos1.w=0;
        e->pos1.h=0;

        e->pos2.x=200;
        e->pos2.y=200;
	
	e->direction =0;
	e->timer=0;
	e->frame=0;
}




void afficherEnnemi(Ennemi e, SDL_Surface  * screen)
{

    SDL_BlitSurface(e.img,NULL,screen, &e.pos2);
 
}




void moveEnnemi( Ennemi * e)
{

    int xx= 5;
    int yy= 5;


        switch (e->direction) {
            case 0: 
                e->pos2.y-= yy;
                break;
            case 1: 
               e->pos2.y+= yy;
                break;
            case 2:
               e->pos2.x += xx;
                break;
            case 3: 
               e->pos2.x -= xx;
                break;   
        }
       
        if (e->pos2.x < 0 || e->pos2.x > SCREEN_W - e->pos1.w) {
            e->direction = rand() % 4; 
        }
        if (e->pos2.y < 0 || e->pos2.y > SCREEN_H - e->pos1.h) {
            e->direction = rand() % 4; 
        }
}




int collisionBB( SDL_Rect posp,  SDL_Rect pose) 
{
	
 if (posp.x + posp.w < pose.x && posp.x > pose.x + pose.w &&  posp.y + posp.h <pose.y && posp.y > pose.y +pose.h) {
        return 0;
    }
    
    return 1;
}


void scroll_e(Background BG, Ennemi *e, int dx)
{
	if (BG.direction != -1)
	{
		switch(BG.direction){
			case 0:
				e->pos2.y -= dx;
				break;
			case 1 :
				e->pos2.y += dx;
				break;
			case 2: 
				e->pos2.x -= dx;
				break;
			case 3:
				e->pos2.x += dx;
				break;
		}
	}
}

void animerEnnemi(Ennemi* e)
{
	e->pos1.y = 128*e->direction;
	if((SDL_GetTicks() - e->timer) >= 100)
	{
		e->anim.frame++;
		e->anim.pos1.x += 64;
		if (e->frame >= 4)
		{
			e->frame = 0;
			e->pos1.x = 0;
		}
		e->timer = SDL_GetTicks();
	}
}
     










