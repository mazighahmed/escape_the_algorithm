#define SCREEN_W 1984
#define SCREEN_H 2304


typedef struct bg
{
char state[20];
SDL_Surface* img;
int done;
}
background;

typedef struct img
{
SDL_Rect pos1;
SDL_Rect pos2;
SDL_Surface* img;
}
Image;
typedef struct anim { 
Image image; int frame; int time;
 } animation;

typedef struct logo
{
SDL_Surface *img[196];
SDL_Rect pos;
int current;
int start;
int time;
}
logo;


//INITIALISATION
Image initialiser_image(char path[20], int x, int y);
void initialiser_logo(logo *anim, char path[20]);

//AFFICHER ANIMATION
void afficher_logo(logo* anim, SDL_Surface *screen);

//LIBERATION MEMOIRE
void liberer_logo(logo* anim);
void liberer_image(Image image);

