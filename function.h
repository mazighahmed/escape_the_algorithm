typedef struct
{
    char *url;
    SDL_Rect pos1;
    SDL_Rect pos2;
    SDL_Surface *img;

	
	int direction;
	int timer;
	int frame;

}Ennemi;


void initEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface  * screen);
void animerEnnemi(Ennemi * e);
void moveEnnemi( Ennemi * e);
int collisionBB(SDL_Rect posp,  SDL_Rect pose) ;
void moveIA( Ennemi * e);



