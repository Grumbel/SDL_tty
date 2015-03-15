SDL_tty
=======

SDL_tty is a very simple library that tries to simulate a primitive
terminal that allows you to print to the screen in much the same way
that you would print to stdout. The usage is like this:

    // Initialize SDL as usual

    // Create the fixed width font
    TTY_Font* font = TTY_CreateFont(temp, 16, 16,
                                    "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    // Create the terminal
    TTY* tty = TTY_Create(40, 30, font);

    // Your mainloop
    while(1)
    {
       // print text via
       TTY_printf(tty, "Hello World\n");

       // renderer the terminal to the screen
       TTY_Blit(tty, screen, 80, 60);

       SDL_Flip(screen);
    }

    TTY_Free(tty);
    TTY_FreeFont(font);

The `c64lookalike` programm demonstrates some more advanced usage of
the library.


Features
--------

* can create a primitive terminal for text output
* some primitve support for scrolling
* support for fixed-width fonts
* support for loading fonts from file as well as directly from code, a
  image to .h converter is provided
* small and meant to be included in your source, not meant to be compiled as
  a real .so/dll library


Webpage/Contact
---------------

The latest version is currently available via:

* https://github.com/Grumbel/SDL_tty

Question and suggestion should go to:

  Ingo Ruhnke <grumbel@gmail.com>

