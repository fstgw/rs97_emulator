#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL/SDL.h>
#include "sprite.h"
#include "text.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "stars.h"
#include "leveleditor.h"

int initMenu(); //Loads menu graphics
int runMenu();
void setMenu(int mstate);

#endif // MENU_H_INCLUDED
