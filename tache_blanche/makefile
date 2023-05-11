prog:main.o menu.o image.o texte.o player.o background.o enigme.o
	gcc main.o menu.o image.o texte.o player.o background.o enigme.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c
	gcc -c main.c -g
menu.o:menu.c
	gcc -c menu.c -g
texte.o:texte.c
	gcc -c texte.c -g
player.o:player.c
	gcc -c player.c -g
image.o:image.c
	gcc -c image.c -g
background.o:background.c
	gcc -c background.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g
