#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include <SDL/SDL.h>
#include "defs.h"
#include "board.h"
#include "cursor.h"
#include "sprite.h"
#include "list.h"

struct boardGraphics_t
{
  SDL_Surface* boardImg;
  SDL_Surface* tileImg;
  SDL_Surface* curImg;
  SDL_Surface* wallImg; //If theme uses extra wall tiles.
  SDL_Surface* explImg[5]; //Brick destroy animations, either one pr tile, or all defaults to 0.
  SDL_Surface* countDownImg;
  spriteType* curSpr;
  spriteType* tiles[NUMTILES];
  spriteType* expl[5][16]; //16 frame animation for each type of brick
  spriteType* walls[16]; //Extra walls
  spriteType* countDownSpr[4]; //Countdown graphics 3,2,1,start
};

int initDraw(const char* bgFile, const char* tileFile);
void cleanUpDraw();
void draw(cursorType* cur, playField* pf, SDL_Surface* screen);
void drawShowCountDown(SDL_Surface* screen, int i);

//For editor
void drawBrick(SDL_Surface* screen, int brickNum, int x, int y);

#endif // DRAW_H_INCLUDED
