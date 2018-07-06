#ifndef _TESC_SELECCION_IDIOMA_
#define _TESC_SELECCION_IDIOMA_

#include "escenarios.h"

REGISTER_CLASS_ID(TESC_Seleccion_Idioma);
TMAString TESC_Seleccion_Idioma::ia_himnos[4][2] = 
{
    {"Data/Idioma/Himnos/espana.ogg","ESPAÑOL"},
    {"Data/Idioma/Himnos/inglaterra.ogg","ENGLISH"},
    {"Data/Idioma/Himnos/francia.ogg","FRANÇAIS"},
    {"Data/Idioma/Himnos/alemania.ogg","DEUTSCH"}
};
int TESC_Seleccion_Idioma::ia_cursor_pos[] = { 76/_REDUCE,216/_REDUCE,356/_REDUCE,496/_REDUCE};

TESC_Seleccion_Idioma::TESC_Seleccion_Idioma():TMAScene()
{
    miGame = (TProfanationGame*)TMAGame::getCurrentGame();
}

TESC_Seleccion_Idioma::~TESC_Seleccion_Idioma()
{
    if (io_Screen!=NULL)
    {
        delete io_Screen;
        io_Screen = NULL;
    }
    if (sprSeleccion!=NULL) delete sprSeleccion;
    if (masoft!=NULL) delete masoft;
}

bool TESC_Seleccion_Idioma::doInit(const PMAObject params)
{    
    li_alpha=0;

    if (!map.setMapFile("Data/Idioma.mpb","./"))
    {
        miGame->showFatalError("No se puede cargar archivo de mapa.");
        return false;
    }
    
    io_Screen = NULL; 
    gotoSelectLanguage();

    if (io_Screen)
    {
        masoft = TMABitmap::loadFromFile("Data/Idioma/masoft.png");
        sprSeleccion = new TSprSeleccion(map.getImageBank(2),true,this);
        sprSeleccion->putAt(ia_cursor_pos[miGame->gi_idioma],276/_REDUCE);
    }

    return (io_Screen!=NULL);
}        

bool TESC_Seleccion_Idioma::doRun(void)
{
    doRunLanguage();    
    return false;
}

void TESC_Seleccion_Idioma::doPaint(TMABitmap& buff)
{
    doPaintLanguage(buff);
};

void TESC_Seleccion_Idioma::doPaintLanguage(TMABitmap& buff)
{
    buff.clear(map.getBackgroundColor());
    map.drawScreen(buff,io_Screen);
    
    sprSeleccion->draw(buff);
    miGame->fontBlue.drawText(buff,ia_himnos[miGame->gi_idioma][1].text(),-1,360/_REDUCE,NULL,640/_REDUCE);

    if (li_alpha<255)
    {
        masoft->setAlpha(li_alpha); li_alpha+=2;
        buff.draw(masoft,70/_REDUCE,50/_REDUCE);
        if (li_alpha>=254) masoft->disableAlpha();
    }
    else  buff.draw(masoft,70/_REDUCE,50/_REDUCE);
}

void TESC_Seleccion_Idioma::doRunLanguage(void)
{
    sprSeleccion->animate();
    map.animateGraphOperations(io_Screen,TMAGraphOperation::OP_ANIM_FRONT);
    
    if (miGame->inputController.isPressDown(TProfanationGame::GKEY_LEFT)&& miGame->gi_idioma>0 && !sprSeleccion->isMoving())
	{
		sprSeleccion->gi_idioma = (miGame->gi_idioma-1);
		sprSeleccion->moveTo(ia_cursor_pos[sprSeleccion->gi_idioma],sprSeleccion->position.y);
	}
	else if (miGame->inputController.isPressDown(TProfanationGame::GKEY_RIGHT) && miGame->gi_idioma<3 && !sprSeleccion->isMoving())
	{
		sprSeleccion->gi_idioma = (miGame->gi_idioma+1);
		sprSeleccion->moveTo(ia_cursor_pos[sprSeleccion->gi_idioma],sprSeleccion->position.y);
	}
	else if ( miGame->inputController.isPressDown(TProfanationGame::GKEY_SELECT) && !sprSeleccion->isMoving()) gotoMainMenu();
	
}


void TESC_Seleccion_Idioma::playCountryMidi(void)
{    
    if (miGame->isSoundAvailable())
    {
    	io_ogg.stop();
        if (io_ogg.load(ia_himnos[miGame->gi_idioma][0].text())) 
        {
            io_ogg.play(true,miGame->gi_volume);
        }
    }
}

void TESC_Seleccion_Idioma::languageChanged(void)
{
    miGame->gi_idioma = sprSeleccion->gi_idioma;
    playCountryMidi();
    miGame->saveConfiguration();
}

void TESC_Seleccion_Idioma::gotoSelectLanguage(void)
{
    miGame->releaseKeys();
    ii_Estado=-1;
    if (io_Screen!=NULL) delete io_Screen;
    io_Screen = map.getScreen(1);
	playCountryMidi();
	ii_Estado=0;
}


void TESC_Seleccion_Idioma::gotoMainMenu(void)
{
	ii_Estado=-1;
	if (miGame->isSoundAvailable()) 
    {
        io_ogg.close();
    }	
    miGame->gi_idioma_anterior = miGame->gi_idioma;
	miGame->setScene(new TESC_Juego());
}

	    
#endif
