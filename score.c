
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "background.h"
#include <SDL/SDL_mixer.h>
#include "score.h"

void incrementer(scoreinfo *s)
{
static Uint32 timer = 0;
if ( (SDL_GetTicks() - timer) >= 1000)
        {
            timer = SDL_GetTicks();
            s->score += 10;
	    s->temps += 1;
	    printf("%d %d\n",s->score, s->temps);

        }
}

//void innitialisertxt

void savescore(scoreinfo s,char *filename)
{
FILE *f=fopen(filename,"a");
fprintf(f,"%d %d\n",s.score,s.temps);
}

void bestscore(char *filename,scoreinfo trois[])
{
FILE *f=fopen(filename,"r");
int i=0,j,b,max;
scoreinfo temp;
char ch[30];
while (fscanf(f,"%d %d",&trois[i].score,&trois[i].temps)!=EOF)
	{i++;}

 for (j=0; j<i-1; j++)
    {
        max=j ;
        for (b=j+1; b<i; b++)
        {
            if (trois[b].score>trois[max].score)
                max=b;
        }
        temp=trois[j];
        trois[j]=trois[max];
        trois[max]=temp;
    }
j=0;	
while(j!=i&&j<3)
	{//printf("score:%d  temps:%d\n",trois[j].score,trois[j].temps);
	sprintf(ch,"%d %d",trois[j].score,trois[j].temps);
	printf("%s\n",ch);
	j++;}
	
 

}
