#ifndef _TSPRVERTICAL_
#define _TSPRVERTICAL_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprVertical);

// Rayos
//
int TSprVertical::AnimRayoMorado[3]     ={25,26,27};
int TSprVertical::AnimRayoAmarillo[3]   ={42,43,44};
int TSprVertical::AnimRayoVerde[3]      ={59,60,61};
int TSprVertical::AnimRayoAzul[3]       ={76,77,78};

// Tablas
//
int TSprVertical::AnimTablaMarron[8]   ={137,138,139,140,141,142,143,144};
int TSprVertical::AnimTablaRoja[8]     ={154,155,156,157,158,159,160,161};
int TSprVertical::AnimTablaMorada[8]   ={171,172,173,174,175,176,177,178};

// Arañas
//
int TSprVertical::AnimSpiderVerde[8]    ={205,206,207,208,209,208,207,206};
int TSprVertical::AnimSpiderRoja[8]     ={222,223,224,225,226,225,224,223};
int TSprVertical::AnimSpiderAzul[8]     ={239,240,241,242,243,242,241,240};

// Tornillos
//
int TSprVertical::AnimTornilloAzul[8]    ={150,151,152,153,167,168,169,170};
int TSprVertical::AnimTornilloAmarillo[8]={184,185,186,187,201,202,203,204};

// Pelotas
//
int TSprVertical::AnimPelotaRoja[4]     ={28,29,30,29};
int TSprVertical::AnimPelotaAmarilla[4] ={45,46,47,46};
int TSprVertical::AnimPelotaVerde[4]    ={62,63,64,63};
int TSprVertical::AnimPelotaAzul[4]     ={79,80,81,80};

// Aros
//
int TSprVertical::AnimAroAmarillo[6]   ={210,211,212,213,214,215};
int TSprVertical::AnimAroRojo[6]       ={227,228,229,230,231,232};
int TSprVertical::AnimAroMorado[6]     ={244,245,246,247,248,249};

// Bolas de Pincho
//
int TSprVertical::AnimBolaPinchoRoja[10]   ={191,192,193,194,195,194,195,194,193,192};


TSprVertical::TSprVertical(PMAImageBank bank,int tipo,int posx,int posy,int pymin,int pymax,int vel,int retardo):TSpriteEnemigo(bank)
{
    ii_Retardo=retardo;
    it_tipo = tipo;
    
    switch (tipo)
    {
    case TSPR_RAYO_MORADO:
        setAnimSequence(AnimRayoMorado,3);
        break;
    case TSPR_RAYO_AMARILLO:
        setAnimSequence(AnimRayoAmarillo,3);
        break;
    case TSPR_RAYO_VERDE:
        setAnimSequence(AnimRayoVerde,3);
        break;
    case TSPR_RAYO_AZUL:
        setAnimSequence(AnimRayoAzul,3);
        break;

    case TSPR_VTABLA_ROJA:
        setAnimSequence(AnimTablaRoja,8);
        break;
    case TSPR_VTABLA_MARRON:
        setAnimSequence(AnimTablaMarron,8);
        break;
    case TSPR_VTABLA_MORADA:
        setAnimSequence(AnimTablaMorada,8);
        break;

    case TSPR_VSPIDER_VERDE:
        setAnimSequence(AnimSpiderVerde,8);
        break;
    case TSPR_VSPIDER_ROJO:
        setAnimSequence(AnimSpiderRoja,8);
        break;
    case TSPR_VSPIDER_AZUL:
        setAnimSequence(AnimSpiderAzul,8);
        break;

    case TSPR_VTORNILLO_AZUL:
        setAnimSequence(AnimTornilloAzul,8);
        break;
    case TSPR_VTORNILLO_AMARILLO:
        setAnimSequence(AnimTornilloAmarillo,8);
        break;

    case TSPR_VPELOTA_ROJA:
        setAnimSequence(AnimPelotaRoja,4);
        break;
    case TSPR_VPELOTA_AMARILLA:
        setAnimSequence(AnimPelotaAmarilla,4);
        break;
    case TSPR_VPELOTA_VERDE:
        setAnimSequence(AnimPelotaVerde,4);
        break;
    case TSPR_VPELOTA_AZUL:
        setAnimSequence(AnimPelotaAzul,4);
        break;

    case TSPR_VARO_AMARILLO:
        setAnimSequence(AnimAroAmarillo,6);
        break;
    case TSPR_VARO_ROJO:
        setAnimSequence(AnimAroRojo,6);
        break;
    case TSPR_VARO_MORADO:
        setAnimSequence(AnimAroMorado,6);
        break;

    case TSPR_VBOLAPINCHO_ROJA:
        setAnimSequence(AnimBolaPinchoRoja,10);
        break;
    }

    init_y = pymin*_TileAY;
    end_y  = pymax*_TileAY;
    mpausa = 0;
    
    if (abs(vel)>100)
    {
        pausa_movimiento = abs(vel)-100;
        velocidad=((vel>0)?1:-1);
    }
    else
    {
        pausa_movimiento=0;    
        velocidad=vel;
    }
    
    if (velocidad<0) 
    {
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

void TSprVertical::animate()
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

    if (bajando)
    {
        mpausa++;
        if (mpausa>=pausa_movimiento)
        {
            position.y += velocidad;
            mpausa=0;
        }
        
        if (position.y > end_y)
        {
            position.y = end_y;
            bajando = false;
        }
    }
    else
    {
        mpausa++;
        if (mpausa>=pausa_movimiento)
        {
            position.y -= velocidad;
            mpausa=0;
        }
        
        if (position.y < init_y)
        {
            position.y = init_y;
            bajando = true;
        }
    }
    
    TMASprite::animate();
}

bool TSprVertical::draw(TMABitmap& g)
{
    PMABitmap img = io_images->getBitmap(ii_CurrentFotograma);
    
    switch (it_tipo)
    {
        case TSPR_VPELOTA_ROJA:       
        case TSPR_VPELOTA_AMARILLA:   
        case TSPR_VPELOTA_VERDE:      
        case TSPR_VPELOTA_AZUL:
            img->setAlpha(150);
            g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
            break;

        default:
            g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
    }
    return true;    
}

void TSprVertical::getCollisionRectangle(TMARectangle& r)
{
    switch (it_tipo)
    {
        case TSPR_RAYO_MORADO:
        case TSPR_RAYO_AMARILLO:
        case TSPR_RAYO_VERDE:
        case TSPR_RAYO_AZUL:
            r.setBounds(position);
            #ifdef SMALL_GAME
                r.width-=8;
                r.x +=4;
            #else
                r.width-=16;
                r.x +=8;
            #endif
            break;
        default:
            TSpriteEnemigo::getCollisionRectangle(r);
    }
}

#endif
