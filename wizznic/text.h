#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <SDL/SDL.h>

#define NUMFONTS 2
#define FONTMEDIUM 1
#define FONTSMALL 0

#include "ticks.h"
void txtInit(); //ret 0 err
void txtQuit();
void txtWrite( SDL_Surface* scr,int font, const char* txt, int x, int y);
void txtWriteCenter( SDL_Surface* scr,int fontNum, const char* txt, int x, int y);

#endif // TEXT_H_INCLUDED
