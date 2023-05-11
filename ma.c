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
#include "background.h"
#include "player.h"
#include <time.h>
#include "robots.h"
#include "enigme.h"
#include "collision.h"
#include "score.h"
#include "door.h"

int main()
{
	//DECLARATION VARIABLE
	int i;
	char input[20];
	Bouton bouton[10];
	
	background backg;
	SDL_Surface* screen=NULL;
	Image Play0, Exit0, Option0, Back0, bg, bg2, menu;
	Image Play1, Exit1, Option1, Back1;
	Image ordi;////////////////////////////////
	Image fs_0, fs_1 ,mus_0 , mus_1, Scroll, ms;
	SDL_Surface *bad, *good, *good_rot, *bad_rot;
	Image GUI;
	logo Logo;
	texte score;
	Player j, j2;
	Uint32 dt, t_prev, timer;
	Background BG, BG2,bob;
	Ennemi e, e2;
	Enigme eni;

	int choix=0;
	int enigme = 0;
	int game_mode =1; 

	Mix_Music* music0;
	Mix_Chunk* click;
	Mix_Chunk* motion;
	SDL_Event event;

	Uint8 *keystates;
	Uint8 *bebsi;

	
	beb bab1,bab2,bab3;



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
	SDL_Rect pos_abs, pos_abs2;
	scoreinfo info, yo[3];
	info.score=0;
	info.temps=0;
	int best=0;
	bg2 = initialiser_image("forest.jpg", 0, 0);
	GUI = initialiser_image("GUI.png", 0, 0);
	menu = initialiser_image("menu/menu.png", 0, 0);
	if (game_mode == 1)
	{
		initialiser_joueur(&j, "character_karim.png", 500,400);
		initBack(&BG);
		init_bob(&bob);// hedhi init taa lvision limite//talkaha fel background.c
		initEnnemi(&e, 600, 600);
		init_door(&bab3,1200,1000,"biben/3.png");
		init_door(&bab2,400,-60,"biben/2.png");
		init_door(&bab1,650,400,"biben/1.png");
		ordi=initialiser_image("contour.png",0,-1000);//initalisation taa contour lordi//
		//init_key(&bab3.k,1700,400);
		//init_key(&bab2.k,1000,1000);
		//init_key(&bab1.k);
	}
	else
	{
		initialiser_joueur(&j, "character_karim.png", 320, 400);
		initialiser_joueur(&j2, "character_karim.png", 960, 400);
		initBack2(&BG2);
		initBack1(&BG);
		initEnnemi(&e, 500, 600);	
		initEnnemi(&e2, 1240, 600);
	}
	initialiser_score(&score); 
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
			SDL_BlitSurface(menu.img, NULL, screen, NULL);
			afficher_menu(bouton, screen);
		}
		else if (!strcmp(backg.state, "options"))
		{
			SDL_BlitSurface(backg.img[backg.frame], NULL, screen, NULL);
			SDL_BlitSurface(ms.img, NULL, screen, NULL);
			afficher_options(bouton, screen);
		}
		else if (!strcmp(backg.state, "play"))
		{
			if (game_mode ==2)
			{
			afficher(BG2, screen);
			afficherEnnemi(e2, screen);
			afficher(BG, screen);
			afficher_joueur(j, screen);
			afficher_joueur(j2, screen);
			if (e.pos2.x < SCREEN_W/2)
			afficherEnnemi(e, screen);
			//SDL_BlitSurface(GUI.img, NULL, screen, &GUI.pos1);
			afficher_stats(j, screen, score);
			}
			if (game_mode == 1)
			{
			//SDL_BlitSurface(BG.mask,&BG.camera_pos,screen,&BG.pos);
			afficher(BG, screen);
			afficher_beb(bab3,screen);//afficher beb 3
			afficher_beb(bab2,screen);//afficher beb 2
			afficher_beb(bab1,screen);//afficher beb 1
			SDL_BlitSurface(ordi.img,NULL,screen,&ordi.pos1);
			afficher_joueur(j, screen);
			afficherEnnemi(e, screen);
			//SDL_BlitSurface(bob.img, &bob.camera_pos, screen, &bob.pos); hedhi li tahser lvision
			
			SDL_BlitSurface(GUI.img, NULL, screen, &GUI.pos1);

	
			

			

			afficher_stats(j, screen, score);
			}
			if (best)
				bestscore("scores.txt", yo, score, screen);
		}
		else if (!strcmp(backg.state, "enigme"))
		{
			if (eni.etat == 0)
				afficherEnigme(&eni, screen);
		}
		else if (!strcmp(backg.state, "select"))
		{
			SDL_BlitSurface(backg.img[backg.frame], NULL, screen, NULL);
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
			else if (!strcmp(backg.state, "play"))
			{
				if (event.type==SDL_KEYDOWN)
					printf("%c \n", event.key.keysym.sym);
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
		if (game_mode ==1)
		{
			keystates = SDL_GetKeyState(NULL);
			update_pos_abs(&pos_abs, j);

			if (keystates[j.config.key[0]] && j.saut.state == 0 && !collision_parfaite_down(BG.mask, pos_abs) && !collision_door_down(BG.mask,pos_abs,bab2))
			{
				j.dir=0;
				if (BG.camera_pos.y + SCREEN_H <2304 && j.pos.y > SCREEN_H/2 )
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
			else if (keystates[j.config.key[1]] && j.saut.state == 0 && !collision_parfaite_up(BG.mask, pos_abs) && !collision_door_up(BG.mask,pos_abs,bab1)&& !collision_door3_up(BG.mask,pos_abs,bab3))
			{
				j.dir=1;
				if (BG.camera_pos.y > 0 && BG.camera_pos.y < 2304 - SCREEN_H/2 )
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
			else if (keystates[j.config.key[2]] && !collision_parfaite_right(BG.mask, pos_abs,j.saut.state))
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
			else if (keystates[j.config.key[3]] && !collision_parfaite_left(BG.mask, pos_abs))
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
			if(keystates[SDLK_e])
			{
				j.acc += 0.005;	
			}
			else if(keystates[SDLK_a])
			{
				j.acc -= 0.001;	
			}
			if (collisionBB(j.pos,bab3.k.pos)==1 )
				{bab3.k.state=1;
				info.score+=500;
				}
			if (collisionBB(j.pos,bab2.k.pos)==1 && bab2.k.state==0)
				{bab2.k.state=1;
				info.score+=250;
				j.score+=250;
				}
			if (collisionBB(j.pos,bab1.k.pos)==1 && bab1.k.state==0)
				{bab1.k.state=1;
				info.score+=150;
				j.score+=150;
				}
			
				
			
					
			
			if (keystates[SDLK_SPACE] && j.dir != 0 && j.dir != 1 && j.saut.state != 1)
			{
				j.saut.state = 1;
				j.saut.x0 = j.pos.x;
				j.saut.y0 = j.pos.y;
				j.saut.dy = 10;		
			}
		}
		if (game_mode == 2  )
		{
			keystates = SDL_GetKeyState(NULL);
			update_pos_abs(&pos_abs, j);
			update_pos_abs(&pos_abs2, j2);
			if (keystates[j.config.key[0]] && j.saut.state == 0 && !collision_parfaite_down(BG.mask, pos_abs))
			{
				j.dir=0;
				if (BG.camera_pos.y + SCREEN_H/2 <2304 && j.pos.y > SCREEN_H/2 )
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
			else if (keystates[j.config.key[1]] && j.saut.state == 0 && !collision_parfaite_up(BG.mask, pos_abs))
			{
				j.dir=1;
				if (BG.camera_pos.y > 0 && BG.camera_pos.y < 2304 - SCREEN_H/4 )
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
			else if (keystates[j.config.key[2]] && !collision_parfaite_right(BG.mask, pos_abs,j.saut.state))
			{
				j.dir=2;
				if (BG.camera_pos.x + SCREEN_W/2 <1984 && j.pos.x > SCREEN_W/4 )
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
			else if (keystates[j.config.key[3]] && !collision_parfaite_left(BG.mask, pos_abs))
			{
				j.dir=3;
				if (BG.camera_pos.x>0 && j.pos.x+BG.camera_pos.x < 1984 - SCREEN_W/4)
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
			if(keystates[SDLK_e])
			{
				j.acc += 0.005;	
			}
			else if(keystates[SDLK_a])
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
			// PLAYEr2
			keystates = SDL_GetKeyState(NULL);
			if (keystates[SDLK_DOWN] && j2.saut.state == 0 && !collision_parfaite_down(BG2.mask, pos_abs2))
			{
				j2.dir=0;
				if (BG2.camera_pos.y + SCREEN_H/2 <2304 && j2.pos.y > SCREEN_H/2)
				{	
					BG2.direction = 0;
					j2.move = 0;
				}
				else
				{
					BG2.direction = -1;
					j2.move = 1;
				}
		
			}
			else if (keystates[SDLK_UP] && j2.saut.state == 0 && !collision_parfaite_up(BG2.mask, pos_abs2))
			{
				j2.dir=1;
				if (BG2.camera_pos.y > 0 && BG2.camera_pos.y < 2304 - SCREEN_H/2 )
				{
					BG2.direction = 1;
					j2.move = 0;	
				}
				else
				{
					BG2.direction = -1;
					j2.move = 1;
				}
			}
			else if (keystates[SDLK_RIGHT] && !collision_parfaite_right(BG2.mask, pos_abs2,j2.saut.state))
			{
				j2.dir=2;
				if (BG2.camera_pos.x + SCREEN_W/4 <1984 && j2.pos.x > SCREEN_W/4 )
				{
					BG2.direction = 2;
					j2.move = 0;
				}
				else
				{
					BG2.direction = -1;
					j2.move = 1;
				}
		
			}
			else if (keystates[SDLK_LEFT] && !collision_parfaite_left(BG2.mask, pos_abs2))
			{
				j2.dir=3;
				if (BG2.camera_pos.x>0 && j2.pos.x+BG2.camera_pos.x < 1984 - SCREEN_W/4)
				{
					BG2.direction = 3;
					j2.move = 0;		
				}
				else
				{
					BG2.direction = -1;
					j2.move = 1;
				}
			}
			else
			{
				j2.dir=-1;
				BG2.direction = -1;
			}
			/*
			if(keystates[SDLK_NUM1])
			{
				j2.acc += 0.005;	
			}
			else if(keystates[SDLK_NUM2])
			{
				j2.acc -= 0.001;	
			}
			*/
			if (keystates[SDLK_SPACE] && j2.dir != 0 && j2.dir != 1 && j2.saut.state != 1)
			{
				j2.saut.state = 1;
				j2.saut.x0 = j2.pos.x;
				j2.saut.y0 = j2.pos.y;
				j2.saut.dy = 10;		
			}
	}//if gamemode
		//--------------
		if (keystates[SDLK_k])
		{
			strcpy(backg.state, "enigme");	
		}
		if (keystates[SDLK_p])
		{
			strcpy(backg.state, "play");	
		}
		if (keystates[SDLK_j])
		{
			best= 1;	
		}
		else
			best = 0;
		if (keystates[SDLK_c]) //reglage joueur 1
		{
				i=0;
				while(i <= 5)
				{ 
					printf("Key %d ? \n", i);
					SDL_WaitEvent(&event);

						if (event.type==SDL_QUIT)
							backg.done = 1;
						if (event.type==SDL_KEYDOWN)
						{
							j.config.key[i] = event.key.keysym.sym;
							i++;
						}
				}
			for (i=0; i<=5; i++)
				printf("Key %d: %s \n",i ,SDL_GetKeyName(j.config.key[i]) );	
		}
		

	//UPDATE		
		update_menu(input, bouton, &backg, click, music0, event, screen);

		if (!strcmp(backg.state, "play"))
		{
			move_joueur(&j, dt, &BG);
			scrolling(&BG, BG.direction ,j.dx);
			
			//update pos_absolue enemy
			e.pos_abs.x = e.pos2.x + BG.camera_pos.x;
			e.pos_abs.y = e.pos2.y + BG.camera_pos.y;
			e.pos_abs.w = 64;
			e.pos_abs.h = 64;
			moveEnnemi(&e, BG.mask);
			scroll_e(BG, &e, j.dx);
			scroll_biben(BG, &bab3,j.dx);
			scroll_biben(BG, &bab2,j.dx);
			scroll_biben(BG, &bab1,j.dx);
			saut(&j);
			animer_joueur(&j);
			animerEnnemi(&e);

			

			animerBack(&BG);
			if (game_mode == 2)
			{
			move_joueur(&j2, dt, &BG2);
			scrolling(&BG2, BG2.direction ,j2.dx);
			//update pos_absolue enemy2
			e2.pos_abs.x = e2.pos2.x + BG2.camera_pos.x;
			e2.pos_abs.y = e2.pos2.y + BG2.camera_pos.y;
			e2.pos_abs.w = 64;
			e2.pos_abs.h = 64;
			//J2
			moveEnnemi(&e2, BG2.mask);
			scroll_e(BG2, &e2, j2.dx);
			saut(&j2);
			animer_joueur(&j2);
			animerEnnemi(&e2);
			}
			if (collisionBB(e.pos2, j.pos))
				strcpy(backg.state, "enigme");	
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
					e.pos2.x = -150;
					j.score += 300;
				}
				else
				{
					j.vie -= 1;
				}
			}	
		}
/*
		if (!strcmp(backg.state, "reglage"))
		{
			
				for(i=0; i<6; i++)
				{ 
					printf("Key %d ?", i);
					while(SDL_WaitEvent(&event))
					{
						if (event.type==SDL_QUIT)
							backg.done = 1;
						if (event.type==SDL_KEYDOWN)
						{
							j.config.key[i] = event.key.keysym.sym;
						}
					}
				}	
		}		
		*/
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
	info.score=j.score;
	
	savescore(info,"scores.txt");
	// LIBERER LES IMAGES DE LA MEMOIRE
	liberer_bg(backg);
	SDL_FreeSurface(menu.img);
	SDL_FreeSurface(BG.img);
	SDL_FreeSurface(BG.mask);
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
    	return 0;
}
