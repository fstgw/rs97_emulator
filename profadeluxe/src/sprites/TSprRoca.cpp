#ifndef _TROCA_
#define _TROCA_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprRoca);

int TSprRoca::AnimBlanca[6]={216,217,218,219,220,221};
int TSprRoca::AnimMarron[6]={233,234,235,236,237,238};

TSprRoca::TSprRoca(PMAImageBank bank,int tipo,int posx,int posy,int pinity,int pendy,int vel,int pausa_rota):TSpriteEnemigo(bank)
{
    miGame = (TProfanationGame*)TMAGame::getCurrentGame();
    pausa_rotura=pausa_rota;
    if (pausa_rotura==0) pausa_rotura=1;

    switch (tipo)
    {
    case TSPR_ROCA_BLANCA:
        setAnimSequence(AnimBlanca,6);
        break;
    case TSPR_ROCA_MARRON:
        setAnimSequence(AnimMarron,6);
        break;
    }

    init_y = pinity*_TileAY;
    end_y  = pendy*_TileAY;
    velocidad=vel;

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

void TSprRoca::animate(void)
{    
    // Calculamos la animación.
    //
    switch (ii_Estado)
    {
    case 0:
        // Hacemos que la roca caiga hasta que llegue a su fin.
        //
        if (position.y < end_y)
        {
            position.y += velocidad;
        }
        else
        {
            position.y = end_y;
            ii_Estado++;
            if (miGame->isSoundAvailable()) miGame->gsnd_Roca.play(false,miGame->gi_volume);
        }
        break;

    default:
 
        if (!(ii_Estado % pausa_rotura)) 
        {
            ii_Frame++;
        }
        ii_Estado++;

        if (ii_Frame==6)
        {
            ii_Frame=0;
            ii_Estado=0;
            position.y = init_y;
        }
        break;
    }

    TMASprite::animate();
}

#endif
