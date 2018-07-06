#ifndef _TMASPRITE_CPP_
#define _TMASPRITE_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMASprite);

TMASprite::TMASprite(TMAImageBank *bank)
{
    // Establecemos el tipo de Sprite
    //
    validate();
    ii_Frame = 0;
    ii_Retardo=0;
    ii_RetardoPos=0;
    ii_EstadoAnim=0;
    ii_Estado=0;
    ii_CurrentFotograma=0;
    ib_flip_x=false;
    ib_flip_y=false;
    ii_AnimSequenceLength=0;
    ia_AnimSequence=NULL;
    io_images=bank;
}


void TMASprite::animate(void)
{
    if (ia_AnimSequence==NULL) return;
    if (ib_flip_x) ii_CurrentFotograma = ia_AnimSequence[ii_AnimSequenceLength - ii_Frame - 1];
    else		   ii_CurrentFotograma = ia_AnimSequence[ii_Frame];
}

bool TMASprite::isCollisioningWith(TMASprite& s)
{
	return position.intersects(s.position);
}
	
bool TMASprite::draw(TMABitmap& g)
{
    g.drawSprite(io_images->getBitmap(ii_CurrentFotograma),position.x,position.y,ib_flip_x,ib_flip_y);
    return true;
}

void TMASprite::setAnimSequence(const int *as,int length)
{
    ii_AnimSequenceLength=length;
    ia_AnimSequence=as;
    ii_Frame = 0;
    TMASprite::animate();
}

#endif
