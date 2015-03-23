all : libSDL_tty.a c64lookalike fontdump

SDL_tty.o : SDL_tty SDL_fnt.o
-o $@ SDL_tty.c SDL_fnt.c -Wall -O2  `sdl-config --cflags`

libSDL_tty.a : SDL_tty.o SDL_fnt.o
	$(AR) rcs

c64lookalike : c64lookalike.c SDL_tty.c
	$(CC) -o $@ $< SDL_tty.c -Wall -O2 `sdl-config --cflags --libs` -lSDL_image

fontdump: fontdump.c
	$(CC) -o $@ $< -Wall -O2 `sdl-config --cflags --libs` -lSDL_image

fonts: fontdump
	./fontdump font8x8 font8x8.png 8 8 " !\"#$$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\`abcdefghijklmnopqrstuvwxyz{|}~" > font8x8.h

# EOF #
