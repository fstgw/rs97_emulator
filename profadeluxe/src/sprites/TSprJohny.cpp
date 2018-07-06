#ifndef _TPROTA_
#define _TPROTA_

#include "sprites.h"
#include "../escenas/escenarios.h"

#ifdef SMALL_GAME
    #define _VELOCIDAD_ANDAR_ 2
    #define _VELOCIDAD_SALTAR_ 3
#else
    #define _VELOCIDAD_ANDAR_ 4
    #define _VELOCIDAD_SALTAR_ 6
#endif

#define _WALK_LEFT              false
#define _WALK_RIGHT             true

#define _MASK_NADA_             0
#define _MASK_PARED_            1
#define _MASK_MUERTE_           2
#define _MASK_COGE_TESORO_      3
#define _MASK_TRANSITO_         4
#define _MASK_INICIO_JOHNY_     5
#define _MASK_PON_TESORO_       6

REGISTER_CLASS_ID(TSprJohny);

int TSprJohny::ia_AnimAndando[48]={1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,
                                5,6,7,8,5,6,7,8,5,6,7,8,5,6,7,8,
                                9,10,11,12,9,10,11,12,9,10,11,12,9,10,11,12};
int TSprJohny::ia_AnimParado[12]={15,13,15,14,15,16,15,14,15,13,15,16};
int TSprJohny::ia_AnimSaltando[12]={17,17,17,17,17,17,17,17,17,17,17,17};

void TSprJohny::pf_EstablecerAnimacion(int tipo)
{
    switch (tipo)
    {
    case ANIM_ANDANDO:
        setAnimSequence(ia_AnimAndando,48);
        ii_Retardo=2;
        break;

    case ANIM_PARADO:
        setAnimSequence(ia_AnimParado,12);
        ii_Retardo=60;
        break;

    case ANIM_SALTANDO:
        setAnimSequence(ia_AnimSaltando,12);
        ii_Retardo=60;
        break;

    case ANIM_MURIENDO:
        setAnimSequence(ia_AnimAndando,4);
        ii_Retardo=10;
        break;
    }

    ii_Frame=0;
}

TSprJohny::TSprJohny():TMASprite(NULL)
{
    miGame = (TProfanationGame*)TMAGame::getCurrentGame();
    screen = NULL;
}

void TSprJohny::init(TMAGameMap& m,int pbank)
{
    map = &m;
    io_images = map->getImageBank(pbank);
    
    detenerSalto();

	ii_vidas=10;	

    position.width = 40/_REDUCE;
    position.height = 40/_REDUCE;
    ii_tilesx = 2;
    ii_tilesy = 2;
    ii_Frame=0;
    ii_Estado=0;
    ib_suelo_mortal=false;
}

void TSprJohny::detenerSalto(void)
{
    ib_andando_izquierda=false;
    ib_andando_derecha=false;
    ib_saltando=false;
    il_longitud_salto=0;
    il_tiempo_salto=0;
    pf_EstablecerAnimacion(ANIM_PARADO);
}

void TSprJohny::putAt(int px,int py)
{
    detenerSalto();
    position.x = px*_TileAX;
    position.y = py*_TileAY;
    GuardarPosicion();
    pf_EstablecerAnimacion(ANIM_PARADO);
    ii_Frame=0;
}

void TSprJohny::animate(bool control)
{
    ii_CurrentFotograma = ia_AnimSequence[ii_Frame];

    // Detectamos el movimiento del Sprite
	//
	if (control && (ii_Estado==0)) pf_ControlMovimiento();
	
	// Caso que este muriendo.
	if (ii_Estado>0)
	{
        ii_Estado+=10;
        return;
    }
    
	switch (ii_EstadoAnim)
	{
	  case 0: // Animación Andando Normal.

		if (ii_RetardoPos<ii_Retardo)
		{
			ii_RetardoPos ++;
		}
		else
		{
			ii_Frame = (ii_Frame<ii_AnimSequenceLength-1)?(ii_Frame+1):0;
			ii_RetardoPos=0;
		}
		break;
	}
}


void TSprJohny::Matar(bool m)
{
    if (m)
    {
        ii_Estado=1;
        if (miGame->isSoundAvailable()) 
        {
            miGame->gsnd_Camina.stop();
            miGame->gsnd_Grito.play(false,miGame->gi_volume);
        }
    }
    else
    {
      ib_suelo_mortal=false;
      ii_Estado=0;
    }
}

bool TSprJohny::draw(TMABitmap& g)
{
    PMABitmap img = io_images->getBitmap(ii_CurrentFotograma);
        
    // Dibujamos el Sprite
    //
    if (ii_Estado==0)
    {
        // Caso de juego normal
        //
        img->disableAlpha();
        g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);
        //g.drawRect(position.x+2,position.y+2,position.x+position.width-3,position.y+position.height-3,MAKERGBCOLOR(255,255,255));
    }
    else
    {
        // Caso de Sprite muriendo..
        //
        img->setAlpha(256-ii_Estado);
        g.drawSprite(img,position.x,position.y,ib_flip_x,ib_flip_y);

        // Indicamos que el Sprite ha muerto.
        //
        if (ii_Estado>=256) 
        {
            detenerSalto();
            return false;
        }
    } 
	
    return true;
}

void TSprJohny::pf_DoJump(void)
{    
    // Mientras podamos subir lo hacemos.
    //
    if (il_tiempo_salto>0)
    {
        il_tiempo_salto--;
        
        if (il_longitud_salto>0)
        {
            il_longitud_salto--;
            
            if (pf_CanJump())
            {
                pf_MoveUp();
            }
            else
            {
                // Si se trataba de un salto vertical, entonces al topar
                // con el techo, comenzamos a caer.
                
                if (!ib_andando_izquierda && !ib_andando_derecha)
                {
                    il_longitud_salto=0;
                    il_tiempo_salto=0;
                }
            }
        }

        if (miGame->isSoundAvailable() && !miGame->gsnd_Salto.isPlaying())
        {
            miGame->gsnd_Salto.play(false,miGame->gi_volume);
        }
    }
    else
    {
        // Ahora hemos de empezar a caer.
        //
        if (pf_CanFallDown())
        {
            pf_MoveDown();
            
            if (miGame->isSoundAvailable() && !miGame->gsnd_Caida.isPlaying())
            {
                miGame->gsnd_Caida.play(false,miGame->gi_volume);
            }
        }
        else
        {
            // Caso que hayamos topado con el suelo.
            //
            if (miGame->isSoundAvailable())
            {
                if (miGame->gsnd_Caida.isPlaying()) miGame->gsnd_Caida.stop();
                if (miGame->gsnd_Salto.isPlaying()) miGame->gsnd_Salto.stop();
            }
            
            detenerSalto();
            return;
        }
    }

    // Caso que se este saltando hacia la izquierda.
    //
    if (ib_andando_izquierda)
    {
        if (pf_CanMove(false))
        {
            pf_MoveLeft();
        }
    }
    else 
    // Caso que se este saltando hacia la derecha
    //
    if (ib_andando_derecha)
    {
        if (pf_CanMove(true))
        {
            pf_MoveRight();
        }
    }
}

void TSprJohny::pf_ControlMovimiento(void)
{
    if (ib_saltando)
    {
        pf_DoJump();
        return;
    }
    
    if (pf_CanFallDown())
    {
        if (miGame->isSoundAvailable())
        {
            if (miGame->gsnd_Camina.isPlaying()) miGame->gsnd_Camina.stop();
            if (!miGame->gsnd_Caida.isPlaying()) miGame->gsnd_Caida.play(false,miGame->gi_volume);
        }
        pf_MoveDown();
        return;
    }
    else
    {
        if (miGame->isSoundAvailable() && miGame->gsnd_Caida.isPlaying()) miGame->gsnd_Caida.stop();
    }
    
    // Intentando Caminar hacia la izquierda
	//
	if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_LEFT))
	{		
		// Determinamos si el personaje puede andar hacia la izquierda
		//
		if (pf_CanMove(_WALK_LEFT))
		{
            // Determinamos la animación.
            //
            if (!ib_andando_izquierda)
            {
                ib_andando_derecha=false;
                ib_andando_izquierda=true;
                pf_EstablecerAnimacion(ANIM_ANDANDO);
            }
			
            // Si anteriormente estaba andando hacia la derecha, justo al
            // pulsar la izquierda, no se desplaza, solo cambia de sentido.
            //
			if (!ib_flip_x)
            {
                ib_flip_x=true;
            }
            else
            {
                pf_MoveLeft();
            }
        }
    }

    // Intentando caminar hacia la derecha.
    //
    else if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_RIGHT))
    {
		// Determinamos si el personaje puede andar hacia la derecha
		//
		if (pf_CanMove(_WALK_RIGHT))
		{
			// Determinamos la animación.
            //
            if (!ib_andando_derecha)
            {
                ib_andando_derecha=true;
                ib_andando_izquierda=false;
                pf_EstablecerAnimacion(ANIM_ANDANDO);
            }
			
            // Si anteriormente estaba andando hacia la derecha, justo al
            // pulsar la izquierda, no se desplaza, solo cambia de sentido.
            //
			if (ib_flip_x)
            {
                ib_flip_x=false;
            }
            else
            {
                pf_MoveRight();
            }
        }
    }
    else
    {
        // Caso que el personaje este parado.
        //
        if (ib_andando_izquierda || ib_andando_derecha)
        {
            if (miGame->isSoundAvailable() && miGame->gsnd_Camina.isPlaying())
            {
                miGame->gsnd_Camina.stop();
            }
            ib_andando_izquierda=false;
            ib_andando_derecha=false;
            pf_EstablecerAnimacion(ANIM_PARADO);
        }
    }

    if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_LONG_JUMP))
    {
        // Caso que se pretenda usar el salto largo.
        //
        ib_saltando=true;
        
        il_longitud_salto=((86/_REDUCE)/_VELOCIDAD_SALTAR_);
        il_tiempo_salto=il_longitud_salto + 2; 

        if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_LEFT))
        {
            ib_andando_izquierda=true;
            ib_andando_derecha=false;
            ib_flip_x=true;
        }
        else if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_RIGHT))
        {
            ib_andando_derecha=true;
            ib_andando_izquierda=false;
            ib_flip_x=false;
        }

        if (ib_andando_izquierda || ib_andando_derecha)
        {
            pf_EstablecerAnimacion(ANIM_SALTANDO);
        }

        if (miGame->isSoundAvailable() and miGame->gsnd_Camina.isPlaying())
        {
            miGame->gsnd_Camina.stop();
        }
        return;
    }
    else if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_SHORT_JUMP))
    {
        // Caso que se pretenda usar el salto corto.
        //
        ib_saltando=true;

        il_longitud_salto=((46/_REDUCE)/_VELOCIDAD_SALTAR_);
        il_tiempo_salto=il_longitud_salto + 2;
        
        if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_LEFT))
        {
            ib_andando_izquierda=true;
            ib_andando_derecha=false;
            ib_flip_x=true;
        }
        else if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_RIGHT))
        {
            ib_andando_derecha=true;
            ib_andando_izquierda=false;
            ib_flip_x=false;
        }

        if (ib_andando_izquierda || ib_andando_derecha)
        {
            pf_EstablecerAnimacion(ANIM_SALTANDO);
        }

        if (miGame->isSoundAvailable() and miGame->gsnd_Camina.isPlaying())
        {
            miGame->gsnd_Camina.stop();
        }
        return;
    }

    // Si el personaje esta andando, ponemos el sonidito.
    //
    if (!ib_saltando && (ib_andando_izquierda || ib_andando_derecha))
    {
        if (miGame->isSoundAvailable() and !miGame->gsnd_Camina.isPlaying())
        {
            miGame->gsnd_Camina.play(true,miGame->gi_volume);
        }
    }

}

bool TSprJohny::isEnterLeft(void)
{
    return (position.x < 0);
}

bool TSprJohny::isEnterRight(void)
{
    switch (screen->getID())
    {
    case 6:
        return (position.x >= 516/_REDUCE);

    default:
        return (position.x + position.width > 640/_REDUCE);
    }
}

bool TSprJohny::isEnterUp(void)
{
    return (position.y < 0);
}

bool TSprJohny::isEnterDown(void)
{
    return (position.y + position.height > 320/_REDUCE);
}

void TSprJohny::enterLeft(void)
{
	position.x = (640/_REDUCE) - position.width ;
	GuardarPosicion();
}

void TSprJohny::enterRight(void)
{
	position.x = 0;
	GuardarPosicion();
}


void TSprJohny::enterUp(void)
{	
	position.y = (320/_REDUCE) - position.height;
	GuardarPosicion();
}

void TSprJohny::enterDown(void)
{
    position.y = 0;
	GuardarPosicion();
}

// Determina si el personaje puede desplazarse un pixel a derecha o izquierda
//
bool TSprJohny::pf_CanMove(bool derecha)
{
	int px,py,valor;

    if (derecha)
        px = (position.x + position.width) / _TileAX;
    else
        px = (position.x - 1) / _TileAX;
    
    if (derecha && px>31) return true;
    if (!derecha && px<0) return true;
    
	for (int i=0;i<position.height;i+=2)
	{
        py = ((position.y+i) / _TileAY);

        valor = screen->getMask(px,py);
        switch (valor)
        {
        case _MASK_TRANSITO_:
            if (!((TESC_Juego*)miGame->getScene())->AbiertaPuertaSecreta()) return false;
            break;
            
        case _MASK_MUERTE_:
        case _MASK_NADA_:
        case _MASK_INICIO_JOHNY_:
            break;

        case _MASK_COGE_TESORO_:
            ((TESC_Juego*)miGame->getScene())->CogerTesoro();
            return false;

        case _MASK_PON_TESORO_:
            ((TESC_Juego*)miGame->getScene())->PonerTesoro();
            return false;

        default:
            return false;
       }
    }
	return true;
}

void TSprJohny::pf_MoveLeft(void)
{
    position.x --;
    for (int i=1;i<_VELOCIDAD_ANDAR_;i++)
    {
        if (pf_CanMove(_WALK_LEFT)) position.x --;
    }
}

void TSprJohny::pf_MoveRight(void)
{
    position.x ++;
    for (int i=1;i<_VELOCIDAD_ANDAR_;i++)
    {
        if (pf_CanMove(_WALK_RIGHT)) position.x ++;
    }
}

bool TSprJohny::pf_CanJump(void)
{
    int px,py,valor;

    py = (position.y - 1) / _TileAY;

    if (py<0) return true;

	for (int i=0;i<position.width;i+=2)
	{
        px = ( (position.x + i) / _TileAX);
		valor = screen->getMask(px,py);
        switch (valor)
        {
            case _MASK_TRANSITO_:
                if (!((TESC_Juego*)miGame->getScene())->AbiertaPuertaSecreta()) return false;
                break;

            case _MASK_MUERTE_:
            case _MASK_NADA_:
            case _MASK_INICIO_JOHNY_:
                break;

            case _MASK_COGE_TESORO_:
                ((TESC_Juego*)miGame->getScene())->CogerTesoro();
                return false;

            case _MASK_PON_TESORO_:
                ((TESC_Juego*)miGame->getScene())->PonerTesoro();
                return false;

            default:
                return false;
        }
	}
	return true;
}

void TSprJohny::pf_MoveUp(void)
{
    position.y --;
    for (int i=1;i<_VELOCIDAD_SALTAR_;i++)
    {
        if (pf_CanJump()) position.y --;
    }
}

bool TSprJohny::pf_CanFallDown(void)
{
    int px,py,valor;
	ib_suelo_mortal=false;
	
    py = (position.y + position.height ) / _TileAY;
    if (py>15) return true;

	for (int i=0;i<position.width;i+=2)
	{
        px = ((position.x+i)  / _TileAX);
        valor = screen->getMask(px,py);
        switch (valor)
        {
            case _MASK_TRANSITO_:
                if (!((TESC_Juego*)miGame->getScene())->AbiertaPuertaSecreta()) return false;
                break;
            
            case _MASK_MUERTE_:
                ib_suelo_mortal=true;
            
            case _MASK_NADA_:    
            case _MASK_INICIO_JOHNY_:
                break;

            case _MASK_COGE_TESORO_:
                ((TESC_Juego*)miGame->getScene())->CogerTesoro();
                return false;

            case _MASK_PON_TESORO_:
                ((TESC_Juego*)miGame->getScene())->PonerTesoro();
                return false;

            default:
                return false;
        }
    }
	return true;
}

void TSprJohny::pf_MoveDown(void)
{
    position.y ++;
    for (int i=1;i<_VELOCIDAD_SALTAR_;i++)
    {
        if (pf_CanFallDown()) position.y ++;
    }
}

void TSprJohny::GuardarPosicion(void)
{
    est_MemPos.setBounds(position);
    est_izquierda=ib_andando_izquierda;
    est_derecha=ib_andando_derecha;
    est_saltando=ib_saltando;
    est_longitud_salto=il_longitud_salto;
    est_tiempo_salto=il_tiempo_salto;

    est_animacion = ia_AnimSequence;
    est_longitud_animacion = ii_AnimSequenceLength;
    est_retardo_animacion = ii_Retardo;

    est_flip = ib_flip_x;
}

void TSprJohny::RestaurarPosicion(void)
{
    position.setBounds(est_MemPos);
    ib_andando_izquierda=est_izquierda;
    ib_andando_derecha=est_derecha;
    ib_saltando=est_saltando;
    il_longitud_salto=est_longitud_salto;
    il_tiempo_salto=est_tiempo_salto;

    setAnimSequence(est_animacion,est_longitud_animacion);
    ii_Retardo=est_retardo_animacion;

    ib_flip_x = est_flip;
}

bool TSprJohny::isCollisioningWith(TSpriteEnemigo& s)
{
    TMARectangle s1,s2;
    if (ib_suelo_mortal) return true;
    
    s1.setBounds(position); 
    
    #ifdef SMALL_GAME
        s1.width-=2;
        s1.height-=1;
        s1.x +=1;
        s1.y +=1;
    #else
        s1.width-=4;
        s1.height-=4;
        s1.x +=2;
        s1.y +=2;
    #endif
    
    s.getCollisionRectangle(s2);
                    
    return s1.intersects(s2);
}

#endif
