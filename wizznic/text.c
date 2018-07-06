#include "text.h"
#include "sprite.h"
#include "math.h"
static SDL_Surface* txtSurf[NUMFONTS]; //3 fonts
static spriteType* txtSprites[NUMFONTS][91];

void txtInit()
{
  int fontNum;
  for(fontNum=0; fontNum < NUMFONTS; fontNum++)
  {
    char tempName[32];
    sprintf(tempName, "data/charmap%i.png", fontNum);
    txtSurf[fontNum] = loadImg( tempName );
    if(txtSurf!=NULL)
    {
      int i;
      int xpos=0;
      int ypos=0;
      int linlen=0;
      for(i=0; i < 91; i++)
      {
        txtSprites[fontNum][i] = cutSprite(txtSurf[fontNum],xpos,ypos,9*(fontNum+1),12*(fontNum+1));
        xpos+=9*(fontNum+1);
        linlen++;
        if(linlen==16)
        {
          linlen=0;
          ypos += 12*(fontNum+1);
          xpos=0;
        }
      }
    }
  }

}

void txtQuit()
{
  int fn;
  for(fn=0; fn < NUMFONTS; fn++)
  {
    SDL_FreeSurface(txtSurf[fn]);
    int i;

    for(i=0; i < 91; i++)
    {
      free(txtSprites[fn][i]);
    }
  }
}

void txtWrite( SDL_Surface* scr,int fontNum, const char* txt, int x, int y)
{
  int px=x;
  int py=y;
  int pos=0;
  char c;
  c = txt[pos];

  while( c != '\0')
  {
    pos++;
    if(c=='\n')
    {
      py+=12*(fontNum+1);
      px=x-8*(fontNum+1);
    }
    else if(c!=' ')
    {
      drawSprite(scr, txtSprites[fontNum][(int)c-32],px,py);
    }
    c = txt[pos];
    px+=9*(fontNum+1);
  }
}

void txtWriteCenter( SDL_Surface* scr,int fontNum, const char* txt, int x, int y)
{
  //Get width
  int pos=0;
  char c = txt[pos];
  while(c != '\0')
  {
    pos++;
    c = txt[pos];
  }
  //pos--; //The last was a \0
  int len = 9*(fontNum+1)*pos;

  x -= len/2;
  txtWrite(scr,fontNum,txt,x,y);
}

/*void txtTest( SDL_Surface* scr, int font )
{
  int i;
  int px=0;
  int py=0;
  for(i=0; i < 90; i++)
  {
    drawSprite(scr, txtSprites[font][i],px,py);
    px+=20;
    if(px+20 > scr->w)
    {
      px=0;
      py +=20;
    }
  }
}**/

void txtWave( SDL_Surface* scr, int fontNum, const char* txt, int x, int y, float* rot)
{
  //dec rot
  *rot -= (float)getTicks()/200.0;
  //For each char:
  float amp=6;
  int px=x;
  int py=y;
  int pos=0;
  int len=strlen(txt);
  float chInc = 6.28318531/len;
  px = x - (9*(fontNum+1)*len)/2;
  char c;
  c = txt[pos];

  while( c != '\0')
  {
    pos++;
    if(c=='\n')
    {
      py+=12*(fontNum+1);
      px=x-9*(fontNum+1);
    }
    else if(c!=' ')
    {
      drawSprite(scr, txtSprites[fontNum][(int)c-32],px,py+(sin(*rot+(pos*chInc))*amp));
    }
    c = txt[pos];
    px+=9*(fontNum+1);
  }


}
