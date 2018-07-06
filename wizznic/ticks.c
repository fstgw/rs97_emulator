#include "time.h"
#include "text.h"

static int lastTick=0; //SDL clock
static int ticks=0; //ticks since last frame
static int drawTime=0;

static int frames=0;
void frameStart()
{
  ticks = SDL_GetTicks() - lastTick;
  lastTick = SDL_GetTicks();
  frames++;
}

static int fpsSecondCounter=0;
static int fps=0;
static char fpsStr[64] = { '0','0','\0' };
static int sample=0;

int getTicks()
{
  return(ticks);
}

int getTimeSinceFrameStart()
{
  return( SDL_GetTicks() - lastTick );
}


void drawFPS(SDL_Surface* scr)
{
  fps++;
  fpsSecondCounter+=getTicks();
  if(fpsSecondCounter > 9999)
  {
    sample++;
    sprintf(fpsStr, "%i Fps (%i)", fps/10, sample);
    fps=0;
    fpsSecondCounter=0;
  }

  txtWrite(scr,FONTSMALL, fpsStr, 0,0);
}
