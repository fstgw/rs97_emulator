#include "draw.h"

struct boardGraphics_t graphics;

int initDraw(const char* bgFile, const char* tileFile)
{
  char tempStr[64];
  int i,x,y;

  //Background image
  sprintf(tempStr, "data/themes/%s.png", bgFile);
  graphics.boardImg = loadImg( tempStr );
  if(!graphics.boardImg)
  {
    cleanUpDraw();
    printf("Error: Couldn't load %s\n", tempStr);
    return(0);
  }

  //Tileset
  sprintf(tempStr, "data/themes/%s.png", tileFile);
  graphics.tileImg = loadImg( tempStr );
  if(!graphics.tileImg)
  {
    cleanUpDraw();
    printf("Error: Couldn't load %s\n", tempStr);
    return(0);
  }

  //Extra walls, if they exist, if they don't, default to tile 6 (from 0) in tiles.
  sprintf(tempStr, "data/themes/%s-walls.png", tileFile);
  graphics.wallImg = loadImg( tempStr );
  int r,c; //rows, column, sprite index
  i=0;
  for(r=0; r < 5; r++)
  {
    for(c=0; c < 3; c++)
    {
      if(graphics.wallImg)
      {
        //Cut out from sheet
        x=c*20;
        y=r*20;
        graphics.walls[i] = cutSprite(graphics.wallImg, x,y, 20, 20);
      } else {
        //Default to tile 6 in tileset
        graphics.walls[i] = cutSprite(graphics.tileImg, 20*6, 0, 20, 20);
      }
      i++;
    }
  }
  //Middle-free is 15 = default tile 6.
  graphics.walls[15] = cutSprite(graphics.tileImg, 20*6, 0, 20, 20);

  //Explosions, reuse R as frame number index
  for(i=0; i < 5; i++)
  {
    //Open explosion
    sprintf(tempStr, "data/themes/%s-expl%i.png", tileFile, i);
    graphics.explImg[i] = loadImg( tempStr );
    if(!graphics.explImg[i]) printf("Couldn't open %s\n",tempStr);
    //Cut
    for(r=0; r < 16; r++)
    {
      x=r*30;
      if(graphics.explImg[i])
      {
        graphics.expl[i][r] = cutSprite(graphics.explImg[i], x,0,30,30);
      } else {
        //default to expl0
        graphics.expl[i][r] = cutSprite(graphics.explImg[0],x,0,30,30);
      }
    }
  }

  //Cursor
  graphics.curImg = loadImg( "data/cursor.png" );

  if(!graphics.curImg)
  {
    cleanUpDraw();
    printf("Error: Couldn't load %s\n", tempStr);
    return(0);
  }
  graphics.curSpr = cutSprite(graphics.curImg, 0, 0, graphics.curImg->w,graphics. curImg->h);


  //Cut sprites
  for(i=0; i < NUMTILES; i++)
  {
    //Cut
    x = i*20;
    graphics.tiles[i] = cutSprite(graphics.tileImg, x, 0, 20,20);
  }

  //Load countdown
  graphics.countDownImg = loadImg( "data/countdown.png" );
  if(!graphics.countDownImg)
  {
    printf("Error: couldn't load data/countdown.png");
    return(0);
  }
  //Cut countdown
  for(i=0; i < 4; i++)
  {
    graphics.countDownSpr[i] = cutSprite(graphics.countDownImg, 0,i*60, 140,60);
  }

  return(1);
}

void cleanUpDraw()
{
  int i,ii;
  //Board image
  if(graphics.boardImg) SDL_FreeSurface(graphics.boardImg);

  //Tile image
  if(graphics.tileImg) SDL_FreeSurface(graphics.tileImg);
  //Tile sprites
  for(i=0; i < NUMTILES; i++)
  {
    if(graphics.tiles[i]) free(graphics.tiles[i]);
  }

  //Cursor image
  if(graphics.curImg) SDL_FreeSurface(graphics.curImg);
  //Cursor sprite
  if(graphics.curSpr) free(graphics.curSpr);

  //Wall image
  if(graphics.wallImg) SDL_FreeSurface(graphics.wallImg);
  //Wall sprites
  for(i=0; i < 16; i++)
  {
    if(graphics.walls[i]) free(graphics.walls[i]);
  }

  //Explosion
  for(i=0; i < 5; i++)
  {
    //image
    if( graphics.explImg[i] ) SDL_FreeSurface( graphics.explImg[i] );
    //sprites
    for(ii=0; ii < 16; ii++)
    {
      if(graphics.expl[i][ii]) free(graphics.expl[i][ii]);
    }
  }

  //Countdown
  if(graphics.countDownImg) SDL_FreeSurface(graphics.countDownImg);
  for(i=0; i < 4; i++)
  {
    if(graphics.countDownSpr[i]) free(graphics.countDownSpr[i]);
  }
}

void drawDisableCursor()
{
  graphics.curSpr = 0;
}


void draw(cursorType* cur, playField* pf, SDL_Surface* screen)
{
  int x,y;

  SDL_BlitSurface(graphics.boardImg , NULL, screen, NULL );

  //Draw static bricks
  for(y=0; y < FIELDSIZE; y++)
  {
    for(x=0; x < FIELDSIZE; x++)
    {
      //Bricks
      if(pf->board[x][y] && pf->board[x][y]->type != RESERVED)
      {
        //printf("X:%i Y:%i Type: %i\n",x,y,pf->board[x][y]->type);
        //Is it a wall?
        if(pf->board[x][y]->type == STD)
        {
          //printf("I want to draw %i for(%i,%i) it has sprite: %i\n",pf->board[x][y]->wall,x,y,graphics.walls[pf->board[x][y]->wall]);
          drawSprite(screen, graphics.walls[pf->board[x][y]->wall], pf->board[x][y]->pxx, pf->board[x][y]->pxy);
        } else
        if(graphics.tiles[pf->board[x][y]->type])
        {
          drawSprite(screen, graphics.tiles[pf->board[x][y]->type], pf->board[x][y]->pxx, pf->board[x][y]->pxy);
        }
      } /*else if( pf->board[x][y] && pf->board[x][y]->type == RESERVED )
      {
        drawSprite(screen, graphics.tiles[6], x*20+90, y*20+10);
      }*/ else {
        //Background
        drawSprite(screen, graphics.tiles[0], x*20+90, y*20+10);
      }
    }
  }

  //Draw moving bricks
  listItem* t=pf->movingList;
  brickType* b;
  while(t=t->next)
  {
    b=(brickType*)t->data;
    drawSprite(screen, graphics.tiles[b->type], b->pxx, b->pxy);
  }

  //Draw dying bricks, animation?
  t=pf->removeList;
  while(t=t->next)
  {
    b=(brickType*)t->data;
    //Draw base brick if time enough left
    if(b->tl > 250)
    {
      drawSprite(screen, graphics.tiles[b->type], b->pxx, b->pxy);
    }

    int explFrame = 16*(500-b->tl)/500;
    if( graphics.expl[b->type-1][explFrame] )
    {
      drawSprite(screen, graphics.expl[b->type-1][explFrame], b->pxx-5, b->pxy-5);
    }
  }

  //Cursor
  updateCursor(cur);
  drawSprite(screen, graphics.curSpr, cur->px, cur->py);

}

void drawShowCountDown(SDL_Surface* screen,int i)
{
  int r,g,b,t;
  int x,y;

  for(y=0; y < 240; y++)
  {
    for(x=0; x < 320; x++)
    {
      readPixel(screen, x,y, &r,&g,&b);
      r /= i+1;
      g /= i+1;
      b /= i+1;
      plotPixel(screen, x,y, SDL_MapRGB(screen->format, r, g, b));
    }
  }
  drawSprite(screen, graphics.countDownSpr[i], 160-140/2,120-60/2);
}

void drawBrick(SDL_Surface* screen, int brickNum, int x, int y)
{
  drawSprite(screen, graphics.tiles[brickNum], x,y);
}
