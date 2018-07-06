#ifndef _TSPRITEENEMIGO_
#define _TSPRITEENEMIGO_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSpriteEnemigo);

TSpriteEnemigo::TSpriteEnemigo(TMAImageBank *bank):TMASprite(bank)
{
}

void TSpriteEnemigo::getCollisionRectangle(TMARectangle& r) 
{
    r.setBounds(position);
    
    #ifdef SMALL_GAME
        r.width-=4;
        r.height-=2;
        r.x +=2;
        r.y +=1;
    #else
        r.width-=8;
        r.height-=4;
        r.x +=4;
        r.y +=2;
    #endif
}

#endif
