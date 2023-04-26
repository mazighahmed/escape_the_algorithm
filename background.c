#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "background.h"
#include "image.h"
#include <SDL/SDL_mixer.h>
void initBack(Background * b)
{
    b->img=IMG_Load("forest.jpg");
    if(b->img==NULL)
        printf("error5");
    b->tab[0]=IMG_Load("map_animation/1.png");
    b->tab[1]=IMG_Load("map_animation/2.png");
    b->tab[2]=IMG_Load("map_animation/3.png");
    b->tab[3]=IMG_Load("map_animation/4.png");

    b->pos.x=0;
    b->pos.y=0;

    b->camera_pos.x=0;
    b->camera_pos.y=0;
    b->camera_pos.w=SCREEN_W;
    b->camera_pos.h=SCREEN_H;

    b->frame=0;

    b->music[0]=Mix_LoadMUS("bob.mp3");
    b->music[1]=Mix_LoadMUS("spngbb.mp3");
	
	Mix_PlayMusic(b->music[0],-1);

}

void afficher(Background b,SDL_Surface *screen)
{
	SDL_BlitSurface(b.img,&b.camera_pos,screen,&b.pos);
	SDL_BlitSurface(b.tab[b.frame],&b.camera_pos,screen,&b.pos);
}

void scrolling(Background *b,int direction,int pas)
{
    if (direction==0)
        b->camera_pos.y += pas;
    if (direction==1)
        b->camera_pos.y -= pas;
    if (direction==2)
        b->camera_pos.x +=pas;
    if (direction==3)
        b->camera_pos.x -=pas;
}
void animerBack(Background *b)
{
	
	
	static Uint32 last_frame_time = 0;
        if (SDL_GetTicks() - last_frame_time > 500) {
            b->frame = (b->frame +1)  ;
		if (b->frame ==4)
			b->frame=0;
		
           last_frame_time = SDL_GetTicks();}


}
