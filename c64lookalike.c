/** 
 ** Copyright (c) 2006 Ingo Ruhnke <grumbel@gmx.de>
 ** 
 ** This software is provided 'as-is', without any express or implied
 ** warranty. In no event will the authors be held liable for any
 ** damages arising from the use of this software.
 ** 
 ** Permission is granted to anyone to use this software for any
 ** purpose, including commercial applications, and to alter it and
 ** redistribute it freely, subject to the following restrictions:
 ** 
 **   1. The origin of this software must not be misrepresented; you
 **      must not claim that you wrote the original software. If you
 **      use this software in a product, an acknowledgment in the
 **      product documentation would be appreciated but is not
 **      required.
 ** 
 **   2. Altered source versions must be plainly marked as such, and
 **      must not be misrepresented as being the original software.
 ** 
 **   3. This notice may not be removed or altered from any source
 **      distribution.
 ** 
 */

/*  Compile via:
 *
 *   gcc -D__TEST__ -ansi -pedantic -Wall -g -O2 -o SDL_tty SDL_tty.c `sdl-config --cflags --libs` -lSDL_image 
 *
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "SDL_tty.h"

int main()
{
  SDL_Surface* screen;
  int quit = 0;
  TTY* tty;
  TTY_Font* font;
  SDL_Event event;

  if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) <0 )
    {
      printf("Unable to init SDL: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  atexit(SDL_Quit);
  
  screen = SDL_SetVideoMode(800, 600, 0,
                            SDL_HWSURFACE|SDL_DOUBLEBUF); /* |SDL_FULLSCREEN);*/

  SDL_WM_SetCaption("C64 Look alike", NULL);
  SDL_EnableUNICODE(1); 
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  if ( screen == NULL )
    {
      printf("Unable to set 640x480 video: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

  {
    // SDL_Surface* temp = TTY_CreateRGBSurface(font8x12);
    SDL_Surface* temp = IMG_Load("c64_16x16.png");
    font = FNT_Create(temp, 16, 16, 
                      "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    tty = TTY_Create(40, 30, font);
    SDL_FreeSurface(temp);
  }

  TTY_SetCursorCharacter(tty, '\x7f');
  TTY_EnableVisibleCursor(tty, 1);

  TTY_printf(tty, "\n    **** COMMODORE 64 BASIC V%d ****\n\n", 2);
  TTY_printf(tty, " %dk RAM SYSTEM  38911 BASIC BYTES FREE\n\n", 64);
  TTY_printf(tty, "READY.\n");

  while (!quit)
    {
      while(SDL_PollEvent(&event))
        {
          switch(event.type) 
            { 
            case SDL_QUIT: 
              quit = 1;
              break;

            case SDL_MOUSEBUTTONDOWN:
              if (event.button.button == 1)
                {
                  if (event.button.x >= 80
                      && event.button.y >= 60
                      && ((event.button.x - 80) / tty->font->glyph_width) < tty->width
                      && ((event.button.y - 60) / tty->font->glyph_height) < tty->height)
                  TTY_SetCursor(tty, 
                                (event.button.x - 80) / tty->font->glyph_width,
                                (event.button.y - 60) / tty->font->glyph_height);
                }
              break;
              
            case SDL_KEYDOWN:
              if (event.key.keysym.sym == SDLK_RETURN)
                {
                  TTY_putchar(tty, '\n');
                }
              else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                  exit(EXIT_SUCCESS);
                }
              else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                  int cx, cy;
                  TTY_GetCursor(tty, &cx, &cy);
              
                  if (cx == 0 && cy != 0)
                    cy -= 1;
                  else if (cx != 0)
                    cx -= 1;
                  else
                    cy = tty->height - 1;
              
                  TTY_SetCursor(tty, cx, cy);
                  TTY_putchar_nomove(tty, 0);
                }

              else if (event.key.keysym.sym == SDLK_HOME)
                {
                  int sx, sy;
                  TTY_GetScrollOffset(tty, &sx, &sy);
                  TTY_SetScrollOffset(tty, sx, sy + 1);
                }
              else if (event.key.keysym.sym == SDLK_END)
                {
                  int sx, sy;
                  TTY_GetScrollOffset(tty, &sx, &sy);
                  TTY_SetScrollOffset(tty, sx, sy - 1);
                }

              else if (event.key.keysym.sym == SDLK_DELETE)
                {
                  int sx, sy;
                  TTY_GetScrollOffset(tty, &sx, &sy);
                  TTY_SetScrollOffset(tty, sx - 1, sy);
                }
              else if (event.key.keysym.sym == SDLK_PAGEDOWN)
                {
                  int sx, sy;
                  TTY_GetScrollOffset(tty, &sx, &sy);
                  TTY_SetScrollOffset(tty, sx + 1, sy);
                }

              else if (event.key.keysym.sym == SDLK_LEFT)
                {
                  int cx, cy; TTY_GetCursor(tty, &cx, &cy);
                  TTY_SetCursor(tty, cx - 1, cy);
                }
              else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                  int cx, cy; TTY_GetCursor(tty, &cx, &cy);
                  TTY_SetCursor(tty, cx + 1, cy);
                }
              else if (event.key.keysym.sym == SDLK_UP)
                {
                  int cx, cy; TTY_GetCursor(tty, &cx, &cy);
                  TTY_SetCursor(tty, cx, cy - 1);
                }
              else if (event.key.keysym.sym == SDLK_DOWN)
                {
                  int cx, cy; TTY_GetCursor(tty, &cx, &cy);
                  TTY_SetCursor(tty, cx, cy + 1);
                }
              else if (event.key.keysym.unicode && (event.key.keysym.unicode & 0xFF80) == 0) 
                {
                  TTY_putchar(tty, event.key.keysym.unicode & 0x7f);
                }
              break;
            }
        }

      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 138, 138, 255));

      {
        SDL_Rect rect;
        rect.x = 80;
        rect.y = 60;
        rect.w = tty->width * tty->font->glyph_width;
        rect.h = tty->height * tty->font->glyph_height;

        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 202));
      }
      
      TTY_Blit(tty, screen, 80, 60);

      SDL_Flip(screen);
    }

  TTY_Free(tty);
  FNT_Free(font);
  return 0;
}

/* EOF */

