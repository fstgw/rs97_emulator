#ifndef _PROFANATION_CPP_
#define _PROFANATION_CPP_

#include "profanation.h"
#include "../escenas/escenarios.h"

#if !defined(TARGET_GP2X) && !defined(TARGET_WII)
	#include <string.h>
	#if defined (LINUX)
	  #include <unistd.h>
	#elif defined (WIN32)
	  #include <dir.h>
	#endif
#endif

// **************************************
// Definición de métodos de clase TMAGame
// **************************************
//
REGISTER_CLASS_ID(TProfanationGame);

TMAString TProfanationGame::gs_charset("ABCDEFGHIJKLMNÑOPQRSTUVWXYZ:.,()*0123456789 Ç'-ÄËÏÖÜÁÉÍÓÚÀÈÌÒÙÂÊÎÔÛ");

int TProfanationGame::gi_idioma=TProfanationGame::LG_SPAIN;
int TProfanationGame::gi_idioma_anterior=TProfanationGame::LG_SPAIN;
int TProfanationGame::gi_volume=128;

// --------- IMPLEMENTACION DE DESTRUCTOR
//
TProfanationGame::~TProfanationGame()
{
    cleanup();
}


#ifdef TARGET_WII

    #define SENSIBILITY 20 

    void TProfanationGame::updateInputController()
    {
	  struct expansion_t stick;
	  bool sleft=false,sright=false,sup=false,sdown=false,nun_C=false,nun_Z=false;
	  
	  WPAD_ScanPads();
	  WPAD_Expansion(WPAD_CHAN_0, &stick);
 
	  u16 buttonsHeld = WPAD_ButtonsHeld(0);
	  u16 buttonsDown = WPAD_ButtonsDown(0);
		
	  if(stick.type == WPAD_EXP_NUNCHUK)
	  {
		float diffx = stick.nunchuk.js.pos.x - stick.nunchuk.js.center.x; 
		float diffy = stick.nunchuk.js.pos.y - stick.nunchuk.js.center.y; 
		
        if(fabs(diffx)>SENSIBILITY)  
        { 
		  sright = (stick.nunchuk.js.pos.x > stick.nunchuk.js.center.x);
		  sleft = (stick.nunchuk.js.pos.x < stick.nunchuk.js.center.x);
		} 
    
        if(fabs(diffy)>SENSIBILITY)  
        { 
		  sup = (stick.nunchuk.js.pos.y > stick.nunchuk.js.center.y);
		  sdown = (stick.nunchuk.js.pos.y < stick.nunchuk.js.center.y);
		} 

		nun_C = stick.nunchuk.btns_held & NUNCHUK_BUTTON_C;
		nun_Z = stick.nunchuk.btns_held & NUNCHUK_BUTTON_Z;
		
		inputController.setStatus(GKEY_LEFT, sleft ||  (buttonsHeld & WPAD_BUTTON_LEFT));
		inputController.setStatus(GKEY_RIGHT,sright || (buttonsHeld & WPAD_BUTTON_RIGHT));
		inputController.setStatus(GKEY_UP,   sup ||    (buttonsHeld & WPAD_BUTTON_UP));
		inputController.setStatus(GKEY_DOWN, sdown ||  (buttonsHeld & WPAD_BUTTON_DOWN));
        
		inputController.setStatus(GKEY_LONG_JUMP, nun_C || (buttonsDown & WPAD_BUTTON_1));
		inputController.setStatus(GKEY_SHORT_JUMP, nun_Z || (buttonsDown & WPAD_BUTTON_2));
	  }
	  else
	  {      
	    inputController.setStatus(GKEY_LEFT, (buttonsHeld & WPAD_BUTTON_UP));
        inputController.setStatus(GKEY_RIGHT,(buttonsHeld & WPAD_BUTTON_DOWN));
        inputController.setStatus(GKEY_UP,   (buttonsHeld & WPAD_BUTTON_RIGHT));
        inputController.setStatus(GKEY_DOWN, (buttonsHeld & WPAD_BUTTON_LEFT));
        
        inputController.setStatus(GKEY_LONG_JUMP, (buttonsDown & WPAD_BUTTON_1));
        inputController.setStatus(GKEY_SHORT_JUMP,(buttonsDown & WPAD_BUTTON_2));
      }
    
      inputController.setStatus(GKEY_SELECT,(buttonsDown & WPAD_BUTTON_A));
      inputController.setStatus(GKEY_ABORT,(buttonsDown & WPAD_BUTTON_HOME));

      inputController.setStatus(GKEY_SCR_PLUS,(buttonsDown & WPAD_BUTTON_PLUS));
      inputController.setStatus(GKEY_SCR_MINUS,(buttonsDown & WPAD_BUTTON_MINUS));
    }

#elif defined(TARGET_GP2X)

	void TProfanationGame::updateInputController(SDL_Event& event)
	{        
        bool lb_pressed = false;
        int lbutton = -1;
        
        switch (event.type)
		{
			case SDL_JOYBUTTONDOWN:
                lb_pressed = true;
				lbutton = event.jbutton.button;
				break;
						
			case SDL_JOYBUTTONUP:
				lb_pressed = false;
				lbutton = event.jbutton.button;
				break;
        }
        
		switch (lbutton)
		{
			case GP2X_BUTTON_L:
				inputController.setStatus(GKEY_SCR_PLUS, lb_pressed);
				break;
				
			case GP2X_BUTTON_R:
				inputController.setStatus(GKEY_SCR_MINUS, lb_pressed);
				break;
				
			case GP2X_BUTTON_UP:
				inputController.setStatus(GKEY_UP, lb_pressed);
				break;
				
			case GP2X_BUTTON_LEFT:
				inputController.setStatus(GKEY_LEFT, lb_pressed);
				break;
				
			case GP2X_BUTTON_RIGHT:
				inputController.setStatus(GKEY_RIGHT, lb_pressed);
				break;
				
			case GP2X_BUTTON_DOWN:
				inputController.setStatus(GKEY_DOWN, lb_pressed);
				break;
				
			case GP2X_BUTTON_A:
				break;

			case GP2X_BUTTON_B:
				break;

			case GP2X_BUTTON_Y:
				inputController.setStatus(GKEY_LONG_JUMP, lb_pressed);
				break;

			case GP2X_BUTTON_X:
				inputController.setStatus(GKEY_SHORT_JUMP, lb_pressed);
				break;
				
			case GP2X_BUTTON_VOLDOWN:
				inputController.setStatus(GKEY_VOLUME_DOWN, lb_pressed);
				break;
				
			case GP2X_BUTTON_VOLUP:
				inputController.setStatus(GKEY_VOLUME_UP, lb_pressed);
				break;
				
			case GP2X_BUTTON_SELECT:
				inputController.setStatus(GKEY_SELECT, lb_pressed);
				break;
				
			case GP2X_BUTTON_HOME:
				inputController.setStatus(GKEY_ABORT, lb_pressed);
				break;
		}
	}

#else

    void TProfanationGame::updateInputController()
    {
        inputController.setStatus(GKEY_LEFT, KeyState[SDLK_LEFT]);
        inputController.setStatus(GKEY_RIGHT,KeyState[SDLK_RIGHT]);
        inputController.setStatus(GKEY_UP,   KeyState[SDLK_UP]);
        inputController.setStatus(GKEY_DOWN, KeyState[SDLK_DOWN]);
    
        inputController.setStatus(GKEY_LONG_JUMP, KeyState[SDLK_UP]);
        inputController.setStatus(GKEY_SHORT_JUMP,KeyState[SDLK_DOWN]);
    
        inputController.setStatus(GKEY_SELECT,KeyState[SDLK_RETURN]);
        inputController.setStatus(GKEY_ABORT,KeyState[SDLK_ESCAPE]);

        inputController.setStatus(GKEY_VOLUME_UP,KeyState[SDLK_PAGEUP]);
        inputController.setStatus(GKEY_VOLUME_DOWN,KeyState[SDLK_PAGEDOWN]);

        inputController.setStatus(GKEY_SCR_PLUS,KeyState[SDLK_KP_PLUS]);
        inputController.setStatus(GKEY_SCR_MINUS,KeyState[SDLK_KP_MINUS]);
    };

#endif 

void TProfanationGame::cleanup(void) {}

void TProfanationGame::showFullScreen(bool fs)
{
    config_fullscreen = fs;    
    TMAGame::setFullScreen(fs);
    saveConfiguration();
}

void TProfanationGame::increaseVolume()
{
    if (TProfanationGame::gi_volume<128) 
    {
        TProfanationGame::gi_volume+=10;
        if (TProfanationGame::gi_volume>128) TProfanationGame::gi_volume=128;
        setVolume(TProfanationGame::gi_volume);
        saveConfiguration();
    }
}

void TProfanationGame::decreaseVolume()
{
    if (TProfanationGame::gi_volume>0) 
    {
        TProfanationGame::gi_volume-=10;
        if (TProfanationGame::gi_volume<0) TProfanationGame::gi_volume=0;
        setVolume(TProfanationGame::gi_volume);
        saveConfiguration();
    }
}

// --------- INICIALIZACION DEL JUEGO
//
bool TProfanationGame::init(void)
{ 
    lb_init=false; 
     
    if (!TMAGame::init()) return false;
    inputController.setNumControls(GKEY_MAX);
    loadConfiguration();
    
    if (!setGraphicsMode(640/_REDUCE,480/_REDUCE,16,config_fullscreen)) return false;
    
    setWindowTitle("Abusimbel Profanation Deluxe");
    setGameFPS(32);
    
    lb_init = true;
                
    // Cargamos los tipos de letras constantes en el juego
    //
    #ifdef SMALL_GAME
        fontMulti.load("Data/Fonts/FuenteMulti.png",10,15,gs_charset.length(),1,false,0);
        fontBlue.load("Data/Fonts/FuenteBlue.png",10,15,gs_charset.length(),1,false,0);
    #else
        fontMulti.load("Data/Fonts/FuenteMulti.png",20,30,gs_charset.length(),1,false,MAKERGBCOLOR(255,0,255));
        fontBlue.load("Data/Fonts/FuenteBlue.png",20,30,gs_charset.length(),1,false,MAKERGBCOLOR(255,0,255));
    #endif
    fontMulti.setCharacters(*gs_charset);
    fontBlue.setCharacters(*gs_charset);
    
    // Cargamos los sonidos
    //
    if (isSoundAvailable())
    {
        setVolume(gi_volume);
        gsnd_Gota.load("Data/Sonidos/gota.wav");
        gsnd_Roca.load("Data/Sonidos/roca.wav");
        gsnd_Camina.load("Data/Sonidos/camina.wav");
        gsnd_Salto.load("Data/Sonidos/salto.wav");
        gsnd_Caida.load("Data/Sonidos/caida.wav");
        gsnd_Tesoro.load("Data/Sonidos/tesoro.wav");
        gsnd_Scroll.load("Data/Sonidos/scroll.wav");
        gsnd_Teletransporte.load("Data/Sonidos/teletransporte.wav");
        gsnd_Grito.load("Data/Sonidos/grito.wav");
    }
    
    miRND.init();
    
    // Establecemos el escenario inicial
    //    
    setScene(new TESC_Seleccion_Idioma());
    
    return true;
}

void TProfanationGame::doRun(void)
{
    if (inputController.isPressDown(TProfanationGame::GKEY_ABORT))
    {
        this->endGame();
        return;
    }
    
    if (inputController.isPressDown(TProfanationGame::GKEY_VOLUME_DOWN)) decreaseVolume();
    if (inputController.isPressDown(TProfanationGame::GKEY_VOLUME_UP)) increaseVolume();
}

void TProfanationGame::doPaint(TMABitmap& buff)
{
    buff.clear(0);
};

void TProfanationGame::loadConfiguration(void)
{
 config_fullscreen = false;
 
 // Intentamos abrir el archivo de configuracion
 //
 FILE *f = fopen("Data/config","rb");
 
 // Si no existe, intentamos crear uno con los valores actuales.
 //
 if (!f)
 {
  saveConfiguration();
  return;
 }
 
 // Leemos los valores.
 //
 fread(&config_fullscreen,sizeof(config_fullscreen),1,f);
 fread(&TProfanationGame::gi_idioma,sizeof(TProfanationGame::gi_idioma),1,f);
 fread(&TProfanationGame::gi_idioma_anterior,sizeof(TProfanationGame::gi_idioma_anterior),1,f);
 fread(&TProfanationGame::gi_volume,sizeof(TProfanationGame::gi_volume),1,f);
 fclose(f);
}

void TProfanationGame::saveConfiguration(void)
{
 // Intentamos crear el archivo de configuracion
 //
 FILE *f = fopen("Data/config","wb");
 
 // Si no podemos crearlo, desistimos
 //
 if (!f) return;
 
 // Escribimos los valores.
 //
 config_fullscreen = (lb_init)?this->isFullScreen():false;
 fwrite(&config_fullscreen,sizeof(config_fullscreen),1,f);
 fwrite(&TProfanationGame::gi_idioma,sizeof(TProfanationGame::gi_idioma),1,f);
 fwrite(&TProfanationGame::gi_idioma_anterior,sizeof(TProfanationGame::gi_idioma_anterior),1,f);
 fwrite(&TProfanationGame::gi_volume,sizeof(TProfanationGame::gi_volume),1,f);
 fclose(f);
}

int MainProc(int argc, char** argv)
{ 

	#if !defined(TARGET_GP2X) && !defined(TARGET_WII)
		// Establecemos como ruta la misma del ejecutable.
		//
		char *path = strdup(argv[0]);
		int lsize = strlen(path)-1;
		while (lsize>1 && path[lsize]!='\\' && path[lsize]!='/') path[lsize--]=0;
		chdir(path);
		free(path);
	#endif

    TProfanationGame miGame;
    
    if (miGame.init())
    {
        miGame.run();
        
        return 0;
    }
    else
    {
        miGame.showAlert("No se pudo inicializar la aplicación.");
    }
    return -1;    
}

#endif
