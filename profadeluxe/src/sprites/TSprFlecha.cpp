#ifndef _TFLECHA_
#define _TFLECHA_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprFlecha);

int TSprFlecha::Anim[4]       ={188,189,188,190};

TSprFlecha::TSprFlecha(TMAImageBank *bank,int posx,int posy,int pinitx,int pendx,int vel,int retardo):TSpriteEnemigo(bank)
{
    ii_Retardo = retardo;

    setAnimSequence(Anim,4);
    
    init_x = pinitx*_TileAX;
    end_x  = pendx*_TileAX;
    velocidad=vel;

    // Definimos la posición inicial y el tamaño del Sprite
    //
    position.x = posx*_TileAX;
    position.y = posy*_TileAY;
    position.width = 40/_REDUCE;
    position.height = 40/_REDUCE;

    ii_Frame=0;
}

void TSprFlecha::animate(void)
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
    if (position.x < end_x)
    {
        position.x += velocidad;
    }
    else
    {
        position.x = init_x;
    }

    TMASprite::animate();
}

#endif
