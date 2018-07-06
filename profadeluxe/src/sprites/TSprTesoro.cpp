#ifndef _TSCROLLTESORO_
#define _TSCROLLTESORO_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprTesoro);

TSprTesoro::TSprTesoro():TMASprite(NULL)
{
    bmp=NULL;
    invalidate();
}

void TSprTesoro::init(TMAGameMap& map,int banco,int grafico,int posx,int posy,int vel,int p_pantalla)
{
    if (vel>1) vel/=_REDUCE;
    velocidad = vel;
    bmp = map.getGraphBank(banco)->getImage(grafico);
    ii_posy = 0;
    position.x = posx * _TileAX;
    position.y = posy * _TileAY;
    position.width = bmp->getWidth();
    position.height = bmp->getHeight();
    ii_pantalla=-p_pantalla;
    validate();
};

void TSprTesoro::animate()
{
    ii_posy+= velocidad;
    if (ii_posy >= position.height) 
    {
        invalidate();
        ii_pantalla = -ii_pantalla;
    }
}

bool TSprTesoro::draw(TMABitmap& buff)
{
    if (bmp!=NULL)
    {
        buff.draw(bmp,0,ii_posy,position.width,position.height - ii_posy,position.x,position.y);
    }
    return isValid();
}

#endif
