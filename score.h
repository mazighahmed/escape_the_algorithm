#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct{
int score,temps;
char nom_player[10];
SDL_Rect pos_nom,pos_score,pos_temps;
SDL_Surface *txt_nom,*txt_scr,*txt_temps;
TTF_Font *font;
SDL_Color color;
}scoreinfo;





void innitialisertxt(scoreinfo *s,TTF_Font *f);
void incrementer(scoreinfo *s);
void savescore(scoreinfo s,char *filename);
void bestscore(char *filename,scoreinfo trois[],SDL_Surface *screen);
