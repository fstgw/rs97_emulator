#include "levelselector.h"
#include <math.h>
#include "text.h"
#include "pixel.h"
#include "ticks.h"

static int lastSelected = -1;
static SDL_Surface* lvlPreviewImg;
static char buf[32];
static char buf2[32];
static char buf3[64];

void levelSelector(SDL_Surface* screen, int l, int stats)
{

  if(lastSelected != l)
  {
    //Unload the previously loaded level-preview
    if(lastSelected != -1)
    {
      SDL_FreeSurface(lvlPreviewImg);
    }
    //Load the level-preview for the currently selected image
    printf("Loading file: %s\n",levelInfo(l)->imgFile);
    lvlPreviewImg=loadImg(levelInfo(l)->imgFile);

    lastSelected=l;
    sprintf(buf, "Level %i", l);
    sprintf(buf2, "Time %i:%01.2i", levelInfo(l)->time/60, levelInfo(l)->time%60 );
    sprintf(buf3,"By: %s", levelInfo(l)->author);
  }

  if(l+1 > getNumLevels()) stats=2;

  drawPreviewImg(screen, lvlPreviewImg, stats);

  if(stats!=2)
  {
    txtWriteCenter(screen, FONTMEDIUM, buf, 160,120-12 );
    txtWriteCenter(screen, FONTSMALL, buf3, 160,120+12 );
    if(stats)
    {
      txtWriteCenter(screen, FONTSMALL, buf2, 160,120+36 );
    } else if(stats) {
      txtWriteCenter(screen, FONTSMALL, "Locked!", 160,120+36 );
    }
  }
}



static float z=200.0;
static float rot=0.0;
void drawPreviewImg(SDL_Surface* screen, SDL_Surface* img, int stats)
{
  int x, y; //In the source image
  int offSetX=160-(55*z/100);
  int offSetY=120-(55*z/100);
  int nx, ny; //new x/y value for px
  uint32_t col; //Color of pixel
  char r,g,b;
  uint32_t grey;

  float pxInc = 6.28318531/110.0;

  float xInc;

  rot-=(float)getTicks()/200;


  for(y=0; y < 110; y++)
  {
    xInc = cos(rot+y*pxInc)*1000;

    for(x=0; x < 110; x++)
    {
      col = *(uint16_t*)( (char*)(img->pixels)+img->pitch*y+img->format->BytesPerPixel*x );

      //Do expensive colorkeying
      r = ((col & img->format->Rmask) >> img->format->Rshift);
      g = ((col & img->format->Gmask) >> img->format->Gshift);
      b = ((col & img->format->Bmask) >> img->format->Bshift);
      if(r!=0 && g!=255 && b!=255)
      {
        //Do b/w
        if(!stats)
        {
          grey = (r+g+b)/3;
          col = (grey << img->format->Rshift) | (grey << img->format->Gshift)<<1 | (grey << img->format->Bshift);
        }


        nx = x*(int)z;
        ny = y*(int)z;
        nx += xInc;
        nx /= 100;
        ny /= 100;

        plotPixel(screen, nx+offSetX,ny+offSetY, col);
      }
    }
  }
}





