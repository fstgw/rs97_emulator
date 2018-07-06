#include "pixel.h"
#include "math.h"

void plotPixel(SDL_Surface* img, int x, int y, uint16_t col)
{
  //Bail if invalid position
  if(x < 0 || x > 319 || y < 0 || y > 239)
  {
    return;
  }
  *(uint16_t*)( (char*)(img->pixels)+img->pitch*y+2*x ) = col;
}

void plotPixelu(SDL_Surface* img, int x, int y, uint16_t col)
{
  *(uint16_t*)( (char*)(img->pixels)+img->pitch*y+2*x ) = col;
}

void readPixel(SDL_Surface* img, int x, int y, int* r, int* g, int* b)
{
  uint32_t col;
  col = *(uint16_t*)( (char*)(img->pixels)+img->pitch*y+img->format->BytesPerPixel*x );

  //Do expensive colorkeying
  *r = ((col & img->format->Rmask) >> img->format->Rshift)*8;
  *g = ((col & img->format->Gmask) >> img->format->Gshift)*4;
  *b = ((col & img->format->Bmask) >> img->format->Bshift)*8;


};

static float rot=0;

void waveImg(SDL_Surface* screen, SDL_Surface* img, int xx, int yy)
{

  int x, y; //In the source image
  int nx, ny; //new x/y value for px
  uint32_t col; //Color of pixel
  char r,g,b;


  float pxInc = 6.28318531/img->w;

  float yInc;

  rot-=(float)getTicks()/400;

  for(x=0; x < img->w; x++)
  {
    yInc = cos(rot+x*pxInc)*10;

    for(y=0; y < img->h; y++)
    {
      col = *(uint16_t*)( (char*)(img->pixels)+img->pitch*y+img->format->BytesPerPixel*x );

      //Do expensive colorkeying
      r = ((col & img->format->Rmask) >> img->format->Rshift);
      g = ((col & img->format->Gmask) >> img->format->Gshift);
      b = ((col & img->format->Bmask) >> img->format->Bshift);
      if(r!=0 && g!=255 && b!=255)
      {
        nx = x;
        ny = y;
        ny += yInc;
        plotPixel(screen, nx+xx,ny+yy, col);
      }
    }
  }
}
