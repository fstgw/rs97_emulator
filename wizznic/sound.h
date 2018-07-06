#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SDL/SDL.h>

#define SND_CLICK 0
#define SND_MENUMOVE 1
#define SND_BRICKMOVE 2
#define SND_BRICKLAND 3
#define SND_BRICKBREAK 4
#define SND_BRICKGRAB 6
#define SND_SCORECOUNT 7
#define SND_ROCKETBOOM 8
#define SND_ROCKETLAUNCH 9
#define SND_COUNTDOWNTOSTART 10
#define SND_START 11
#define SND_TIMEOUT 12
#define SND_VICTORY 13
#define NUMSAMPLES 14


int initSound();
int loadSamples(); //Loads all samples for the game
void sndPlay(int sample, int posX);

#endif // SOUND_H_INCLUDED
