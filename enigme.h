#define  Enigme_H

typedef struct
{
  TTF_Font *police;
  SDL_Colour color;
  SDL_Surface *txt;
}text;

typedef struct
{
	int etat;
	int repj;
	SDL_Surface *bg;
	char qst[20];
	char rep1[20];
	char rep2[20];
	char rep3[20];
	SDL_Rect pos_qst;
	SDL_Rect pos_rep1;
	SDL_Rect pos_rep2;
	SDL_Rect pos_rep3;	
	SDL_Surface *image;
	SDL_Rect pos;
	text txte;

}Enigme;

void initialiser_txt(text *txte);
void genererEnigme(Enigme *e, char nomfichier[]);
void afficherEnigme(Enigme *e, SDL_Surface *screen);
void sauvegarder (Player p, Background b, char *nomfichier) ;
void charger ( Player * p, Background *b , char *nomfichier);

