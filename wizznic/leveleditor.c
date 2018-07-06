#include "leveleditor.h"
#include "cursor.h"
#include "board.h"
#include "draw.h"
#include "states.h"
#include "input.h"
#include "text.h"
#include "levels.h"
#include "list.h"
#include <stdio.h>

static playField pf;
static cursorType cur;
static int selBrick=1;
static char saveFile[32];
static int changed=0;
static char fileName[64];
static char buf[64];

void editorLoad(const char* fn)
{
  //Set filename
  editorFileName(fn);

  //Init cursor
  initCursor(&cur);
  //Load field
  loadField(&pf, fileName);

  initDraw(pf.bgFile, pf.tileFile);
  changed=0;
  selBrick=1;

}

void editorCleanUp()
{
  //Free board and graphics here
}

void editorFileName(const char* fn)
{
  changed=1;
  strcpy(fileName,fn);
}

int runEditor(SDL_Surface* screen)
{
  int x,y;

  //Handle movement
  if(getButton(C_UP))
  {
    resetBtn(C_UP);
    moveCursor(&cur, 0,DIRUP, 0);
  }

  if(getButton(C_DOWN))
  {
    resetBtn(C_DOWN);
    moveCursor(&cur, 0,DIRDOWN,0);
  }

  if(getButton(C_LEFT))
  {
    resetBtn(C_LEFT);
    moveCursor(&cur, DIRLEFT,0, 0);
  }

  if(getButton(C_RIGHT))
  {
    resetBtn(C_RIGHT);
    moveCursor(&cur, DIRRIGHT,0, 0);
  }

  if(getButton(C_BTNB))
  {
    resetBtn(C_BTNB);
    if(selBrick<8) selBrick++;
  }

  if(getButton(C_BTNA))
  {
    resetBtn(C_BTNA);
    if(selBrick>1) selBrick--;
  }

  if(getButton(C_BTNX))
  {
    resetBtn(C_BTNX);
    if(!pf.board[cur.x][cur.y])
      pf.board[cur.x][cur.y]=malloc(sizeof(brickType));

    pf.board[cur.x][cur.y]->type=selBrick;
    if(selBrick==STD)
    {
      boardSetWalls(&pf);
    }
    pf.board[cur.x][cur.y]->pxx=cur.x*20+boardOffsetX;
    pf.board[cur.x][cur.y]->pxy=cur.y*20+boardOffsetY;
    changed=1;
  }

  if(getButton(C_BTNY))
  {
    resetBtn(C_BTNY);
    if(pf.board[cur.x][cur.y])
    {
      free(pf.board[cur.x][cur.y]);
      pf.board[cur.x][cur.y]=0;
      changed=1;
    }

    boardSetWalls(&pf);

  }

  if(getButton(C_BTNSELECT))
  {
    resetBtn(C_BTNSELECT);
    FILE *f = fopen(fileName, "w");
    int x,y;
    fputs("Unknown Author\n",f);
    fputs("360\n",f);
    fputs(pf.bgFile, f);
    fputc('\n',f);
    fputs(pf.tileFile, f);

    if(f)
    {
      for(y=0; y < FIELDSIZE; y++)
      {
        fputc('\n',f);
        for(x=0; x < FIELDSIZE; x++)
        {
          if(pf.board[x][y])
          {
            fprintf(f,"%i", pf.board[x][y]->type);
          } else {
            fputc('0',f);
          }
        }
      }
      fputc('\n',f);
      changed=0;
      fclose(f);

      addUserLevel(fileName);
    }
  }

  if(getButton(C_BTNMENU))
  {
    editorCleanUp();
    return(STATEMENU);
  }

  draw(&cur, &pf, screen);
  if(!changed)
  {
    sprintf(buf, "Saved", fileName);
  } else {
    sprintf(buf, "Not Saved", fileName);
  }

  txtWriteCenter(screen, FONTSMALL,"Status:", 45,200);
  txtWriteCenter(screen, FONTSMALL,buf, 45,210);

  txtWriteCenter(screen, FONTSMALL,fileName, 160,230);
  txtWriteCenter(screen, FONTSMALL,"X:Put Y:Del Start:Exit Select:Save", 160,0);

  txtWriteCenter(screen, FONTSMALL, "Brick",45,20);
  drawBrick(screen, selBrick,35,35);
  if(selBrick>1)
    txtWrite(screen, FONTSMALL,"<A", 35-18-3,38);

  if(selBrick< 8)
    txtWrite(screen, FONTSMALL,"B>", 55+3,38);

  return(STATEEDIT);
}
