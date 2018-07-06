#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "font.h"

int fd=-1;
SDL_RWops *rw;
TTF_Font *font=NULL;
SDL_Surface *ScreenSurface=NULL;
SDL_Surface *screen=NULL;
extern uint8_t rwfont[];
volatile unsigned long *mem;

int get_mem_total(void)
{
	FILE *meminfo = fopen("/proc/meminfo", "r");
	if(meminfo == NULL){
		return 0;
	}

	char line[256];
	while(fgets(line, sizeof(line), meminfo)){
		int ram;
		if(sscanf(line, "MemTotal: %d kB", &ram) == 1){
			fclose(meminfo);
			return ram;
		}
	}

	fclose(meminfo);
	return 0;
}

int main(int argc, char* argv[])
{
  int loop=1;
	long ram=0;
	char buf[255];
	SDL_Rect rt={0};
  SDL_Event event;
	SDL_Color color={255, 255, 255};

  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("%s, failed to SDL_Init\n", __func__);
    return -1;
  }
  SDL_ShowCursor(0);
 
  ScreenSurface = SDL_SetVideoMode(320, 480, 16, SDL_HWSURFACE);
  screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 16, 0, 0, 0, 0);
  if(screen == NULL){
    printf("%s, failed to SDL_SetVideMode\n", __func__);
    return -1;
  }
  if(TTF_Init() == -1){
    printf("failed to TTF_Init\n");
    return -1;
  }
  rw = SDL_RWFromMem(rwfont, sizeof(rwfont));
  font = TTF_OpenFontRW(rw, 1, 14);
	TTF_SetFontHinting(font, TTF_HINTING_MONO);
	TTF_SetFontOutline(font, 0);
  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
 
	ram = get_mem_total();
	sprintf(buf, "RAM Size: %d(KB)", ram);
	SDL_Surface *msg = TTF_RenderText_Solid(font, buf, color);
  rt.x = 20;
  rt.y = 20;
  SDL_BlitSurface(msg, NULL, screen, &rt);
  SDL_FreeSurface(msg);

  int x, y;
  uint32_t *s = (uint32_t*)screen->pixels;
  uint32_t *d = (uint32_t*)ScreenSurface->pixels;
  for(y=0; y<240; y++){
    for(x=0; x<160; x++){
      *d++ = *s++;
    }   
    d+= 160;
  }
  SDL_Flip(ScreenSurface);
	while(loop){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_KEYDOWN){
        loop = 0;
        break;
      }
    }   
  }

  SDL_RWclose(rw);
  SDL_Quit();
  return 0;    
}

