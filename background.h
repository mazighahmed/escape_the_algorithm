
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct 
{
SDL_Rect pos;
SDL_Rect camera_pos;
SDL_Surface *img;
int direction;
SDL_Surface *tab[4];
Mix_Music *music[3];
int frame;
}Background;

void initBack(Background *b);
void afficher(Background b,SDL_Surface *screen);
void scrolling(Background *b,int direction,int pas);
void animerBack(Background *b);
