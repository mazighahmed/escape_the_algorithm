#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "image.h"
#include "bouton.h"
#include "menu.h"
#include "texte.h"
#include "player.h"
#include "background.h"
#include <time.h>
#include "robots.h"
#include "enigme.h"

int main()
{
	//DECLARATION VARIABLE
	char input[20];
	Bouton bouton[10];
	background backg;
	SDL_Surface* screen=NULL;
	Image Play0, Exit0, Option0, Back0, bg, bg2;
	Image Play1, Exit1, Option1, Back1;
	Image fs_0, fs_1 ,mus_0 , mus_1, Scroll, ms;
	SDL_Surface *bad, *good, *good_rot, *bad_rot;
	Image GUI;
	logo Logo;
	texte score;
	Player j;
	Uint32 dt, t_prev, timer;
	Background BG;
	Ennemi e;
	Enigme eni;

	int choix=0;
	int enigme = 0;

	Mix_Music* music0;
	Mix_Chunk* click;
	Mix_Chunk* motion;
	SDL_Event event;

	Uint8 *keystates;

	//SDL INIT
	if(IMG_Init(IMG_INIT_PNG)==-1)
		printf("ERROR SDL_IMAGE INIT");
    	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO|SDL_INIT_TIMER)==-1)
		printf("ERROR SDL INIT \n");
	TTF_Init();
//INITIALISATION DU MENU
	//MIXER INIT
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	click = Mix_LoadWAV("click2.wav");
	motion = Mix_LoadWAV("motion.wav");
	music0 = Mix_LoadMUS("Music0.mp3");

	//INIT TEXTE


	//IMAGES INIT

	initialiser_menu(&backg);

	//initialiser_logo(&Logo, "logo.txt");
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	Scroll = initialiser_image("boutons/scroll.png", 473, 537);
	ms = initialiser_image("boutons/bg_options.png", 0, 0);
	fs_0 = initialiser_image("boutons/fs_0.png", 814, 401);
	fs_1 = initialiser_image("boutons/fs_1.png", 814, 401);
	mus_0 = initialiser_image("boutons/mus_0.png", 746, 314);
	mus_1 = initialiser_image("boutons/mus_1.png", 746, 314);

	Play0 = initialiser_image("boutons/Play0.png", SCREEN_W/3 + 75, SCREEN_H/3 + 75);
	Option0 = initialiser_image("boutons/Options0.png", SCREEN_W/3 + 75, SCREEN_H/3 + 200);
	Exit0 = initialiser_image("boutons/Exit0.png", SCREEN_W/3 + 75, SCREEN_H/3 + 325);
	Back0 = initialiser_image("boutons/Back0.png", 25, 25);

	Play1 = initialiser_image("boutons/Play1.png", SCREEN_W/3+75 , SCREEN_H/3 + 75);
	Option1 = initialiser_image("boutons/Options1.png", SCREEN_W/3 + 75, SCREEN_H/3 + 200);
	Exit1 = initialiser_image("boutons/Exit1.png", SCREEN_W/3 + 75, SCREEN_H/3 + 325);
	Back1 = initialiser_image("boutons/Back1.png", 25, 25);
	bouton[0] = initialiser_bouton(Play0, Play1);
	bouton[1] = initialiser_bouton(Option0, Option1);
	bouton[2] = initialiser_bouton(Exit0, Exit1);
	bouton[3] = initialiser_bouton(Back0, Back1);

	bouton[5] = initialiser_bouton(fs_0, fs_1);
	bouton[4] = initialiser_bouton(mus_0, mus_1);
	bouton[6] = initialiser_bouton(Scroll, Scroll);

//INITIALISATION JEU
	initialiser_joueur(&j, "character_karim.png");
	bg2 = initialiser_image("forest.jpg", 0, 0);
	GUI = initialiser_image("GUI.png", 0, 0);
	initialiser_score(&score); 
	initBack(&BG);
	initEnnemi(&e);
//MANETTE


	//GAME LOOP
		//AFFICHAGE ANIMATION LOGO
	//afficher_logo(&Logo, screen);
	timer = SDL_GetTicks();
	while (!backg.done)
	{
	t_prev = SDL_GetTicks();
	//RENDER MENU	
		if (!strcmp(backg.state, "menu"))
		{
			afficher_bg(&backg, screen);
			afficher_menu(bouton, screen);
		}
		else if (!strcmp(backg.state, "options"))
		{
			SDL_BlitSurface(ms.img, NULL, screen, NULL);
			afficher_options(bouton, screen);
		}
		else if (!strcmp(backg.state, "play"))
		{
			afficher(BG, screen);
			afficher_joueur(j, screen);
			afficherEnnemi(e, screen);
			SDL_BlitSurface(GUI.img, NULL, screen, &GUI.pos1);
			afficher_stats(j, screen, score);
		}
		else if (!strcmp(backg.state, "enigme"))
		{
			if (eni.etat == 0)
				afficherEnigme(&eni, screen);
		}

		SDL_Flip(screen);		
	//EVENT
		while(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
				backg.done = 1;


			if (!strcmp(backg.state, "menu"))
			{
				input_clavier(input, event, bouton, motion);
				input_menu(input, event, bouton, motion);
			}
			else if (!strcmp(backg.state, "options"))
			{
				input_options(input, event, bouton, motion);
			}	
		}
			if (eni.etat == 0)
			{
				if (event.type==SDL_MOUSEBUTTONDOWN)
				{
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						if (event.motion.y >= 300 && event.motion.y <= (300 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{
							choix = 1;
						}
						if (event.motion.y >= 400 && event.motion.y <= (400 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{
							choix = 2;
						}
						if (event.motion.y >= 500 && event.motion.y <= (500 + 75) && event.motion.x >= 50 && event.motion.x <= (50 + 400))
						{

							choix = 3;
						}
					}
				}
			}
		
		keystates = SDL_GetKeyState(NULL);
		if (keystates[SDLK_s] && j.saut.state == 0)
		{
			j.dir=0;
			if (BG.camera_pos.y + SCREEN_H <2304 && j.pos.y > SCREEN_H/2)
			{
				BG.direction = 0;
				j.move = 0;		
			}
			else
			{
				BG.direction = -1;
				j.move = 1;
			}
	
		}
		else if (keystates[SDLK_z] && j.saut.state == 0 && BG.camera_pos.y < 2304 - SCREEN_H/2)
		{
			j.dir=1;
			if (BG.camera_pos.y > 0)
			{
				BG.direction = 1;
				j.move = 0;	
			}
			else
			{
				BG.direction = -1;
				j.move = 1;
			}
		}
		else if (keystates[SDLK_d])
		{
			j.dir=2;
			if (BG.camera_pos.x + SCREEN_W <1984 && j.pos.x > SCREEN_W/2)
			{
				BG.direction = 2;
				j.move = 0;
			}
			else
			{
				BG.direction = -1;
				j.move = 1;
			}
	
		}
		else if (keystates[SDLK_q])
		{
			j.dir=3;
			if (BG.camera_pos.x>0 && j.pos.x+BG.camera_pos.x < 1984 - SCREEN_W/2)
			{
				BG.direction = 3;
				j.move = 0;		
			}
			else
			{
				BG.direction = -1;
				j.move = 1;
			}
		}
		else
		{
			j.dir=-1;
			BG.direction = -1;
		}
		if(keystates[SDLK_UP])
		{
			j.acc += 0.005;	
		}
		else if(keystates[SDLK_DOWN])
		{
			j.acc -= 0.001;	
		}
		if (keystates[SDLK_SPACE] && j.dir != 0 && j.dir != 1 && j.saut.state != 1)
		{
			j.saut.state = 1;
			j.saut.x0 = j.pos.x;
			j.saut.y0 = j.pos.y;
			j.saut.dy = 10;		
		}
		if (keystates[SDLK_k])
		{
			strcpy(backg.state, "enigme");	
		}

	//UPDATE		
		update_menu(input, bouton, &backg, click, music0, event, screen);

		if (!strcmp(backg.state, "play"))
		{
			move_joueur(&j, dt);
			scrolling(&BG, BG.direction ,j.dx);
			moveEnnemi(&e);
			scroll_e(BG, &e, j.dx);
			saut(&j);
			animer_joueur(&j);
		}

		if (!strcmp(backg.state, "enigme"))
		{
			if(enigme == 0)
			{	genererEnigme(&eni, "enigme.txt");
				enigme = 1;
			}
			if (choix != 0)
			{
				if (choix == eni.repj)
				{
					printf("reponse juste \n");
					enigme = 0;
					strcpy(backg.state, "play");	
					choix = 0;
				}
				else
				{
					printf("reponse fausse \n");
				}
			}	
		}		
		
		/*
		if( Mix_PlayingMusic() == 0 )
		{
		        //Play the music
			Mix_PlayMusic(music0, -1);
	   	}
		*/

		if ( (SDL_GetTicks() - timer) >= 1000)
		{
			timer = SDL_GetTicks();
			j.score += 1;
		}
		dt= (SDL_GetTicks()-t_prev);
				
	}
	// LIBERER LES IMAGES DE LA MEMOIRE
	liberer_bg(backg);
	SDL_FreeSurface(BG.img);
	SDL_FreeSurface(ms.img);
	SDL_FreeSurface(bg2.img);
	SDL_FreeSurface(GUI.img);
	SDL_FreeSurface(e.img);
	SDL_FreeSurface(j.img_vie.img);	
	SDL_FreeSurface(j.shadow.img);	
	SDL_FreeSurface(j.anim.image.img);
	liberer_boutons(bouton);
	//liberer_logo(&Logo);
	Mix_FreeChunk(click);
	Mix_FreeMusic(music0);
	Mix_CloseAudio();
	liberer_texte(score);
	TTF_Quit();
	SDL_Quit();
	printf("bob");
    	return 0;
}

//test test test
//test 2
