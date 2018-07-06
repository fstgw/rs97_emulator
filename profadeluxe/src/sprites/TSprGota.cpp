#ifndef _TGOTA_
#define _TGOTA_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprGota);

int TSprGota::AnimRojo[7]       ={18,19,20,21,22,23,24};
int TSprGota::AnimAmarillo[7]   ={35,36,37,38,39,40,41};
int TSprGota::AnimVerde[7]      ={52,53,54,55,56,57,58};
int TSprGota::AnimAzul[7]       ={69,70,71,72,73,74,75};

TSprGota::TSprGota(PMAImageBank bank,int tipo,int posx,int posy,int pinity,int pendy,int vel,int pausa_rota):TSpriteEnemigo(bank)
{
    miGame = (TProfanationGame*)TMAGame::getCurrentGame();

    pausa_rotura=pausa_rota;
    if (pausa_rotura==0) pausa_rotura=1;

    switch (tipo)
    {
    case TSPR_GOTA_ROJA:
        setAnimSequence(AnimRojo,7);
        break;
    case TSPR_GOTA_AMARILLA:
        setAnimSequence(AnimAmarillo,7);
        break;
    case TSPR_GOTA_VERDE:
        setAnimSequence(AnimVerde,7);
        break;
    case TSPR_GOTA_AZUL:
        setAnimSequence(AnimAzul,7);
        break;
    }

    init_y = pinity*_TileAY;
    end_y  = pendy*_TileAY;
    
    if ( abs(vel)<100)
    {
        pausa_caida = 0;
        velocidad=vel;
    }
    else 
    {
        pausa_caida=abs(vel)-100;
        velocidad=1;
    }

    // Definimos la posición inicial y el tamaño del Sprite
    //
    position.x = posx*_TileAX;
    position.y = init_y;
    position.width = 40/_REDUCE;
    position.height = 40/_REDUCE;

    // Establecemos el primer fotograma de la animación.
    //
    if (posy>pinity)
    {
        position.y = posy*_TileAY;
        ii_Frame=2;
        ii_Estado=10;
    }
    else
    {
        ii_Frame=0;
        ii_Estado=0;
    }
}

void TSprGota::animate(void)
{
    static int pcaida=0;
    
    // Animamos la gota.
    //
    switch (ii_Estado)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
    
            // Los 2 primeros fotogramas son la condensación de la gota.
            if (ii_Estado==4 || ii_Estado==9) ii_Frame++;
            ii_Estado++;
            break;
    
        case 10:
            ii_Estado++;
            break;
    
        case 11:
            // Hacemos que la gota caiga hasta que llegue a su fin.
            if (position.y < end_y)
            {
                pcaida++;
                if (pcaida>=pausa_caida)
                {
                    position.y += velocidad;
                    pcaida=0;
                }
            }
            else
            {
                position.y = end_y;
                ii_Frame++;
                ii_Estado++;
                if (miGame->isSoundAvailable()) miGame->gsnd_Gota.play(false,miGame->gi_volume);
            }
            break;
    
        default:
     
            if (!(ii_Estado % pausa_rotura)) 
            {
                ii_Frame++;
            }
            ii_Estado++;
    
            if (ii_Frame==7)
            {
                ii_Frame=0;
                ii_Estado=0;
                position.y = init_y;
            }
            break;
    }
    
    TMASprite::animate();
}

bool TSprGota::draw(TMABitmap& g)
{
    PMABitmap img = io_images->getBitmap(ii_CurrentFotograma);
    img->setAlpha(150);
    g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
    //g.drawRect(position.x+6,position.y+2,position.x+position.width-10,position.y+position.height-3,MAKERGBCOLOR(255,255,255));
    return true;
}

void TSprGota::getCollisionRectangle(TMARectangle& r)
{
     r.setBounds(position);
     
     #ifdef SMALL_GAME
        r.width-=5;
        r.height-=2;
        r.x +=3;
        r.y +=1;
     #else
        r.width-=10;
        r.height-=4;
        r.x +=6;
        r.y +=2;
     #endif
}

#endif
