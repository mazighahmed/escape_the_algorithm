#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "texte.h"
#include "score.h"
#include "background.h"
#include "image.h"
#include "player.h"
#include "enigme.h"
#include "menu.h"

void initialiser_txt(text *txte)
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

	initialiser_txt(&(e->txte));
	
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


void sauvegarder (Player p, Background b, char *nomfichier)
{
   FILE* f = fopen(nomfichier, "w");
    if (f != NULL) 
      {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomfichier);

    fprintf(f, "person\n");
    fprintf(f, "%f\n", p.speed);
    fprintf(f, "%d\n", p.vie);
    fprintf(f, "%d %d %d %d\n", p.pos.x, p.pos.y, p.pos.w, p.pos.h);
      }

    fprintf(f, "background\n");
    fprintf(f,"%d %d\n",b.camera_pos.x,b.camera_pos.y);
    fprintf(f, "%d\n", b.frame);
    fclose(f);

}
void charger ( Player * p, Background *b , char * nomfichier)
{

FILE* f = fopen(nomfichier, "r");
    if (f != NULL) 
      {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomfichier);

    fscanf(f, "person\n");
    fscanf(f, "%lf\n", &p->speed);
    fscanf(f, "%d\n", &p->vie);
    fscanf(f, "%hd %hd \n", &p->pos.x, &p->pos.y);
    fscanf(f, "%d\n", &p->score);
      }

    fscanf(f, "background\n");
    fscanf(f,"%hd %hd\n",&b->pos.x,&b->pos.y);
    fscanf(f,"%hd %hd\n",&b->camera_pos.x,&b->camera_pos.y);
    fscanf(f, "%d\n", &b->frame);
    fclose(f);

}

