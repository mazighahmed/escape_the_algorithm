typedef struct
{
	int state;
	int x0;
	int y0;
	double gravite;
	int dy;
}
Jump;

typedef struct
{
	animation anim;
	SDL_Rect pos;  	//position x et y relatif au personnage
	int dir;	//direction (0:down 1:up 2:droite 3:gauche -1:aucun mouvement)
	int vie;
	int score;
	double speed;
	double acc;
	int dx;
	Jump saut;
	int move;

	Image shadow;
	Image img_vie;
}Player;



//INITIALISATION JOUEUR
void initialiser_joueur(Player* joueur, char path[]);


//AFFICHAGE
void afficher_joueur(Player joueur, SDL_Surface* screen);
void afficher_stats(Player joueur, SDL_Surface *screen, texte txte);


//UPDATE
void move_joueur(Player* joueur, Uint32 dt);
void animer_joueur(Player* joueur);
void saut(Player* joueur);
