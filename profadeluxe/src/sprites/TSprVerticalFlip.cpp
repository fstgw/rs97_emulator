#ifndef _TSPRVERTICALFLIP_
#define _TSPRVERTICALFLIP_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprVerticalFlip);

// Babosas
//
int TSprVerticalFlip::AnimBabosaAmarilla[8]={92,93,94,95,96,95,94,93};
int TSprVerticalFlip::AnimBabosaVerde[8]=   {109,110,111,112,113,112,111,110};
int TSprVerticalFlip::AnimBabosaRoja[8]=    {126,127,128,129,130,129,128,127};

// Peces
//
int TSprVerticalFlip::AnimPezAmarilloS[4]={86,87,88,87};
int TSprVerticalFlip::AnimPezAmarilloB[4]={89,90,91,90};
int TSprVerticalFlip::AnimPezAzulS[4]    ={103,104,105,104};
int TSprVerticalFlip::AnimPezAzulB[4]    ={106,107,108,107};
int TSprVerticalFlip::AnimPezVerdeS[4]   ={120,121,122,121};
int TSprVerticalFlip::AnimPezVerdeB[4]   ={123,124,125,124};

TSprVerticalFlip::TSprVerticalFlip(PMAImageBank bank,int tipo,int posx,int posy,int pymin,int pymax,int vel,int retardo):TSpriteEnemigo(bank)
{
    anim=NULL;
    ii_Retardo=retardo;

    switch (tipo)
    {
    case TSPR_VBABOSA_AMARILLA:
        setAnimSequence(AnimBabosaAmarilla,8);
        break;
    case TSPR_VBABOSA_VERDE:
        setAnimSequence(AnimBabosaVerde,8);
        break;
    case TSPR_VBABOSA_ROJA:
        setAnimSequence(AnimBabosaRoja,8);
        break;

    case TSPR_PEZ_AMARILLO:
        setAnimSequence(AnimPezAmarilloB,4);
        anim=AnimPezAmarilloS;
        break;
    case TSPR_PEZ_AZUL:
        setAnimSequence(AnimPezAzulB,4);
        anim=AnimPezAzulS;
        break;
    case TSPR_PEZ_VERDE:
        setAnimSequence(AnimPezVerdeB,4);
        anim=AnimPezVerdeS;
        break;
    }

    init_y = pymin*_TileAY;
    end_y  = pymax*_TileAY;
    velocidad=vel;

    if (velocidad<0)
    {
        const int *aux_anim;
        aux_anim = ia_AnimSequence;
        ia_AnimSequence = anim;
        anim = aux_anim;
        velocidad=-velocidad;
        bajando=false;
    }
    else bajando=true;

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

void TSprVerticalFlip::animate(void)
{
    const int *aux_anim;

    if (ii_RetardoPos<ii_Retardo)
	{
		ii_RetardoPos ++;
	}
	else
	{
		ii_Frame = (ii_Frame<ii_AnimSequenceLength-1)?(ii_Frame+1):0;
		ii_RetardoPos=0;
	}

    if (bajando)
    {
        position.y += velocidad;
        if (position.y > end_y)
        {
            position.y = end_y;
            bajando = false;
            if (anim!=NULL)
            {
                aux_anim = ia_AnimSequence;
                ia_AnimSequence = anim;
                anim = aux_anim;
            }
            else ib_flip_y=!ib_flip_y;
        }
    }
    else
    {
        position.y -= velocidad;
        if (position.y < init_y)
        {
            position.y = init_y;
            bajando = true;
            if (anim!=NULL)
            {
                aux_anim = ia_AnimSequence;
                ia_AnimSequence = anim;
                anim = aux_anim;
            }
            else ib_flip_y=!ib_flip_y;
        }
    }
    
    TMASprite::animate();
}

bool TSprVerticalFlip::draw(TMABitmap& g)
{
    g.drawSprite(io_images->getBitmap(ii_CurrentFotograma),position.x,position.y,ib_flip_x,ib_flip_y);
    return true;
}

#endif
