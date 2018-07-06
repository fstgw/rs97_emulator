#ifndef _TSPRHORIZONTAL_
#define _TSPRHORIZONTAL_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprHorizontal);

// Pelotas
//
int TSprHorizontal::AnimPelotaRoja[4]     ={28,29,30,29};
int TSprHorizontal::AnimPelotaAmarilla[4] ={45,46,47,46};
int TSprHorizontal::AnimPelotaVerde[4]    ={62,63,64,63};
int TSprHorizontal::AnimPelotaAzul[4]     ={79,80,81,80};

// Tornillos
//
int TSprHorizontal::AnimTornilloAzul[8]    ={150,151,152,153,167,168,169,170};
int TSprHorizontal::AnimTornilloAmarillo[8]={184,185,186,187,201,202,203,204};

// Palos
//
int TSprHorizontal::AnimPaloAzul[8]     ={145,146,147,148,149,148,147,146};
int TSprHorizontal::AnimPaloAmarillo[8] ={162,163,164,165,166,165,164,163};
int TSprHorizontal::AnimPaloVerde[8]    ={179,180,181,182,183,182,181,180};

// Arañas
//
int TSprHorizontal::AnimSpiderVerde[8]    ={205,206,207,208,209,208,207,206};
int TSprHorizontal::AnimSpiderRoja[8]     ={222,223,224,225,226,225,224,223};
int TSprHorizontal::AnimSpiderAzul[8]     ={239,240,241,242,243,242,241,240};

// Aros
//
int TSprHorizontal::AnimAroAmarillo[6]   ={210,211,212,213,214,215};
int TSprHorizontal::AnimAroRojo[6]       ={227,228,229,230,231,232};
int TSprHorizontal::AnimAroMorado[6]     ={244,245,246,247,248,249};

// Tablas
//
int TSprHorizontal::AnimTablaMarron[8]   ={137,138,139,140,141,142,143,144};
int TSprHorizontal::AnimTablaRoja[8]     ={154,155,156,157,158,159,160,161};
int TSprHorizontal::AnimTablaMorada[8]   ={171,172,173,174,175,176,177,178};

// Bolas de Pincho
//
int TSprHorizontal::AnimBolaPinchoRoja[10]   ={191,192,193,194,195,194,195,194,193,192};
int TSprHorizontal::AnimBolaPinchoAzul[10]   ={196,197,198,199,200,199,200,199,198,197};

// Homiguero
//
int TSprHorizontal::AnimHormiguero[6]={250,251,252,253,254,255};


TSprHorizontal::TSprHorizontal(PMAImageBank bank,int tipo,int posx,int posy,int pxmin,int pxmax,int vel,int retardo):TSpriteEnemigo(bank)
{
    ii_Retardo=retardo;
    it_tipo = tipo;
    switch (tipo)
    {

    case TSPR_HPELOTA_ROJA:
        setAnimSequence(AnimPelotaRoja,4);
        break;
    case TSPR_HPELOTA_AMARILLA:
        setAnimSequence(AnimPelotaAmarilla,4);
        break;
    case TSPR_HPELOTA_VERDE:
        setAnimSequence(AnimPelotaVerde,4);
        break;
    case TSPR_HPELOTA_AZUL:
        setAnimSequence(AnimPelotaAzul,4);
        break;

    case TSPR_HPALO_AZUL:
        setAnimSequence(AnimPaloAzul,8);
        break;
    case TSPR_HPALO_AMARILLO:
        setAnimSequence(AnimPaloAmarillo,8);
        break;
    case TSPR_HPALO_VERDE:
        setAnimSequence(AnimPaloVerde,8);
        break;


    case TSPR_HTABLA_ROJA:
        setAnimSequence(AnimTablaRoja,8);
        break;
    case TSPR_HTABLA_MARRON:
        setAnimSequence(AnimTablaMarron,8);
        break;
    case TSPR_HTABLA_MORADA:
        setAnimSequence(AnimTablaMorada,8);
        break;

    case TSPR_HSPIDER_VERDE:
        setAnimSequence(AnimSpiderVerde,8);
        break;
    case TSPR_HSPIDER_ROJO:
        setAnimSequence(AnimSpiderRoja,8);
        break;
    case TSPR_HSPIDER_AZUL:
        setAnimSequence(AnimSpiderAzul,8);
        break;

    case TSPR_HTORNILLO_AZUL:
        setAnimSequence(AnimTornilloAzul,8);
        break;
    case TSPR_HTORNILLO_AMARILLO:
        setAnimSequence(AnimTornilloAmarillo,8);
        break;

    case TSPR_HARO_AMARILLO:
        setAnimSequence(AnimAroAmarillo,6);
        break;
    case TSPR_HARO_ROJO:
        setAnimSequence(AnimAroRojo,6);
        break;
    case TSPR_HARO_MORADO:
        setAnimSequence(AnimAroMorado,6);
        break;

    case TSPR_HBOLAPINCHO_ROJA:
        setAnimSequence(AnimBolaPinchoRoja,10);
        break;
    case TSPR_HBOLAPINCHO_AZUL:
        setAnimSequence(AnimBolaPinchoAzul,10);
        break;

    case TSPR_HORMIGUERO:
        setAnimSequence(AnimHormiguero,6);
        break;
    }

    mpausa=0;
    init_x = pxmin*_TileAX;
    end_x  = pxmax*_TileAX;

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
    if (velocidad<0)
    {
        derecha=false;
        velocidad=-velocidad;
    }
    else derecha=true;
}

void TSprHorizontal::animate(void)
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

    if (derecha)
    {
        mpausa++;
        if (mpausa>=pausa_movimiento)
        {
            position.x += velocidad;
            mpausa=0;
        }

        if (position.x > end_x)
        {
            position.x = end_x;
            derecha = false;
        }
    }
    else
    {
        mpausa++;
        if (mpausa>=pausa_movimiento)
        {
            position.x -= velocidad;
            mpausa=0;
        }
        
        if (position.x < init_x)
        {
            position.x = init_x;
            derecha = true;
        }
    }
    
    TMASprite::animate();    
}

bool TSprHorizontal::draw(TMABitmap& g)
{
    PMABitmap img = io_images->getBitmap(ii_CurrentFotograma);
    
    switch (it_tipo)
    {
        case TSPR_HPELOTA_ROJA:       
        case TSPR_HPELOTA_AMARILLA:   
        case TSPR_HPELOTA_VERDE:      
        case TSPR_HPELOTA_AZUL:  
            img->setAlpha(150);
            g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
            break;

        default:
            g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
    }
    
    /*
    sprintf(buff,"%i,%i,%i",velocidad,mpausa,mpausa_movimiento);
    TProfanationGame *pg = (TProfanationGame*)TMAGame::getCurrentGame();
    pg->fontMulti.drawText(g,buff,position.x,position.y);
    */
    
    return true;
}


#endif
