#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#include "board.h"
#include "cursor.h"
#include "draw.h"
#include "input.h"
#include "sprite.h"
#include "text.h"
#include "sound.h"
#include "states.h"
#include "game.h"
#include "levels.h"
#include "leveleditor.h"

#ifndef GP2X
  #include "dumplevelimages.h"
#endif

SDL_Surface *ScreenSurface=NULL;
int main(int argc, char *argv[])
{
  #ifdef WIN32
  //Redirect stdout to console on windows, so we can see what's going in.
  FILE *stream;
  stream = freopen("CON", "w", stdout);
  #endif
  int doScale=0;
  int doDump=0;
  int state=1; //Game, Menu, Editor, Quit

  //Init SDL
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER ) <0 )
  {
    printf("SDL_Init failed: %s\n",SDL_GetError());
    return(-1);
  }

  //Setup display
  #ifdef GP2X
  ScreenSurface = SDL_SetVideoMode(320, 480, 16, SDL_SWSURFACE);
  SDL_Surface *screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);
  #else
  SDL_Surface* scale;
  SDL_Surface* screen;
  if(argc==2)
  {
    if(strcmp(argv[1], "-z")==0)
    {
      doScale=1;
    } else if(strcmp(argv[1], "-d")==0)
    {
      doDump=1;
    } else if(!doScale)
    {
      printf("Usage:\n wizznic -d Dumps levelimages.\n wizznic -z Zoom to 640x480\n");
      return(-1);
    }

  }

  if(doScale)
  {
    scale = SDL_SetVideoMode(640,480,16, SDL_SWSURFACE);
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320,240,16, scale->format->Rmask,scale->format->Gmask,scale->format->Bmask,0xff000000);
  } else {
    scale = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
    screen = scale;
  }

  #endif
  //Open Joysticks (for wiz)
  if (SDL_NumJoysticks() > 0) SDL_JoystickOpen(0);

  #ifdef GP2X
  SDL_ShowCursor(SDL_DISABLE);
  /* Try and save a little battery */
  int mhz=350;
  WIZ_SetClock(mhz);
  #endif

  //Load fonts
  txtInit();

  //Load sounds
  if(!initSound())
  {
    printf("Couldn't init sound.\n");
    return(-1);
  }


  //Menu Graphics
  if(!initMenu())
  {
    printf("Couldn't load menu graphics.\n");
    return(-1);
  }

  //Init controls
  initControls();

  //Scan data/levels
  makeLevelList();

  #ifndef GP2X
  if(doDump)
  {
    dumplevelimages(screen);
    return(0);
  }
  #endif

  //Clear score, read maxLevel, highscore and volume
  initPlayer();

  //init starfield
  initStars(screen);

  int lastTick;
  while(state!=STATEQUIT)
  {
    lastTick=SDL_GetTicks();

    frameStart();
    runControls();

    switch(state)
    {
      case STATEPLAY:
        state = runGame(screen);
      break;

      case STATEMENU:
        state = runMenu(screen);
      break;

      case STATEEDIT:
        state=runEditor(screen);
      break;

      default:
        return(-1);
      break;
    }

   // drawFPS(screen);

    #ifdef GP2X
    WIZ_ShowVolume(screen);

    while(SDL_GetTicks()-lastTick < 20)
    {

    }

    //SDL_Flip(screen);
    {
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_LockSurface(ScreenSurface);
      int x, y;
      uint32_t *s = (uint32_t*)screen->pixels;
      uint32_t *d = (uint32_t*)ScreenSurface->pixels;
      for(y=0; y<240; y++){
        for(x=0; x<160; x++){
          *d++ = *s++;
        }
        d+= 160;
      }
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_UnlockSurface(ScreenSurface);
      SDL_Flip(ScreenSurface);
    }

    #else

    if(doScale)
    {
      int x,xx,y,yy;
      int r,g,b;
      for(y=0; y< 240; y++)
      {
        for(x=0; x < 320; x++)
        {
          readPixel(screen, x,y, &r,&g,&b);
          uint16_t c = SDL_MapRGB(scale->format,r,g,b);
          xx=x*2;
          yy=y*2;
          plotPixelu(scale, xx,yy, c);
          plotPixelu(scale, xx+1,yy, c);
          plotPixelu(scale, xx,yy+1, c);
          plotPixelu(scale, xx+1,yy+1, c);
        }
      }
    }

    //SDL_Flip(scale);
    {
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_LockSurface(ScreenSurface);
      int x, y;
      uint32_t *s = (uint32_t*)scale->pixels;
      uint32_t *d = (uint32_t*)ScreenSurface->pixels;
      for(y=0; y<240; y++){
        for(x=0; x<160; x++){
          *d++ = *s++;
        }
        d+= 160;
      }
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_UnlockSurface(ScreenSurface);
      SDL_Flip(ScreenSurface);
    }
    int t=SDL_GetTicks()-lastTick;
    if(t < 20)
    {
      SDL_Delay( 20 -t);
    }

    #endif


  }

  #ifdef GP2X
  WIZ_SetClock(533);
  #endif

  //Free screen
  SDL_FreeSurface(screen);
  //Free text
  txtQuit();

  SDL_Quit(); // Added for Dingoo A320 clean exit

  return(0);
}


