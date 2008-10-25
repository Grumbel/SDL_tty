#include <SDL_image.h>

int main()
{
  if (0)
    {
      /* Dump code */
      temp = IMG_Load("8x14font.png");

      printf("Size:   %dx%d\n", temp->w, temp->h);
      printf("Pitch:  %d\n",    temp->pitch);
      printf("RMask:  %08x\n",  temp->format->Rmask);
      printf("GMask:  %08x\n",  temp->format->Gmask);
      printf("BMask:  %08x\n",  temp->format->Bmask);
      printf("AMask:  %08x\n",  temp->format->Amask);

      {
        char* font_name = "font8x12";
        FILE* out = fopen("font.h", "w");
 
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
        fprintf(out, "int    %s_glyph_width  = %d;\n", font_name, width);
        fprintf(out, "int    %s_glyph_height = %d;\n", font_name, height);
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
  else
    {
      /*temp = SDL_CreateRGBSurfaceFrom(font8x12_data,
        font8x12_width, font8x12_height, font8x12_bpp, font8x12_pitch,
        font8x12_rmask, font8x12_gmask,  font8x12_bmask, font8x12_amask);*/
      

    }
}

