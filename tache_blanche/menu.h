struct Boutton
{
    int actif;
    SDL_Surface* Img[2];
    SDL_Rect Pos;
    Mix_Chunk *music;
    int num;
};
typedef struct Boutton Boutton;
struct Menu
{
    SDL_Surface * image_bg;
    SDL_Rect pos_bg;
    int nbr_boutton; 
    Boutton tab[10];
    Mix_Music *son;
    int num_bt_actif; 
};
typedef struct Menu Menu;
Menu init_SousMenu();
void afficher_sousmenu(Menu sous_menu,SDL_Surface *ecran);
int update_SousMenu(Menu *sous_menu, SDL_Event input, int *interface);
void liberer_SousMenu(Menu* sous_menu);
void initialiser_audiobref(Mix_Chunk *music);
void initialiser_son(Mix_Music *son);
void liberer_musiquebref(Mix_Chunk *music);
void liberer_musique(Mix_Music *son);
