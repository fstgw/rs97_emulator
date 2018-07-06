#ifndef FPSCOUNTER_H_INCLUDED
#define FPSCOUNTER_H_INCLUDED

#include <SDL/SDL.h>

void frameStart();

int getTicks();
int getTimeSinceFrameStart();

void drawFPS(SDL_Surface* scr);

#endif // FPSCOUNTER_H_INCLUDED
