#ifndef _PROFANATION_H_
#define _PROFANATION_H_

#include "../ma-sdl/ma_classes.h"
#include "../ma-sdl/maps/mapas.h"

#ifdef SMALL_GAME
    #define _REDUCE 2
#else
    #define _REDUCE 1
#endif


#ifdef TARGET_WII
	
    #include <wiiuse/wpad.h>
	
#elif defined(TARGET_GP2X)
    
    #define GP2X_BUTTON_UP              (0)
	#define GP2X_BUTTON_DOWN            (4)
	#define GP2X_BUTTON_LEFT            (2)
	#define GP2X_BUTTON_RIGHT           (6)
	#define GP2X_BUTTON_UPLEFT          (1)
	#define GP2X_BUTTON_UPRIGHT         (7)
	#define GP2X_BUTTON_DOWNLEFT        (3)
	#define GP2X_BUTTON_DOWNRIGHT       (5)
	#define GP2X_BUTTON_CLICK           (18)
	#define GP2X_BUTTON_A               (12)
	#define GP2X_BUTTON_B               (13)
	#define GP2X_BUTTON_X               (15)
	#define GP2X_BUTTON_Y               (14)
	#define GP2X_BUTTON_L               (11)
	#define GP2X_BUTTON_R               (10)
	#define GP2X_BUTTON_HOME            (8)
	#define GP2X_BUTTON_SELECT          (9)
	#define GP2X_BUTTON_VOLUP           (16)
	#define GP2X_BUTTON_VOLDOWN         (17)
	
#endif

class TProfanationGame:public TMAGame
{
    REGISTER_CLASS protected:
        
    public:
        PUBLIC_CLASS_ID;
        
        // Idiomas y Juegos de Caracteres
        //
        static TMAString gs_charset;
        static const int LG_SPAIN=0;
        static const int LG_ENGLISH=1;
        static const int LG_FRENCH=2;
        static const int LG_DEUTCH=3;
        
        // Valores de las teclas
        //
        static const int GKEY_LEFT=0;
        static const int GKEY_RIGHT=1;
        static const int GKEY_UP=2;
        static const int GKEY_DOWN=3;
        static const int GKEY_LONG_JUMP=4;
        static const int GKEY_SHORT_JUMP=5;
        static const int GKEY_SELECT=6;
        static const int GKEY_ABORT=7;
        static const int GKEY_VOLUME_UP=8;
        static const int GKEY_VOLUME_DOWN=9;
        static const int GKEY_SCR_PLUS=10;
        static const int GKEY_SCR_MINUS=11;
        static const int GKEY_MAX=12;
                        
        // Mapas y Tipos de Letras
        //
        static int gi_idioma,gi_idioma_anterior,gi_volume; 
        TMAFont fontBlue;
        TMAFont fontMulti;
        
        bool config_fullscreen;
        bool lb_init;
        
        TMASound gsnd_Gota;
        TMASound gsnd_Roca;
        TMASound gsnd_Camina;
        TMASound gsnd_Salto;
        TMASound gsnd_Caida;
        TMASound gsnd_Tesoro;
        TMASound gsnd_Scroll;
        TMASound gsnd_Teletransporte;
        TMASound gsnd_Grito;
        
        TMARandom miRND;
        
        // Constructor y Métodos
        //
        ~TProfanationGame();  
        
        bool init(void);
        void cleanup(void);
        void doRun(void);
        void doPaint(TMABitmap&);
        
        void loadConfiguration(void);
        void saveConfiguration(void);
        
        void showFullScreen(bool);
        
        void increaseVolume(void);
        void decreaseVolume(void);
        
		#ifdef TARGET_GP2X
            void updateInputController(SDL_Event&);
        #else
            void updateInputController();
        #endif
};

#endif
