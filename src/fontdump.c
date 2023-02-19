#include <stdint.h>
#include <stdlib.h>

#include <SDL_image.h>

void write_escaped_string(FILE* out, char const* glyphs)
{
  int i;
  int len = strlen(glyphs);
  fputc('"', out);

  uint8_t const* codepoints = (uint8_t const*)glyphs;
  for(i = 0; i < len; ++i)
  {
    if (codepoints[i] == '"') {
      fprintf(out, "\\\"");
    } else if (codepoints[i] == '\\') {
      fprintf(out, "\\\\");
    } else if (codepoints[i] >= 0x7f) {
      fprintf(out, "\\x%x", (int)codepoints[i]);
    } else {
      fputc(codepoints[i], out);
    }
  }
  fputc('"', out);
}

int main(int argc, char** argv)
{
  if (argc != 6)
    {
      puts("Usage: fontdump FONTNAME IMAGEFILE GLYPHWIDTH GLYPHHEIGHT GLYPHS");
    }
  else
    {
      if (SDL_Init(0) != 0)
        {
          puts(SDL_GetError());
          exit(EXIT_FAILURE);
        }

      int i;
      char* font_name    = argv[1];
      int   glyph_width  = atoi(argv[3]);
      int   glyph_height = atoi(argv[4]);
      char* glyphs       = argv[5];

      /* Dump code */
      SDL_Surface* temp = IMG_Load(argv[2]);

      {
        FILE* out = stdout;

        SDL_LockSurface(temp);
        fprintf(out, "/* automatically generated file */\n\n");
        fprintf(out, "char   %s_glyphs[] = ", font_name); write_escaped_string(out, glyphs); fprintf(out, ";\n");
        fprintf(out, "int    %s_width  = %d;\n", font_name, temp->w);
        fprintf(out, "int    %s_height = %d;\n", font_name, temp->h);
        fprintf(out, "int    %s_pitch  = %d;\n", font_name, temp->pitch);
        fprintf(out, "int    %s_bpp    = %d;\n", font_name, temp->format->BitsPerPixel);
        fputc('\n', out);
        fprintf(out, "Uint32 %s_rmask  = 0x%08x;\n", font_name, temp->format->Rmask);
        fprintf(out, "Uint32 %s_gmask  = 0x%08x;\n", font_name, temp->format->Gmask);
        fprintf(out, "Uint32 %s_bmask  = 0x%08x;\n", font_name, temp->format->Bmask);
        fprintf(out, "Uint32 %s_amask  = 0x%08x;\n", font_name, temp->format->Amask);
        fputc('\n', out);
        fprintf(out, "int    %s_glyph_width  = %d;\n", font_name, glyph_width);
        fprintf(out, "int    %s_glyph_height = %d;\n", font_name, glyph_height);
        fputc('\n', out);
        fprintf(out, "unsigned char %s_data[] = \n{\n  ", font_name);
        for(i = 0; i < (temp->w * temp->h * 4); ++i)
          {
            fprintf(out, "0x%02x", ((unsigned char*)(temp->pixels))[i]);
            if (i != ((temp->w * temp->h * 4) - 1))
              fprintf(out, ", ");
            else
              fprintf(out, "\n");

            if (((i+1) % 12) == 0)
              fprintf(out, "\n  ");
          }
        fprintf(out, "};\n\n/* EOF */\n");
        fclose(out);
        SDL_UnlockSurface(temp);
      }
    }
  return 0;
}

/* EOF */
