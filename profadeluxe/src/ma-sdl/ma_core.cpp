#ifndef _MA_CORE_CPP_
#define _MA_CORE_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMAObject);

TMAObject::~TMAObject(){}

bool TMAObject::isInstanceOf(long class_id)
{
    return (classID()==class_id);
}
long TMAObject::getClassID(void)
{
    return classID();
}

// Punto de entrada principal, que se redireccionara al metodo MainProc
//
int main(int argc,char **argv) 
{
    TMAGame::ARGC = argc;
    TMAGame::ARGV = argv;
      
    if((SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return -1;
    }
    TMAGame::setSoundAvailable(true);
 
 	#if defined(TARGET_GP2X) 
	
    	Mix_OpenAudio(32000, AUDIO_S16, MIX_DEFAULT_CHANNELS, 128); // Initialize SDL_mixer for GP2X, buffer is set lower than PC
	
    #elif defined(TARGET_WII)
	
		// Inicializamos el sistema FAT y Mando de Wii
		//
		if (!fatInitDefault()) return -1;
        SDL_EnableUNICODE(true);     
		WPAD_Init();
		Mix_OpenAudio(32000, AUDIO_S16MSB , MIX_DEFAULT_CHANNELS, 4096); // Initialize SDL_mixer for Wii, buffer is set higher
	
    #else
	
        SDL_EnableUNICODE(true);     
		Mix_OpenAudio(32000, AUDIO_S16, MIX_DEFAULT_CHANNELS, 4096); // Initialize SDL_mixer for PC, buffer is set higher		
	
    #endif

    if (SDL_JoystickOpen(0)) TMAGame::setJoystickAvailable(true);
     
    int ret = MainProc(argc,argv);

	Mix_CloseAudio();	
	SDL_Delay(1000);
	
	#ifndef TARGET_GP2X
		SDL_Quit();
	#else
		chdir("/usr/gp2x");
		execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
	#endif

	return ret;
}

#endif
