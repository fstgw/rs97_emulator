#ifndef _TESC_JUEGO_
#define _TESC_JUEGO_

#include <math.h>
#include <ctype.h>
#include <string.h>
#include "escenarios.h"
#include "idioma.h"
#include "enemigos.h"

TESC_Juego::TESC_Juego():TMAScene()
{
    miGame = (TProfanationGame*)TMAGame::getCurrentGame();
    io_current_screen = NULL;
    
    // Inicializamos la lista de Sprites a Vacia
    //
    for (int i=0;i<_MAX_SPRITES_;i++)
    {
        lst_Sprites[i]=NULL;
    }

    setState(ST_MENU);
    il_pausa_recorrido_pantalla = 0;    
}

TESC_Juego::~TESC_Juego()
{
    pf_LimpiarSprites();

    if (miGame->isSoundAvailable())
    {
        io_ogg.stop();
    }
    
    if (io_current_screen!=NULL)
    {
        delete io_current_screen;
        io_current_screen = NULL;
    }
}

void TESC_Juego::pf_LimpiarSprites(void)
{
    // Limpiamos la lista de Sprites si 
    //
    for (int i=0;i<_MAX_SPRITES_;i++)
    {
        if (lst_Sprites[i]) delete lst_Sprites[i];
        lst_Sprites[i]=NULL;
    }
}

void TESC_Juego::pf_CrearSprites(int pantalla)
{
    PMAImageBank imgbank = GameMap.getImageBank(1);
    
    TSpriteEnemigo *lspr;
    signed int param0,param1,param2,param3,param4,param5,param6;

    // Limpiamos los posibles Sprites que Existan
    //
    pf_LimpiarSprites();

    // Si el rango de pantalla no es valido, salimos.
    //
    pantalla--;
    if (pantalla<0 || pantalla>_MAX_PANTALLAS_ - 1) return;
    
    // Crea los diferentes sprites.
    //
    for (int i=0;i<_MAX_ENEMIGOS_;i++)
    {
        lspr = NULL;
        
        // Cargamos los parametros del Sprite i-esimo
        //
        param0 = ia_ScrInfo[pantalla].enemigos[i][0];
        param1 = ia_ScrInfo[pantalla].enemigos[i][1];
        param2 = ia_ScrInfo[pantalla].enemigos[i][2];
        param3 = ia_ScrInfo[pantalla].enemigos[i][3];
        param4 = ia_ScrInfo[pantalla].enemigos[i][4];
        param5 = ia_ScrInfo[pantalla].enemigos[i][5];
        param6 = ia_ScrInfo[pantalla].enemigos[i][6];

		if (abs(param5)<100)
		{
			// Ajuste de velocidad - modo small -
			//
			if (_REDUCE>1 && abs(param5)>1) 
			{
				if (param5%2!=0)
				{
					if (param5>0) param5++; 
					else param5--;
				}
				param5/=_REDUCE;
			}
		}
        
        switch (param0)
        {
        case TSPR_GOTA_ROJA:
        case TSPR_GOTA_VERDE:
        case TSPR_GOTA_AZUL:
        case TSPR_GOTA_AMARILLA:
            lspr = new TSprGota(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_FLECHA:
            lspr = new TSprFlecha(imgbank,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_PELOTABOTA:
            lspr = new TSprPelotaBota(imgbank,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_ROCA_BLANCA:
        case TSPR_ROCA_MARRON:
            lspr = new TSprRoca(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_HBABOSA_VERDE:
        case TSPR_HBABOSA_ROJA:
        case TSPR_HBABOSA_AMARILLA:
        case TSPR_SERPIENTE_ROSA:
        case TSPR_SERPIENTE_VERDE:
        case TSPR_SERPIENTE_AMARILLA:
        case TSPR_SERPIENTE_AZUL:
        case TSPR_MOMIA_AZUL:
        case TSPR_MOMIA_VERDE:
        case TSPR_MOMIA_ROJA:
            lspr = new TSprHorizontalConFlip(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_RAYO_MORADO:
        case TSPR_RAYO_AMARILLO:
        case TSPR_RAYO_VERDE:
        case TSPR_RAYO_AZUL:
        case TSPR_VTABLA_ROJA:
        case TSPR_VTABLA_MARRON:
        case TSPR_VTABLA_MORADA:
        case TSPR_VSPIDER_VERDE:
        case TSPR_VSPIDER_ROJO:
        case TSPR_VSPIDER_AZUL:
        case TSPR_VTORNILLO_AZUL:
        case TSPR_VTORNILLO_AMARILLO:
        case TSPR_VPELOTA_ROJA:       
        case TSPR_VPELOTA_AMARILLA:   
        case TSPR_VPELOTA_VERDE:      
        case TSPR_VPELOTA_AZUL:    
        case TSPR_VARO_AMARILLO:      
        case TSPR_VARO_ROJO:          
        case TSPR_VARO_MORADO:
        case TSPR_VBOLAPINCHO_ROJA:
            lspr = new TSprVertical(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_HPELOTA_ROJA:       
        case TSPR_HPELOTA_AMARILLA:   
        case TSPR_HPELOTA_VERDE:      
        case TSPR_HPELOTA_AZUL:       
        case TSPR_HTORNILLO_AZUL:     
        case TSPR_HTORNILLO_AMARILLO: 
        case TSPR_HPALO_AZUL:          
        case TSPR_HPALO_AMARILLO:      
        case TSPR_HPALO_VERDE:         
        case TSPR_HSPIDER_VERDE:      
        case TSPR_HSPIDER_ROJO:       
        case TSPR_HSPIDER_AZUL:       
        case TSPR_HARO_AMARILLO:      
        case TSPR_HARO_ROJO:          
        case TSPR_HARO_MORADO:        
        case TSPR_HBOLAPINCHO_ROJA:   
        case TSPR_HBOLAPINCHO_AZUL:   
        case TSPR_HTABLA_ROJA:
        case TSPR_HTABLA_MARRON:
        case TSPR_HTABLA_MORADA:
        case TSPR_HORMIGUERO:
            lspr = new TSprHorizontal(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;

        case TSPR_VBABOSA_AMARILLA:
        case TSPR_VBABOSA_VERDE:
        case TSPR_VBABOSA_ROJA:
        case TSPR_PEZ_AMARILLO:
        case TSPR_PEZ_AZUL:
        case TSPR_PEZ_VERDE:
            lspr = new TSprVerticalFlip(imgbank,param0,param1,param2,param3,param4,param5,param6);
            break;
        }

        lst_Sprites[i]=lspr;
    }        
}

void TESC_Juego::pf_PrepararScrollTesoro(void)
{
    int lpx;
    bool acierto;

    // Determinamos si la pantalla en curso, tiene puertas o cosas
    // que deban abrirse, y las creamos..
    //
    PMAScreenMap scr = io_current_screen;
    
    switch (scr->getID())
    {
     case 4:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,4,67);
            sprScroll.init(GameMap,4,67,28,10,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 6:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_cogido)
        {
            scr->deleteGraphOperation(1,2,99);
            sprScroll.init(GameMap,2,99,26,10,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 8:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_cogido)
        {
            scr->deleteGraphOperation(1,4,90);
            sprScroll.init(GameMap,4,90,28,2,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 9:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,4,72);
            sprScroll.init(GameMap,4,72,19,2,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 12:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,3,28);
            sprScroll.init(GameMap,3,28,11,2,1,13);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 16:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_cogido)
        {
            scr->deleteGraphOperation(1,4,70);
            sprScroll.init(GameMap,4,70,26,4,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 17:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,3,37);
            sprScroll.init(GameMap,3,37,24,11,1,18);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 21:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,4,89);
            sprScroll.init(GameMap,4,89,28,10,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 22:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_cogido)
        {
            ia_ScrInfo[scr->getID() - 1].tesoro_cogido=false;
            scr->deleteGraphOperation(1,4,74);
            sprScroll.init(GameMap,4,74,20,2,20,19);
        }
        break;

     case 25:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            ia_ScrInfo[scr->getID() - 1].tesoro_puesto=false;
            sprScroll.init(GameMap,4,74,0,0,20,26);
        }
        break;

     case 26:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,4,90);
            sprScroll.init(GameMap,4,90,20,11,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 36:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_cogido)
        {
            lpx = ( (sprJohny.position.x+10) / _TileAX);
            
            acierto = ( (lpx>=15 && lpx<=17 && ii_color_diamante==1) ||
                        (lpx>=18 && lpx<=20 && ii_color_diamante==2) ||
                        (lpx>=21 && lpx<=23 && ii_color_diamante==3) ||
                        (lpx>=24 && lpx<=26 && ii_color_diamante==4) ||
                        (lpx>=27 && lpx<=29 && ii_color_diamante==5) );

            ia_ScrInfo[scr->getID() - 1].tesoro_cogido=false;
            if (acierto)
            {
                // Pasamos a la pantalla siguiente.
                //
                sprScroll.init(GameMap,4,74,0,0,20,37);
            }
            else
            {
                // Quedamos encerrados.
                //
                sprScroll.init(GameMap,4,74,0,0,20,10);
            }
        }
        else if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,4,94);
            sprScroll.init(GameMap,4,94,9,2,1);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        
        break;

     case 37:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,3,38);
            sprScroll.init(GameMap,3,38,19,12,1,38);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

     case 43:
        if (ia_ScrInfo[scr->getID() - 1].tesoro_puesto)
        {
            scr->deleteGraphOperation(1,3,39);
            sprScroll.init(GameMap,3,39,21,2,1,45);
            if (miGame->isSoundAvailable()) miGame->gsnd_Scroll.play(false,miGame->gi_volume);
        }
        break;

    }
}

void TESC_Juego::pf_PrepararPantalla(int pantalla)
{
    if (miGame->isSoundAvailable() && miGame->gsnd_Scroll.isPlaying()) miGame->gsnd_Scroll.stop();
    sprScroll.setPantalla(0);
    sprScroll.invalidate();

    if (io_current_screen!=NULL)
    {
        delete io_current_screen;
        io_current_screen = NULL;
    }

    io_current_screen = GameMap.getScreen(pantalla);
    sprJohny.screen = io_current_screen;
    pf_CrearSprites(pantalla);
    pf_PrepararScrollTesoro();
    GameMap.drawFastBuffer(io_current_screen,0);
    
    if (!ia_ScrInfo[pantalla].visitada)
    {
        ii_pantallas_visitadas++;
        ia_ScrInfo[pantalla].visitada=true;
    }

    if (ii_EstadoJuego==ST_GAME)
    {
        // Si es la pantalla del diamante, ponemos el que corresponde.
        //
        if (pantalla==10)
        {
            io_current_screen->deleteGraphOperation(1,3,45);
            sprScroll.init(GameMap,3,40+ii_color_diamante,25,6,0);
        }

        // Si es la ultima pantalla, preparamos un scroll de paso de pantalla
        //
        if (pantalla==45)
        {
            // Pasamos al final del juego.
            //
            pf_PreparaTextoScroll(3);
            setState(ST_ENDGAME);
        }
    }
}

bool TESC_Juego::doInit(const PMAObject params)
{ 		
    // Definimos la tabla de textos a utilizar.
    //
    switch (miGame->gi_idioma)
    {
        case TProfanationGame::LG_SPAIN:
            ia_txt = ia_txt_sp;
            break;

        case TProfanationGame::LG_ENGLISH:
            ia_txt = ia_txt_en;
            break;

        case TProfanationGame::LG_FRENCH:
            ia_txt = ia_txt_fr;
            break;

        case TProfanationGame::LG_DEUTCH:
            ia_txt = ia_txt_de;
            break;
    }

    // Rellenamos la tabla de senos.
    //
    pf_rellenaTablaSenosMenu((_REDUCE==1)?3:2,20);

    // Establecemos la velocidad de fotograma
    //
    miGame->setGameFPS(36);
    
    // Vamos al menu principal.
    //
    pf_menuPrincipal();
    
    return true;
}

void TESC_Juego::pf_menuPrincipal(void)
{
    int i;
    setState(ST_MENU);
    ii_OpcionMenu=0;
    il_pausa_recorrido_pantalla=0;
    
    // Limpiamos las tablas de estao de tesoros y demás
    // información modificada durante el juego.
    //
    for (i=0;i<_MAX_PANTALLAS_;i++)
    {
        ia_ScrInfo[i].visitada = false;
        ia_ScrInfo[i].tesoro_cogido = false;
        ia_ScrInfo[i].tesoro_puesto = false;
    }
    
    // Establecemos el mapa e inicializamos
	//
	GameMap.setMapFile("Data/mapa.mpb","./");
	GameMap.createBufferForFastDrawing(640/_REDUCE,320/_REDUCE);
	sprScroll.invalidate();
	
	// Comienza la música
	//
	if (miGame->isSoundAvailable())
    {
        if (!io_ogg.isPlaying())
        {
            io_ogg.load("Data/Sonidos/musica.ogg");
            io_ogg.play(true,miGame->gi_volume);
        }
    }
    
    miGame->releaseKeys();
}

void TESC_Juego::pf_comenzarPartida(void)
{
    int i;
    il_pausa_recorrido_pantalla = 0;

    // Limpiamos las tablas de estao de tesoros y demás
    // información modificada durante el juego.
    //
    for (i=0;i<_MAX_PANTALLAS_;i++)
    {
        ia_ScrInfo[i].visitada = false;
        ia_ScrInfo[i].tesoro_cogido = false;
        ia_ScrInfo[i].tesoro_puesto = false;
    }

    for (i=0;i<6;i++) VICTOR[i]=false;

    // Gestion de Tesoros
    //
    buffertesoro[0]=0;
    buffertesoro[1]=0;

    // Gestion de Trucos
    //
    ib_inmune=false;
    ib_vidas_infinitas=false;
    ib_situando_a_johny=false;
    
    // Inicializamos otras acciones importantes para el juego.
    //
    miGame->releaseKeys();
    ii_pantallas_visitadas=0;
    sprJohny.init(GameMap,1);
    sprJohny.putAt(5,13);
    sprJohny.GuardarPosicion();
    sprJohny.Matar(false);
    setState(ST_GAME);
    pf_PrepararPantalla(1);
    
    // Detenemos la Música.
    //
    if (miGame->isSoundAvailable() && io_ogg.isPlaying()) io_ogg.stop();
    
    // Calculamos el color del diamante para esta partida.
    //
    ii_color_diamante = miGame->miRND.nextInt(5)+1;
}

void TESC_Juego::pf_AnimaSprites(void)
{
    for (int i=0;i<_MAX_SPRITES_;i++)
    {
        if (lst_Sprites[i])
        {
            lst_Sprites[i]->animate();
        }
    }    
    if (sprScroll.isValid()) sprScroll.animate();        
}

void TESC_Juego::pf_GestionaCrack(void)
{
    #if defined (TARGET_GP2X) || defined (TARGET_WII)
	
         ib_vidas_infinitas=true;
         ib_situando_a_johny=true;
         miGame->releaseKeys();
         sprJohny.detenerSalto();
         setState(ST_GAME);
         return;
    
	#else
    
		int li_i,lkey;   
        lkey = TMAGame::getLastAsciiKeyPressed();
        if (!lkey) return;
    
        TMAGame::releaseLastAsciiKeyPressed();
        lkey = toupper(lkey & 0xFF);
    
        switch (lkey)
        {
            case 8: // Delete
                if (strlen(ia_password)>0)
                {
                    ia_password[strlen(ia_password)-1]=0;
                }
                break;
                
            case 10:
            case 13:
                if (strlen(ia_password)>7)
                {
                    if (ia_password[0]=='1' &&
                        ia_password[1]=='8' &&
                        ia_password[2]=='0' &&
                        ia_password[3]=='1' &&
                        ia_password[4]=='7' &&
                        ia_password[5]=='4' )
                    {
                        // Salto de Pantalla a...
                        int scr = atoi(&ia_password[6]);
                        if (scr>=1 && scr<=44)
                        {
                            // Enlentecemos el juego, para que el Sprite
                            // Pueda posicionarse sin problemas.
                            //
                            pf_PrepararPantalla(scr);
                            ib_situando_a_johny=true;
                            sprJohny.detenerSalto();
                            miGame->releaseKeys();
                        }
                    }
                }                        
                else if (strlen(ia_password)==7)
                {
                    if (ia_password[0]=='M' &&
                        ia_password[1]=='A' &&
                        ia_password[2]=='L' &&
                        ia_password[3]=='I' &&
                        ia_password[4]=='V' &&
                        ia_password[5]=='E' &&
                        ia_password[6]=='S')
                    {
                        // Vidas infinitas hasta que comience otra partida...
                        //
                        ib_vidas_infinitas=true;
                    }
                    else if (ia_password[0]=='M' &&
                        ia_password[1]=='A' &&
                        ia_password[2]=='S' &&
                        ia_password[3]=='U' &&
                        ia_password[4]=='P' &&
                        ia_password[5]=='E' &&
                        ia_password[6]=='R')
                    {
                        // Vidas inmunidad hasta que comience otra partida...
                        //
                        ib_inmune = true;
                    }
                }
                // Volvemos al juego.
                //
                setState(ST_GAME);
                break;
                
            default:
                for (li_i=0;miGame->gs_charset.text()[li_i]!=lkey && li_i<miGame->gs_charset.length();li_i++);
                if (li_i < miGame->gs_charset.length())
                {
                    if (strlen(ia_password)<sizeof(ia_password)-1)
                    {
                        ia_password[strlen(ia_password)]=lkey;
                        ia_password[strlen(ia_password)+1]=0;
                    }
                }
                break;
        }
    #endif
}

#if defined (TARGET_GP2X) || defined (TARGET_WII)

	void TESC_Juego::pf_DetectCrack(void)
	{
		static int keysequence[6] = { 

			TProfanationGame::GKEY_SELECT,
			TProfanationGame::GKEY_UP,
			TProfanationGame::GKEY_DOWN,
			TProfanationGame::GKEY_UP,
			TProfanationGame::GKEY_DOWN,
			TProfanationGame::GKEY_SELECT 
			
		};
										  
		for (int i=0;i<6;i++)
		{
			if (!VICTOR[i])
			{
				if (i>0 && miGame->inputController.isHoldDown(keysequence[i-1])) return;
				if (miGame->inputController.isPressDown(keysequence[i]))
				{
					VICTOR[i]=true;
					return;
				}
				else break;
			}
		}
		
		// Si hay una tecla pulsada, pero no es ninguna de las esperadas, 
		// empezamos de nuevo.
		//
		if (miGame->inputController.isAnyHoldDown()>0)
		{
			for (int li_i=0;li_i<6;li_i++) VICTOR[li_i]=false;
		}
	}

#else

	void TESC_Juego::pf_DetectCrack(void)
	{
		int lkey = TMAGame::getLastAsciiKeyPressed();            
		if (lkey>0)
		{                                
			TMAGame::releaseLastAsciiKeyPressed();
			
			switch (toupper(lkey & 0xFF))
			{
				case 'V':
					VICTOR[0]=true;
					for (int li_i=1;li_i<6;li_i++) VICTOR[li_i]=false;
					break;
					
				case 'I':
					VICTOR[1]=true;
					for (int li_i=2;li_i<6;li_i++) VICTOR[li_i]=false;
					break;
					
				case 'C':
					VICTOR[2]=true;
					for (int li_i=3;li_i<6;li_i++) VICTOR[li_i]=false;
					break;
					
				case 'T':
					VICTOR[3]=true;
					for (int li_i=4;li_i<6;li_i++) VICTOR[li_i]=false;
					break;
					
				case 'O':
					VICTOR[4]=true;
					VICTOR[5]=false;
					break;
					
				case 'R':
					VICTOR[5]=true;
					break;
			
				default:        
					for (int li_i=0;li_i<6;li_i++) VICTOR[li_i]=false;
					break;
			}
		}
	}

#endif 

bool TESC_Juego::doRun(void)
{    
    // Caso de pulsar CTRL+RETURN
    //
    #if !defined(TARGET_GP2X) && !defined(TARGET_WII)
    
        if (TMAGame::KeyState[SDLK_RETURN] && (TMAGame::KeyState[SDLK_LCTRL] || TMAGame::KeyState[SDLK_RCTRL]))
        {
            miGame->releaseKeys();
            miGame->showFullScreen(!miGame->isFullScreen());
            miGame->releaseKeys();
            miGame->saveConfiguration();
            return true;
        }
    
    #endif
        
    if (ii_EstadoJuego == ST_GAME || ii_EstadoJuego==ST_SHOWSCREENS) 
    {
        GameMap.animateGraphOperations(io_current_screen,TMAGraphOperation::OP_ANIM_FRONT);
        GameMap.animateGraphOperations(io_current_screen,TMAGraphOperation::OP_ANIM_NORMAL);

        pf_AnimaSprites();
        
        if (ib_situando_a_johny)
        {
            if (miGame->inputController.isPressDown(TProfanationGame::GKEY_SELECT))
            {
                ib_situando_a_johny=false;
                sprJohny.detenerSalto();
                sprJohny.GuardarPosicion();
                miGame->releaseKeys();
            }
            else
            {
                if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_LEFT))
                {
                    sprJohny.position.x -= GameMap.getGridAX();
                    miGame->sleep(100);
                }
                if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_RIGHT))
                {
                    sprJohny.position.x += GameMap.getGridAX();
                    miGame->sleep(100);
                }
                if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_UP))
                {
                    sprJohny.position.y -= GameMap.getGridAY();
                    miGame->sleep(100);
                }
                if (miGame->inputController.isHoldDown(TProfanationGame::GKEY_DOWN))
                {
                    sprJohny.position.y += GameMap.getGridAY();
                    miGame->sleep(100);
                }
                if (miGame->inputController.isPressDown(TProfanationGame::GKEY_SCR_PLUS))
                {
                    if (io_current_screen->getID()>1)
                    {
                        pf_PrepararPantalla(io_current_screen->getID()-1);
                    }
                }
                if (miGame->inputController.isPressDown(TProfanationGame::GKEY_SCR_MINUS))
                {
                    if (io_current_screen->getID()<44)
                    {
                        pf_PrepararPantalla(io_current_screen->getID()+1);
                    }
                }
            }            
        }
        else
        {
            if (ii_EstadoJuego == ST_GAME) sprJohny.animate(true);
        }
        
        if (miGame->inputController.isPressDown(TProfanationGame::GKEY_ABORT))
        {
            miGame->sleep(200);
            miGame->releaseKeys();
            pf_menuPrincipal();
            return true;
        }
    }
    
    // Controles en funcion del escenario
    //
    switch (ii_EstadoJuego)
    {
        case ST_MENU:
            
            // Rota table de senos para que los textos bailen.
            //
            pf_rotarTablaSenosMenu();

            // Contador para comenar a ver pantallas.
            //
            il_pausa_recorrido_pantalla++;
			if (il_pausa_recorrido_pantalla>400)
			{
				// Pasamos al recorrido por las pantallas.
				//
				setState(ST_SHOWSCREENS);
				ii_pantalla=0;
				il_pausa_recorrido_pantalla=0;
				pf_PrepararPantalla(ia_recorrido_pantallas[ii_pantalla]);
				break;
            }
            
            // Teclas en el menu
            //
            if (miGame->inputController.isPressDown(TProfanationGame::GKEY_UP))
            {
                if (ii_OpcionMenu>0) ii_OpcionMenu--;
                else ii_OpcionMenu=3;
                miGame->gsnd_Gota.play(false,miGame->gi_volume);
            }
            else if (miGame->inputController.isPressDown(TProfanationGame::GKEY_DOWN))
            {
                if (ii_OpcionMenu<3) ii_OpcionMenu++;
                else ii_OpcionMenu=0;
                miGame->gsnd_Gota.play(false,miGame->gi_volume);
            }
            if (miGame->inputController.isPressDown(TProfanationGame::GKEY_SELECT))
            {
                switch (ii_OpcionMenu)
                {                        
                    case 0:
                        // Pasamos a las instrucciones
                        //
                        miGame->releaseKeys();
                        pf_PreparaTextoScroll(2);
                        setState(ST_INSTRUCTIONS);
                        return true;
                    
                    case 1:
                        // Pasamos al acerca de
                        //
                        miGame->releaseKeys();
                        pf_PreparaTextoScroll(1);
                        setState(ST_ABOUT);
                        return true;
                        
                    case 2:
                        // Comenzamos el juego.
                        //
                        miGame->releaseKeys();
                        pf_comenzarPartida();
                        return true;
                        
                    case 3:
                        // Fin del juego
                        //
                        miGame->endGame();
                        return true;
                }
            }            
            break;
            
        case ST_GAME:
            
            pf_DetectCrack();
            
            if ((VICTOR[0]) && (VICTOR[1]) && (VICTOR[2]) && (VICTOR[3]) && (VICTOR[4]) && (VICTOR[5]))
            {
                // Solo si VICTOR esta activo, se hace lo siguiente.
                //
                setState(ST_CRACK);
                memset(ia_password,0,sizeof(ia_password));
                for (int i=0;i<6;i++) VICTOR[i]=false;
            }

            break;                   
                        
        case ST_SHOWSCREENS:    // Recorrido por pantallas

            il_pausa_recorrido_pantalla++;
            if (il_pausa_recorrido_pantalla>100)
            {
                il_pausa_recorrido_pantalla=0;
                ii_pantalla++;
                if (ii_pantalla==45)
                {
                    il_pausa_recorrido_pantalla=0;
                    setState(ST_MENU);
                    return true;
                }
                pf_PrepararPantalla(ia_recorrido_pantallas[ii_pantalla]);
            }

            if (miGame->inputController.isAnyHoldDown())
            {
                miGame->releaseKeys();
                pf_menuPrincipal();
                return true;
            }
            break;
        
        case ST_INSTRUCTIONS:   // Instrucciones.
        case ST_ABOUT:          // A cerca de.

            pf_AnimInstrucciones();
        
            if (miGame->inputController.isAnyHoldDown())
            {
                miGame->releaseKeys();
                pf_menuPrincipal();
                return true;
            }
            break;

        case ST_ENDGAME:        // Final del juego.

            pf_AnimFinalJuego();

            if (miGame->inputController.isAnyHoldDown())
            {
                miGame->releaseKeys();
                pf_menuPrincipal();
                return true;
            }
            break;
                    
        case ST_CRACK:
            pf_GestionaCrack();
            return true;
    }

    // Ignoramos la tecla de abortar, excepto en el juego, que ya esta controlada.
    //
    if (miGame->inputController.isPressDown(TProfanationGame::GKEY_ABORT)) return true;
    
	return false;
}

void TESC_Juego::pf_DibujaMenu(TMABitmap& buff)
{
    int i;
    PMABitmap bmp;

    // Dibujamos La esfinge y el Logo de Profanation
    //
    bmp = GameMap.getGraphBank(5)->getImage(0);
    buff.draw(bmp,0,379/_REDUCE);
    bmp = GameMap.getGraphBank(7)->getImage(1);
    buff.draw(bmp,144/_REDUCE,10/_REDUCE);
    
    // Dibujamos los textos del menu.
    //
    for (i=0;i<4;i++)
    {
        if (ii_OpcionMenu==i)
        {
            int tw = miGame->fontMulti.getTextWidth(ia_txt[i]) + 20;
            int tx = (640/_REDUCE - tw)/2;
            int ty = (110+i*36)/_REDUCE;
            buff.drawRectFilled(tx,ty,tx+tw,ty+33/_REDUCE,MAKERGBACOLOR(255,255,0,80));
        }
        miGame->fontMulti.drawText(buff,ia_txt[i],-1,(110+i*36)/_REDUCE,ii_offsety_menutxt,640/_REDUCE);
    }
    
    #ifndef TARGET_GP2X
        miGame->fontBlue.drawText(buff,ia_txt[4],-1,300/_REDUCE,NULL,640/_REDUCE);
    #endif     
}

void TESC_Juego::pf_DibujaJuego(TMABitmap& buff)
{
    PMABitmap bmp;
    char bufftxt[40];

    pf_DibujaPantalla(buff,true);
    
    // Pintamos Logotipo 
    //
    bmp = GameMap.getGraphBank(5)->getImage(0);
    buff.draw(bmp,0,379/_REDUCE);
    
    // Pintamos el Pergamino
    //
    bmp = GameMap.getGraphBank(4)->getImage(18);
    buff.draw(bmp,220/_REDUCE,355/_REDUCE);

    // Dibujamos los tesoros si los hay.
    //
    if (buffertesoro[0]!=0) 
    {
        bmp = GameMap.getGraphBank(3)->getImage(buffertesoro[0]);
        buff.draw(bmp,270/_REDUCE,373/_REDUCE);
    }
        
    if (buffertesoro[1]!=0) 
    {
        bmp = GameMap.getGraphBank(3)->getImage(buffertesoro[1]);
        buff.draw(bmp,330/_REDUCE,373/_REDUCE);
    }

    // Dibujamos los textos.
    //
    sprintf(bufftxt,"%s %02i  %s %02i",ia_txt[11],ii_pantallas_visitadas,ia_txt[12],sprJohny.ii_vidas);
    miGame->fontMulti.drawText(buff,bufftxt,-1,325/_REDUCE,NULL,640/_REDUCE);
   
    // Detectamos el paso de pantalla.
    //
    if (!ib_situando_a_johny)
    {
        if (!pf_PasoPantalla())
        {
            if (sprScroll.isValid()) sprScroll.draw(buff);
        }
    }
}

void TESC_Juego::pf_DibujaPantalla(TMABitmap& buff,bool johny)
{
    // Dibuja los graficos de fondo
    //
    buff.draw(GameMap.getFastScreenBuffer(),0,0);
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_ANIM_NORMAL);
    
    // Dibujamos los Sprites
    //
    if (!(sprScroll.isValid() && sprScroll.getPantalla()!=0))
    {
        for (int i=0;i<_MAX_SPRITES_;i++)
        {            
            if (lst_Sprites[i]) 
            {
                lst_Sprites[i]->draw(buff);

                if ( johny && (!ib_inmune) && (!ib_situando_a_johny) )
                {
                    if (!sprJohny.estaMuriendo() && sprJohny.isCollisioningWith(*lst_Sprites[i]))
                    {
                        sprJohny.Matar(true);
                    }
                }
            }            
        }
    }
    
    if (johny)
    {
        // Si el draw devuelve false, significa que matan al prota, 
        // por tanto lo ponemos en el ultimo sitio conocido.
        //
        if (!sprJohny.draw(buff)) 
        {
            if (sprJohny.ii_vidas == 0)
            {
                pf_menuPrincipal();
                return;
            }
            if (!ib_vidas_infinitas) sprJohny.ii_vidas --;
            pf_PrepararPantalla(io_current_screen->getID());
            sprJohny.RestaurarPosicion();
            sprJohny.Matar(false);
        }
    }
    
    // Dibujamos los graficos delanterios
    //    
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_FRONT);
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_ANIM_FRONT);
}

void TESC_Juego::pf_DibujaRecorridoPorPantallas(TMABitmap& buff)
{
    // Dibuja la pantalla actual
    //
    pf_DibujaPantalla(buff,false);
    
    // Dibujamos el Logo de Profanation
    //
    PMABitmap bmp = GameMap.getGraphBank(5)->getImage(0);
    buff.draw(bmp,0,379/_REDUCE);    
}

void TESC_Juego::pf_DibujaInstrucciones(TMABitmap& buff)
{
    int i;

    // Dibujamos la esfinge
    //
    PMABitmap bmp = GameMap.getGraphBank(7)->getImage(1);
    buff.draw(bmp,144/_REDUCE,10/_REDUCE);

    // Dibujamos los textos en sus coordenadas
    //
    for (i=0;i<30/_REDUCE;i++)
    {
        if (ia_texto_buff[i].txt)
        {
            if (ia_texto_buff[i].rainbow)
                miGame->fontMulti.drawText(buff,ia_texto_buff[i].txt,-1,ia_texto_buff[i].y,ii_offsety_menutxt,640/_REDUCE);
            else
                miGame->fontBlue.drawText(buff,ia_texto_buff[i].txt,-1,ia_texto_buff[i].y,ii_offsety_menutxt,640/_REDUCE);                
        }
    }
    
    // Dibujamos el Logo de Profanation
    //
    bmp = GameMap.getGraphBank(5)->getImage(0);
    buff.draw(bmp,0,379/_REDUCE);
}

void TESC_Juego::pf_AnimInstrucciones()
{
    static int offset=0;
    bool lb_rainbow;
    int i;

    pf_rotarTablaSenosMenu();
    offset++;

    // Caso que haya que incluir un nuevo texto.
    //
    if (offset>30/_REDUCE)
    {
        offset=0;
        lb_rainbow=(ii_EstadoJuego==ST_INSTRUCTIONS);
        if (strcmp(ia_txt[ii_texto_scroll],"-*-")==0)
        {
            ii_texto_scroll = ii_texto_scroll1;
        }

        if (strcmp(ia_txt[ii_texto_scroll],"[rainbow]")==0)
        {
            ii_texto_scroll++;
            lb_rainbow=true;
        }

        // Buscamos un hueco y ponemos el siguiente texto.
        //
        for (i=0;i<30/_REDUCE;i++)
        {
            if (ia_texto_buff[i].txt==NULL)
            {
                ia_texto_buff[i].y = 380/_REDUCE;
                ia_texto_buff[i].txt = ia_txt[ii_texto_scroll++];
                ia_texto_buff[i].rainbow = lb_rainbow;
                break;
            }
        }
    }

    // Movemos sus coordenadas
    //
    for (i=0;i<30/_REDUCE;i++)
    {
        if (ia_texto_buff[i].txt)
        {
            if (ia_texto_buff[i].y<-20/_REDUCE)
            {
               memmove(&ia_texto_buff[0],&ia_texto_buff[1],29*sizeof(ia_texto_buff[0]));
	           memset(&ia_texto_buff[29],0,sizeof(ia_texto_buff[29]));
            }
            else
            {                
                ia_texto_buff[i].y --;
            }
        }
    }
}

void TESC_Juego::pf_AnimFinalJuego()
{
    pf_rotarTablaSenosMenu();
}


void TESC_Juego::pf_DibujaFinalJuego(TMABitmap& buff)
{
    int i;

    // Dibujamos la pantalla de fondo.
    //
    buff.draw(GameMap.getFastScreenBuffer(),0,0);
        
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_ANIM_NORMAL);
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_FRONT);
    GameMap.drawScreenGraphOperations(buff,io_current_screen,TMAGraphOperation::OP_ANIM_FRONT);

    // Dibuja el texto..
    //
    i=0;
    while (strcmp(ia_txt[ii_texto_scroll+i],"-*-")!=0)
    {
        miGame->fontMulti.drawText(buff,ia_txt[ii_texto_scroll+i],-1,(10+i*30)/_REDUCE,ii_offsety_menutxt,640/_REDUCE);
        i++;
    }

    // Dibujamos el Logo de Profanation
    //
    PMABitmap bmp = GameMap.getGraphBank(5)->getImage(0);
    buff.draw(bmp,0,379/_REDUCE);
}


void TESC_Juego::pf_PreparaTextoScroll(int nm)
{
    int pos=0;

    while (nm>0)
    {
        if (strcmp(ia_txt[pos++],"-*-")==0)
        {
            nm--;
        }
    }

    memset(ia_texto_buff,0,sizeof(ia_texto_buff));
    ii_texto_scroll=pos;
    ii_texto_scroll1=pos;
    ii_texto_buff_index=0;
}

void TESC_Juego::doPaint(TMABitmap& buff)
{
    buff.clear(0);
    
    switch (ii_EstadoJuego)
    {
    case ST_MENU:
        pf_DibujaMenu(buff);
        break;
    
    case ST_GAME:
        pf_DibujaJuego(buff);
        break;

    case ST_INSTRUCTIONS:
    case ST_ABOUT:
        
        // Instrucciones y a cerca de
        //
        pf_DibujaInstrucciones(buff);
        break;

    case ST_ENDGAME:
        // El final del juego.
        //
        pf_DibujaFinalJuego(buff);
        break;

    case ST_SHOWSCREENS:
        // Gestion del recorrido de pantallas
        //
        pf_DibujaRecorridoPorPantallas(buff);
        break;

    case ST_CRACK:
        
        // Gestion de VICTOR
        //
        miGame->fontBlue.drawText(buff,ia_txt[13],-1,200/_REDUCE,NULL,640/_REDUCE);
        miGame->fontMulti.drawText(buff,ia_password,-1,240/_REDUCE,NULL,640/_REDUCE);
        break;
    }
}

void TESC_Juego::pf_rellenaTablaSenosMenu(int radio,int arcos)
{
 int i;
 double dx = (3.1415926535 * arcos) / 640;
 double val = 0;

 // Calculamos la tabla de senos para la onda vertical.
 //
 for(i=0;i<640;i++)
 {
     ii_offsety_menutxt[i]=(int)(radio*sin(val));
     val+=dx;
 }
}

void TESC_Juego::pf_rotarTablaSenosMenu(void)
{
	int tmp[2] = {ii_offsety_menutxt[639],ii_offsety_menutxt[638]};
	memmove(&ii_offsety_menutxt[2],&ii_offsety_menutxt[0],638*sizeof(ii_offsety_menutxt[0]));
	ii_offsety_menutxt[0] = tmp[0];
	ii_offsety_menutxt[1] = tmp[1];
}

bool TESC_Juego::AbiertaPuertaSecreta(void)
{
    int ScreenID = (io_current_screen->getID() - 1);

    return (
            (ia_ScrInfo[ScreenID].hay_poner_tesoro && ia_ScrInfo[ScreenID].tesoro_puesto) 
            ||
            (ia_ScrInfo[ScreenID].hay_tesoro && ia_ScrInfo[ScreenID].tesoro_cogido)
           );
}

void TESC_Juego::CogerTesoro(void)
{
    int pos;
    int ScreenID = (io_current_screen->getID()- 1);

    if (buffertesoro[0]==0)
    {
        pos=0;
    }
    else
    {
        pos=1;
    }

    if ((ia_ScrInfo[ScreenID].hay_tesoro!=0) && (!ia_ScrInfo[ScreenID].tesoro_cogido))
    {
        if (ia_ScrInfo[ScreenID].hay_tesoro>0)
        {
            if (miGame->isSoundAvailable()) miGame->gsnd_Tesoro.play(false,miGame->gi_volume);
            buffertesoro[pos]=ia_ScrInfo[ScreenID].hay_tesoro;
        }
        ia_ScrInfo[ScreenID].tesoro_cogido=true;
        pf_PrepararScrollTesoro();
    }
}

void TESC_Juego::PonerTesoro(void)
{
    int ScreenID = (io_current_screen->getID() - 1);

    // Si en la ultima pantalla, no tenemos la llave, no podremos
    // poner el tesoro.
    //
    if (ScreenID==42 && (buffertesoro[0]!=40 && buffertesoro[1]!=40)) return;

    if ((ia_ScrInfo[ScreenID].hay_poner_tesoro!=0) && (!ia_ScrInfo[ScreenID].tesoro_puesto))
    {
        if (ia_ScrInfo[ScreenID].hay_poner_tesoro >0)
        {
            if (buffertesoro[0]==ia_ScrInfo[ScreenID].hay_poner_tesoro)
            {
                if (buffertesoro[1])
                {
                    buffertesoro[0]=buffertesoro[1];
                    buffertesoro[1]=0;  
                }
                else buffertesoro[0]=0;

                if (miGame->isSoundAvailable()) miGame->gsnd_Tesoro.play(false,miGame->gi_volume);
                ia_ScrInfo[ScreenID].tesoro_puesto=true;
                pf_PrepararScrollTesoro();
                return;
            }

            if (buffertesoro[1]==ia_ScrInfo[ScreenID].hay_poner_tesoro)
            {
                buffertesoro[1]=0;
                if (miGame->isSoundAvailable()) miGame->gsnd_Tesoro.play(false,miGame->gi_volume);
                ia_ScrInfo[ScreenID].tesoro_puesto=true;
                pf_PrepararScrollTesoro();
                return;
            }
        }
        else if (ia_ScrInfo[ScreenID].hay_poner_tesoro < 0)
        {
          ia_ScrInfo[ScreenID].tesoro_puesto=true;
          pf_PrepararScrollTesoro();
        }

    }
}

bool TESC_Juego::pf_PasoPantalla(void)
{
    int ScreenID = io_current_screen->getID();
    int ScreenIDNew;

    // Detectamos si hay paso de pantalla por apertura de tesoro.
    //
    if (sprScroll.getPantalla()>0)
    {
        pf_PrepararPantalla(sprScroll.getPantalla());
        pf_buscarPosicionInicialJohny();
        if (miGame->isSoundAvailable()) miGame->gsnd_Teletransporte.play(false,miGame->gi_volume);
        return true;
    }
    
	// Detectamos el paso de pantalla a la izquierda
	//
	if (sprJohny.isEnterLeft())
	{
		ScreenIDNew = ia_ScrInfo[ScreenID-1].scrLeft;
		if (ScreenIDNew!=0)
		{
			pf_PrepararPantalla(ScreenIDNew);
            sprJohny.enterLeft();
            return true;
		}
	}

    // Detectamos el paso de pantalla hacia arriba
	//
	if (sprJohny.isEnterUp())
	{
		ScreenID = ia_ScrInfo[ScreenID-1].scrTop;
		if (ScreenID!=0)
		{
			pf_PrepararPantalla(ScreenID);
			sprJohny.enterUp();
            return true;
		}
	}

	// Detectamos el paso de pantalla a la derecha
	//
	if (sprJohny.isEnterRight())
	{
		ScreenIDNew = ia_ScrInfo[ScreenID-1].scrRight;
		if (ScreenIDNew!=0)
		{
			pf_PrepararPantalla(ScreenIDNew);
            switch (ScreenID)
            {
            case 4:
            case 6:
            case 8:
            case 16:
            case 21:
                pf_buscarPosicionInicialJohny();
                if (miGame->isSoundAvailable()) miGame->gsnd_Teletransporte.play(false,miGame->gi_volume);
                break;
            default:
			    sprJohny.enterRight();
                break;
            }
            return true;
		}
	}

	// Detectamos el paso de pantalla hacia abajo
	//
	if (sprJohny.isEnterDown())
	{
		ScreenID = ia_ScrInfo[ScreenID-1].scrBottom;
		if (ScreenID!=0)
		{
			pf_PrepararPantalla(ScreenID);
			sprJohny.enterDown();
            return true;
		}
	}


    // No se pasa de pantalla
    //
    return false;
}

void TESC_Juego::pf_buscarPosicionInicialJohny(void)
{
	int tx,ty;

	// Localizamos dentro de la pantalla activa, un lugar donde
	// debe colocarse el sprite principal.
    // Esto solo ocurre cuando se salta hacia una pantalla por arriba.
	//
	tx = GameMap.getScreenX()/ GameMap.getGridAX();
	ty = GameMap.getScreenY() / GameMap.getGridAY();

	for (int px=0;px<tx;px++)
	for (int py=0;py<ty;py++)
	{
		if (io_current_screen->getMask(px,py)==5)
		{
            sprJohny.detenerSalto();
            sprJohny.putAt(px,py-1);
            sprJohny.GuardarPosicion();
            return;
		}
	}

}

#endif
