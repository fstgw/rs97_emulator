#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include <SDL/SDL.h>

void plotPixel(SDL_Surface* img, int x, int y, uint16_t col);
void plotPixelu(SDL_Surface* img, int x, int y, uint16_t col);
void readPixel(SDL_Surface* img, int x, int y, int* r, int* g, int* b);

void waveImg(SDL_Surface* screen, SDL_Surface* img, int x, int y);
#endif // PIXEL_H_INCLUDED
