env = Environment(CFLAGS=['-Wall', '-O2'])
env.ParseConfig('sdl-config --cflags --libs')

libsdl_tty = env.StaticLibrary('SDL_tty', ['SDL_tty.c', 'SDL_fnt.c'])

env.Program('c64lookalike', ['c64lookalike.c'], LIBS=[libsdl_tty, 'SDL_image'])
env.Program('fontdump', ['fontdump.c'], LIBS=['SDL_image'])

Command('font8x8.h', ['font8x8.png'],
        './fontdump font8x8 font8x8.png 8 8 ' +
        '"\x7f !\\\"#$$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\\`abcdefghijklmnopqrstuvwxyz{|}~"' +
        " > font8x8.h")

# EOF #
