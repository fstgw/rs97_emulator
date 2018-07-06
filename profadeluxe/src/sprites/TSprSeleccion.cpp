#ifndef _TSPRSELECCION_CPP_
#define _TSPRSELECCION_CPP_

#include "sprites.h"
#include "../escenas/escenarios.h"

REGISTER_CLASS_ID(TSprSeleccion);
const int TSprSeleccion::ia_anim_idioma[2]={1,2};
const int TSprSeleccion::ia_anim_game[2]={24,25};
    	
TSprSeleccion::TSprSeleccion(PMAImageBank bank,bool idioma,TESC_Seleccion_Idioma* esc):TMASprite(bank)
{
    ib_moviendo=false;
    ii_vel=8/_REDUCE;
    gi_idioma=0;
    ii_Retardo=3;
    setAnimSequence((idioma)?ia_anim_idioma:ia_anim_game,2);
    notify=esc;
}

void TSprSeleccion::moveTo(int x,int y)
{
	ir_destino.x = x;
	ir_destino.y = y;

	if (ir_destino.x < position.x) ir_destino.width = -ii_vel;
	else if (ir_destino.x > position.x) ir_destino.width = ii_vel;
	else ir_destino.width = 0;

	if (ir_destino.y < position.y) ir_destino.height = -ii_vel;
	else if (ir_destino.y > position.y) ir_destino.height = ii_vel;
	else ir_destino.height = 0;

	ib_moviendo = true;	
}

void TSprSeleccion::animate(void)
{
   	if (ib_moviendo)
    {
    	if (abs(position.x - ir_destino.x)>8) position.x += ir_destino.width;
    	if (abs(position.y - ir_destino.y)>8) position.y += ir_destino.height;
    
    	if ( (abs(position.x - ir_destino.x)<=8) && 
    	     (abs(position.y - ir_destino.y)<=8) )
    	{
    		position.x = ir_destino.x;
    		position.y = ir_destino.y;
    		ib_moviendo = false;
    		if (notify!=NULL) notify->languageChanged();
    	}
    }
    
    if (ii_RetardoPos<ii_Retardo)
    {
    	ii_RetardoPos ++;
    }
    else
    {
    	ii_Frame = (ii_Frame<ii_AnimSequenceLength - 1)?(ii_Frame+1):0;
    	ii_RetardoPos=0;
    }
    
    TMASprite::animate();
}


#endif
