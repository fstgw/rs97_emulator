#ifndef _TPELOTABOTA_
#define _TPELOTABOTA_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprPelotaBota);

int TSprPelotaBota::Anim[4]       ={45,46,47,46};

TSprPelotaBota::TSprPelotaBota(PMAImageBank bank,int pinitx,int pinity,int pendx,int pendy,int vel,int retardo):TSpriteEnemigo(bank)
{
    ii_Retardo = retardo;

    setAnimSequence(Anim,4);

    init_x = pinitx*_TileAX;
    init_y = pinity*_TileAY;
    end_x  = pendx*_TileAX;
    end_y  = pendy*_TileAY;
    vx=vel; vy=vel;

    // Definimos la posición inicial y el tamaño del Sprite
    //
    position.x = pinitx*_TileAX;
    position.y = pinity*_TileAY;
    position.width = 40/_REDUCE;
    position.height = 40/_REDUCE;

    ii_Frame=0;
}

void TSprPelotaBota::animate(void)
{
    if (ii_RetardoPos<ii_Retardo)
	{
		ii_RetardoPos ++;
	}
	else
	{
		ii_Frame = (ii_Frame<ii_AnimSequenceLength-1)?(ii_Frame+1):0;
		ii_RetardoPos=0;
	}

    // Hacemos que la flecha surque hasta que llegue a su fin.
    //
    if (position.x < init_x || position.x > end_x )
    {
        vx=-vx;
    }
    if (position.y < init_y || position.y > end_y )
    {
        vy=-vy;
    }
    
    position.x += vx;
    position.y  += vy;

    TMASprite::animate();
}

bool TSprPelotaBota::draw(TMABitmap& g)
{
    PMABitmap img = io_images->getBitmap(ii_CurrentFotograma);
    img->setAlpha(150);
    g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
    return true;
}

#endif
