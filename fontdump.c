#include <SDL_image.h>

int main(int argc, char** argv)
{
  if (argc != 5)
    {
      puts("Usage: fontdump FONTNAME IMAGEFILE GLYPHWIDTH GLYPHHEIGHT");
    }
  else
    {
      int i;
      char* font_name  = argv[1];
      int glyph_width  = atoi(argv[3]);
      int glyph_height = atoi(argv[4]);

      /* Dump code */
      SDL_Surface* temp = IMG_Load(argv[2]);
  
      printf("Size:   %dx%d\n", temp->w, temp->h);
      printf("Pitch:  %d\n",    temp->pitch);
      printf("RMask:  %08x\n",  temp->format->Rmask);
      printf("GMask:  %08x\n",  temp->format->Gmask);
      printf("BMask:  %08x\n",  temp->format->Bmask);
      printf("AMask:  %08x\n",  temp->format->Amask);

      {
        FILE* out = fopen("fount-out.h", "w");
 
        SDL_LockSurface(temp);
        fprintf(out, "/* automatically generated file */\n\n");
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
