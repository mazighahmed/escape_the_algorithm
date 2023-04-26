typedef struct
{
	int etat;
	int repj;
	char qst[14];
	SDL_Surface *image;
	//SDL_Rect pos;

}Enigme;

void genererEnigme(Enigme *e, char nomfichier[]);
void afficherEnigme(Enigme *e, SDL_Surface *screen);
