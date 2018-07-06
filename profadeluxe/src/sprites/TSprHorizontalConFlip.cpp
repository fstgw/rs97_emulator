#ifndef _TSPRHORIZONTALCONFLIP_
#define _TSPRHORIZONTALCONFLIP_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprHorizontalConFlip);

// Serpientes
//
int TSprHorizontalConFlip::AnimSerpienteRosa[6]     ={31,32,33,34,33,32};
int TSprHorizontalConFlip::AnimSerpienteAmarilla[6] ={48,49,50,51,50,49};
int TSprHorizontalConFlip::AnimSerpienteVerde[6]    ={65,66,67,68,67,66};
int TSprHorizontalConFlip::AnimSerpienteAzul[6]     ={82,83,84,85,84,83};

// Babosa
//
int TSprHorizontalConFlip::AnimBabosaAmarilla[8]    ={96,95,94,93,92,93,94,95};
int TSprHorizontalConFlip::AnimBabosaVerde[8]       ={113,112,111,110,109,110,111,112};
int TSprHorizontalConFlip::AnimBabosaRoja[8]        ={130,129,128,127,126,127,128,129};

// Momia
//
int TSprHorizontalConFlip::AnimMomiaAzul[6]         ={97,98,99,100,101,102};
int TSprHorizontalConFlip::AnimMomiaVerde[6]        ={114,115,116,117,118,119};
int TSprHorizontalConFlip::AnimMomiaRoja[6]         ={131,132,133,134,135,136};

TSprHorizontalConFlip::TSprHorizontalConFlip(PMAImageBank bank,int tipo,int posx,int posy,int pxmin,int pxmax,int vel,int retardo):TSpriteEnemigo(bank)
{
    ii_Retardo=retardo;

    switch (tipo)
    {
    case TSPR_SERPIENTE_ROSA:
        setAnimSequence(AnimSerpienteRosa,6);
        break;
    case TSPR_SERPIENTE_AMARILLA:
        setAnimSequence(AnimSerpienteAmarilla,6);
        break;
    case TSPR_SERPIENTE_VERDE:
        setAnimSequence(AnimSerpienteVerde,6);
        break;
    case TSPR_SERPIENTE_AZUL:
        setAnimSequence(AnimSerpienteAzul,6);
        break;

    case TSPR_HBABOSA_AMARILLA:
        setAnimSequence(AnimBabosaAmarilla,8);
        break;
    case TSPR_HBABOSA_VERDE:
        setAnimSequence(AnimBabosaVerde,8);
        break;
    case TSPR_HBABOSA_ROJA:
        setAnimSequence(AnimBabosaRoja,8);
        break;

    case TSPR_MOMIA_AZUL:
        setAnimSequence(AnimMomiaAzul,6);
        break;
    case TSPR_MOMIA_VERDE:
        setAnimSequence(AnimMomiaVerde,6);
        break;
    case TSPR_MOMIA_ROJA:
        setAnimSequence(AnimMomiaRoja,6);
        break;
    }

    init_x = pxmin*_TileAX;
    end_x  = pxmax*_TileAX;
    velocidad=vel;
    if (velocidad<0)
    {
        setFlipX(true);
        velocidad=-velocidad;
    }
    
    // Definimos la posición inicial y el tamaño del Sprite
    //
    position.x = posx*_TileAX;
    position.y = posy*_TileAY;
    position.width = 40/_REDUCE;
    position.height = 40/_REDUCE;

    // Establecemos el primer fotograma de la animación.
    //
    ii_Frame=0;
    ii_Estado=0;
}

void TSprHorizontalConFlip::animate(void)
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

    if (!ib_flip_x)
    {
        position.x += velocidad;
        if (position.x > end_x)
        {
            position.x = end_x;
            ib_flip_x = true;
        }
    }
    else
    {
        position.x -= velocidad;
        if (position.x < init_x)
        {
            position.x = init_x;
            ib_flip_x = false;
        }
    }
    
    TMASprite::animate();
}

bool TSprHorizontalConFlip::draw(TMABitmap& g)
{
    g.drawSprite(io_images->getBitmap(ii_CurrentFotograma),position.x,position.y,ib_flip_x,ib_flip_y);
    return true;
}

#endif
