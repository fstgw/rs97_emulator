#include "board.h"

#include <stdio.h>


static int isWall(playField* pf, int x, int y)
{
  if(x < 0) return(0);
  if(x == FIELDSIZE) return(0);
  if(y < 0) return(0);
  if(y == FIELDSIZE) return(0);

  if(!pf->board[x][y]) return(0);
  if(pf->board[x][y]->type==6) return(1);
  return(0);
}

void setWallType(playField* pf, int x, int y)
{
        //see if has neighbours:
        //Top-Left
        if( !isWall(pf, x-1,y) && !isWall( pf, x, y-1) && isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 0;
        }
        //Top
        if( isWall(pf, x-1,y) && !isWall( pf, x, y-1) && isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 1;
        }
        //Top-Right
        if( isWall(pf, x-1,y) && !isWall( pf, x, y-1) && !isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 2;
        }
        //Left
        if( !isWall(pf, x-1,y) && isWall( pf, x, y-1) && isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 3;
        }
        //Middle
        if( isWall(pf, x-1,y) && isWall( pf, x, y-1) && isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 4;
        }
        //Right
        if( isWall(pf, x-1,y) && isWall( pf, x, y-1) && !isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 5;
        }
        //LeftBot
        if( !isWall(pf, x-1,y) && isWall( pf, x, y-1) && isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 6;
        }
        //Bot
        if( isWall(pf, x-1,y) && isWall( pf, x, y-1) && isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 7;
        }
        //RightBot
        if( isWall(pf, x-1,y) && isWall( pf, x, y-1) && !isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 8;
        }
        //Left,Top,Right
        if( !isWall(pf, x-1,y) && !isWall( pf, x, y-1) && !isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 9;
        }
        //Left, top, bot
        if( !isWall(pf, x-1,y) && !isWall( pf, x, y-1) && isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 10;
        }
        //Top, right, bot
        if( isWall(pf, x-1,y) && !isWall( pf, x, y-1) && !isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 11;
        }
        //Left, bot, right
        if( !isWall(pf, x-1,y) && isWall( pf, x, y-1) && !isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 12;
        }
        //Vert
        if( !isWall(pf, x-1,y) && isWall( pf, x, y-1) && !isWall(pf, x+1,y) && isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 13;
        }
        //Horiz
        if( isWall(pf, x-1,y) && !isWall( pf, x, y-1) && isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall = 14;
        }

        //Middle - clear
        if( !isWall(pf, x-1,y) && !isWall( pf, x, y-1) && !isWall(pf, x+1,y) && !isWall(pf,x,y+1) )
        {
          pf->board[x][y]->wall=15;
        }
}

void boardSetWalls(playField* pf)
{
  int x,y;
  for(x=0; x < FIELDSIZE; x++)
  {
    for(y=0; y < FIELDSIZE; y++)
    {
      if(pf->board[x][y] && pf->board[x][y]->type==STD)
      {
        setWallType(pf,x,y);
      }
    }
  }
}

int loadField(playField* pf, const char* file)
{
  FILE *f = fopen(file, "r");
  if(!f)
  {
    printf("Board: couldn't open '%s'\n",file);
  }

  char temp[32];
  //First lines are:
  fgets( temp, 32, f); //Just read the line, and discard it.

  // time in seconds
  fgets( temp, 32, f);
  pf->timeLeft=atoi( temp );
  // background image
  fgets( pf->bgFile, 32, f );
  pf->bgFile[strlen(pf->bgFile)-1] = '\0';
  // tileset
  fgets( pf->tileFile, 32, f );
  pf->tileFile[strlen(pf->tileFile)-1] = '\0';

  //For atoi hack
  temp[1] = '\0'; //Terminate string after first byte

  //For checking that level var correctly loaded
  int bytes=0;
  //Read each byte into the field
  int c=0,x=0,y=0;
  do {
    c = fgetc(f);

    if(c=='\n')
    {
        y++;
        x=0;
        if(y == FIELDSIZE)
        {
          break;
        }
    } else if(c=='\r')
    {
      //Ignore windows wanting to run on a typewriter.
    } else {
      if(x==FIELDSIZE) { return(0); } //Error loading level, bail before accesing invalid index.
      temp[0]=(char)c;
      if(c !='0')
      {
        pf->board[x][y] = malloc( sizeof( brickType ) );
        pf->board[x][y]->type = atoi( temp );
        pf->board[x][y]->pxx = x*brickSize+boardOffsetX;
        pf->board[x][y]->pxy = y*brickSize+boardOffsetY;
        pf->board[x][y]->dir=0;
        pf->board[x][y]->checked=0;
        pf->board[x][y]->curLock=0;
        pf->board[x][y]->sx = x;
        pf->board[x][y]->sy = y;
        pf->board[x][y]->dx = x;
        pf->board[x][y]->dy = y;
        pf->board[x][y]->tl  = MOVERCOUNTDOWN;
      } else {
        pf->board[x][y] = 0;
      }
      bytes++;
      x++;
    }

  } while( c != EOF );

  //Close the file
  fclose(f);

  pf->movingList = initList();
  pf->removeList = initList();

  pf->blocker = malloc(sizeof(brickType));
  pf->blocker->type=RESERVED;

  //Figure out which tile to use for each wall (int 6)
  boardSetWalls(pf);

  return(1);
}

void freeField(playField* pf)
{
  int x,y;
  for(y=0; y < FIELDSIZE; y++)
  {
    for(x=0; x < FIELDSIZE; x++)
    {
      if(pf->board[x][y])
      {
        //We don't want to free the blocker more than once.
        if(pf->board[x][y]->type!=RESERVED)
        {
          free(pf->board[x][y]);
        }
        pf->board[x][y]=0;
      }
    }
  }
  free(pf->blocker);
  //Clear the lists
  freeList(pf->movingList);
  freeList(pf->removeList);
}

int moveBrick(playField* pf, int x, int y, int dirx, int diry, int block, int speed)
{
  //Destination x
  int dx = x+dirx;
  int dy = y+diry;

  //Trying to move out of field?
  if( dx < 0 || dx == FIELDSIZE ) return(0);
  if( dy < 0 || dy == FIELDSIZE ) return(0);


  if(!pf->board[x][y]) return(0);


  //If destination is empty
  if( !pf->board[dx][dy] || (block==NOBLOCK && (!pf->board[dx][dy] || pf->board[dx][dy]->type==RESERVED)) )
  {
      //Set destination
      pf->board[x][y]->dx=dx;
      pf->board[x][y]->dy=dy;

      //Set source
      pf->board[x][y]->sx=x;
      pf->board[x][y]->sy=y;

      //If caller is player move code:
      if(block==CURLOCK)
      {
        pf->board[x][y]->curLock=1;
      }

      //Set moving speed
      pf->board[x][y]->moveXspeed=speed*dirx;
      pf->board[x][y]->moveYspeed=speed*diry;

      //add to moving
      listAddData(pf->movingList, (void*)pf->board[x][y]);

      pf->board[dx][dy]=pf->blocker;
      pf->board[x][y]=pf->blocker;


    return(1);
  }

  return(0);
}


//BUG: This function will move a mover which is getting atop or below another.
//Don't have movers that can touch.
static int vertMover(playField* pf,int x, int y, int dir)
{
  //Outside bounds
  if(y+dir < 0 || y+dir == FIELDSIZE) return(0);
  //Abort if it's not a brick, or a mover.
  if(!isBrick(pf->board[x][y]) && !isMover(pf->board[x][y]) ) return(0);

  //Found a space
  if( !pf->board[x][y+dir] )
  {
     moveBrick(pf,x,y,0,dir, NOBLOCK, VERTMOVERSPEED);
     return(1);
  } else if(vertMover(pf, x, y+dir, dir))
  {
    moveBrick(pf,x,y,0,dir, NOBLOCK, VERTMOVERSPEED);
    return(1);
  }

  return(0);
}

static int bricksOnTop(playField* pf, int x, int y)
{
  int num=0;
  while(1)
  {
    y--;
    if(y < 0) return(num);
    if(pf->board[x][y] && isBrick(pf->board[x][y]))
      num++;
      else
    return(num);
  }

}

static void horizMover(playField* pf, int x, int y, int dir)
{
  //Out of bounds
  if(x+dir<FIELDSIZE && x+dir>-1)

  {
    //Can it move to the side?
    if( !pf->board[x+dir][y] )
    {
      //Move
      moveBrick(pf,x,y,dir,0, DOBLOCK, HORIZMOVERSPEED);

      //Move the ones on top (if possible)
      int stop=0;
      while( !stop )
      {

        if(x+dir < FIELDSIZE && x+dir > -1)
        {
          y--;
          if( y > -1 && pf->board[x][y] && isBrick(pf->board[x][y]) )
          {
            //Can we move that brick one to the dir?
            if( !pf->board[x+dir][y] )
            {
              moveBrick(pf,x,y,dir,0, DOBLOCK, HORIZMOVERSPEED);
            }
          } else { stop=1; }

        } else { stop=1; }

      }

    } else { //Switch direction
      pf->board[x][y]->dir = !pf->board[x][y]->dir;
    }
  } else {
    pf->board[x][y]->dir = !pf->board[x][y]->dir;
  }
}

void simField(playField* pf, cursorType* cur)
{
  int x,y;

  //Update moving bricks
  listItem* li=pf->movingList;
  brickType* b;
  x=0;
  while( li = li->next )
  {
    x++;
   // printf("Bricks in list: %i\n",x);
    //Because I'm drunk enough
    b=(brickType*)li->data;

    //Do we need to move it?
    int deltaX= (b->dx*brickSize+boardOffsetX) - b->pxx ;
    int deltaY= (b->dy*brickSize+boardOffsetY) - b->pxy ;

    if(deltaX != 0 || deltaY !=0)
    {
      //Doing this lock to only move one dir at a time
      if(deltaX != 0)
      {
        b->pxx +=b->moveXspeed;
      } else {
        if(deltaY !=0 )
         b->pxy +=b->moveYspeed;
      }
      //Is cursor attached?
      if(cur->lock && b->curLock)
      {
        //Update cursor
        cur->px=b->pxx-4;
        cur->py=b->pxy-4;
      } else {
        b->curLock=0;
      }
    //  printf("Dx:%i X:%i Dy:%i Y:%i\n",deltaX,b->pxx, deltaY, b->pxy);
    } else {

      if(cur->lock && b->curLock)
      {
        cur->x=b->dx;
        cur->y=b->dy;
        cur->dx=b->dx;
        cur->dy=b->dy;
      }
      if(!cur->lock)
        b->curLock=0; //Release cursor from brick no matter what

      //Put it down:
      pf->board[ b->dx ][ b->dy ] = b;
      //Clear source
      pf->board[ b->sx ][ b->sy ] = 0;

      //Remove brick from moving list
      listRemoveItem( pf->movingList, li );
    }
  }

  //Static bricks
  for(y=FIELDSIZE-1; y > -1; y--)
  {
    for(x=0; x < FIELDSIZE; x++)
    {
      if( pf->board[x][y] && !pf->board[x][y]->checked)
      {
        pf->board[x][y]->checked=1;

        //Is it a brick
        if( isBrick(pf->board[x][y]) )
        {
          //Cursor locked on it?
          if( cur->lock && cur->x == x && cur->y == y )
          {
            pf->board[x][y]->curLock=1;
          }
          //Falling?
          if( y+1 < FIELDSIZE && !pf->board[x][y+1] )
          {
            //Move down
            moveBrick(pf, x, y, 0, +1, DOBLOCK, FALLINGSPEED);
          }
        }

        //Is it a mover
        if(isMover(pf->board[x][y]))
        {
          //Horiz mover?
          if(pf->board[x][y]->type == MOVERHORIZ)
          {
            //Moving right?
            if(pf->board[x][y]->dir)
            {
              horizMover(pf, x,y, 1);
            } else {
              horizMover(pf, x,y, -1);
            }
          } else if(pf->board[x][y]->type== MOVERVERT)
          {
            //Vertical mover
            if(pf->board[x][y]->dir)
            {
              //Moving up
              if(!vertMover(pf,x,y,-1))
              {
                pf->board[x][y]->tl -= getTicks();
                if(pf->board[x][y]->tl < 1)
                {
                  pf->board[x][y]->dir = 0;
                  pf->board[x][y]->tl  = MOVERCOUNTDOWN;
                }
              }
            } else {
              int numOnTop = bricksOnTop(pf,x,y);
              if(!vertMover(pf,x,y-numOnTop, 1))
              {
                pf->board[x][y]->tl -= getTicks();
                if(pf->board[x][y]->tl < 1)
                {
                  pf->board[x][y]->dir = 1;
                  pf->board[x][y]->tl  = MOVERCOUNTDOWN;
                }
              }
            }
          }
        } //Mover

      }
    }
  }
  for(y=FIELDSIZE-1; y > -1; y--)
  {
    for(x=0; x < FIELDSIZE; x++)
    {
      if(pf->board[x][y]) pf->board[x][y]->checked=0;
    }
  }

}

int isBrick(brickType* b)
{
  if( b->type < BRICKSBEGIN || b->type > BRICKSEND ) return(0);
  return(1);
}

int doRules(playField* pf)
{
  int x,y;
  int removed=0;
  int bricksLeft=0;

  //Count moving bricks
  listItem* li=pf->movingList;
  brickType* b;
  while( li = li->next )
  {
    bricksLeft++;
  }

  for(y=FIELDSIZE-1; y > -1; y--)
  {
    for(x=0; x < FIELDSIZE; x++)
    {
      if(!isBrickFalling(pf,x,y))
      {
        //Is brick, it will only remove itself, this avoids multiple entries of the same brick.
        if(pf->board[x][y] && isBrick(pf->board[x][y]))
        {
          bricksLeft++;
          //On top
          if(y > 0 && pf->board[x][y-1] && pf->board[x][y-1]->type == pf->board[x][y]->type && !isBrickFalling(pf,x,y-1) )
          {
            pf->board[x][y]->dir=1;
            listAddData(pf->removeList, (void*)pf->board[x][y]);
            //pf->board[x][y]=0;
         } else
          //Below
          if(y+1 < FIELDSIZE && pf->board[x][y+1] && pf->board[x][y+1]->type == pf->board[x][y]->type && !isBrickFalling(pf,x,y+1) )
          {
            pf->board[x][y]->dir=1;
            listAddData(pf->removeList, (void*)pf->board[x][y]);
            //pf->board[x][y]=0;
          } else
          //Left
          if(x > 0 && pf->board[x-1][y] && pf->board[x-1][y]->type == pf->board[x][y]->type && !isBrickFalling(pf,x-1,y) )
          {
            pf->board[x][y]->dir=1;
            listAddData(pf->removeList, (void*)pf->board[x][y]);
            //pf->board[x][y]=0;
          } else
          //Right
          if(x+1 < FIELDSIZE && pf->board[x+1][y] && pf->board[x+1][y]->type == pf->board[x][y]->type && !isBrickFalling(pf,x+1,y))
          {
            pf->board[x][y]->dir=1;
            listAddData(pf->removeList, (void*)pf->board[x][y]);
            //pf->board[x][y]=0;
          }

        } //A brick
      } //Not falling
    }
  }
  //Remove ones that need removed
  li=pf->removeList;
  while(li=li->next)
  {
    //Count dying bricks as alive untill they are really removed
    bricksLeft++;
    b=(brickType*)li->data;
    if(b->dir)
    {
      sndPlayOnce(SND_BRICKBREAK,b->pxx);
//      sndPlay(SND_BRICKBREAK, b->pxx);
      b->dir=0;
      b->tl=500;
      //Reserve, to prevent bricks from falling into the animation
      pf->board[b->dx][b->dy]=pf->blocker;
    } else {
      b->tl -= getTicks();

      if(b->tl < 1)
      {
        removed++;
        //Unreserve
        pf->board[b->dx][b->dy]=0;
        //Dealloc the brick
        free(b);
        //Remove from list
        listRemoveItem(pf->removeList, li);
      }
    }
  }

  if(removed)
    return(removed);

  if(!bricksLeft)
    return(-1);

  return(0);
}

int isBrickFalling(playField* pf, int x, int y)
{
  if(y+1 < FIELDSIZE)
  {
    if( !pf->board[x][y+1] || pf->board[x][y+1]->type==RESERVED )
    {
      return(1);
    }
  }
  return(0);
}


int isMover(brickType* b)
{
  if(!b) return(0);
  if(b->type==MOVERHORIZ||b->type==MOVERVERT) return(1);
  return(0);
}
