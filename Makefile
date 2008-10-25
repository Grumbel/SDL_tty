all : c64lookalike fontdump

c64lookalike : c64lookalike.c SDL_tty.c
	$(CC) -o $@ $< SDL_tty.c -Wall -O2 `sdl-config --cflags --libs` -lSDL_image

fontdump: fontdump.c
	$(CC) -o $@ $< -Wall -O2 `sdl-config --cflags --libs` -lSDL_image

fonts: fontdump
	./fontdump font8x8 font8x8.png 8 8 " !\"#$$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\`abcdefghijklmnopqrstuvwxyz{|}~" > font8x8.h

# EOF #
