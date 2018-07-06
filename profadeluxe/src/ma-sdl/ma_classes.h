#ifndef _MA_SDL_H_
#define _MA_SDL_H_

#include <stdlib.h>
#include "ma_object.h"
#include "utils/utils.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>

#define max(x,y) (x>=y)?x:y
#define min(x,y) (x<=y)?x:y

#define MAKERGBCOLOR(r,g,b) ( (r<<24)|(g<<16)|(b<<8)|0xFF )
#define MAKERGBACOLOR(r,g,b,a) ( (r<<24)|(g<<16)|(b<<8)|a )

#define GET_REDVALUE(color) ( (color>>24) & 0xFF )
#define GET_GREENVALUE(color) ( (color>>16) & 0xFF )
#define GET_BLUEVALUE(color) ( (color>>8) & 0xFF )
#define GET_ALPHAVALUE(color) ( color & 0xFF )

#ifdef TARGET_GP2X
	#include <unistd.h>
	#include <string.h>
#endif

#ifdef TARGET_WII
	#include <gccore.h>
	#include <wiiuse/wpad.h>
	#include <fat.h>	
#endif	

// Definición de Prototipos y Tipos de Datos, 
// para facilitar referencias cruzadas
//
class TMABitmap;
class TMAGame;
class TMAScene;
class TMAImageBank;
class TMASprite;
class TMAFont;
class TMASound;
class TMAOgg;
class TMAInputController;

typedef TMABitmap *PMABitmap;
typedef TMAGame* PMAGame;
typedef TMAScene *PMAScene;
typedef TMAImageBank* PMAImageBank;
typedef TMASprite *PMASprite;
typedef TMAFont* PMAFont;
typedef TMASound* PMASound;
typedef TMAOgg*  PMAOgg;
typedef TMAInputController* PMAInputController;


// ****************************************
// Clase que encapsula un BITMAP: TMAObject
// ****************************************
//
class TMABitmap : public TMAObject
{
    REGISTER_CLASS protected:
        
        friend class TMAGame;

        static PMAGame GMAGame;
        SDL_Surface *io_bmp;
        bool ib_destroy;
    
        TMABitmap(SDL_Surface*,bool shared=false);       
        
    public:
        PUBLIC_CLASS_ID;
        
        ~TMABitmap();

    // ***********************************************
    // Métodos de creación de BITMAPS/Buffers Graficos
    // ***********************************************
        
        // Crea un bitmap a partir de un archivo de imagen
        //
        static PMABitmap loadFromFile(const char *filename,bool compatible=false);
                
        // Crea un bitmap de la misma profundidad que la pantalla actual.
        // Puede crearse en memoria de video.
        //
        static PMABitmap create(int width,int height,bool videomem);
        
        // Crea un bitmap del tamaño y profundidad especificados.
        //
        static PMABitmap create(int width,int height,int depth);
        
        // Crea un nuevo bitmap, del mismo tamaño y caracteristicas
        // del indicado como argumento.
        //
        static PMABitmap create(PMABitmap);

        // Crea un nuevo bitmap, compartiendo memoria con otro existente.
        // El existente, nunca debe ser liberado antes que este.
        //
        static PMABitmap create(PMABitmap,int x,int y,int width,int height);

        // Devuelve la referencia al BITMAP interno..
        //
        inline SDL_Surface *getInternalBitmapRef(void) { return io_bmp; }

        // Devuelve una copia del bitmap
        //
        PMABitmap clone(void);
        
        // Devuelve una copia del bitmap, pero con flips
        //
        PMABitmap cloneFlipX(void);
        PMABitmap cloneFlipY(void);
        PMABitmap cloneFlipXY(void);        
                        
    // ****************************************
    // Métodos para la obtención de propiedades
    // ****************************************
        
        bool saveToFile(const char *filename);
        int getColorDepth(void);
        int getWidth(void);
        int getHeight(void);
        void getSize(int& width,int& height);

    // **************************************
    // Métodos operaciones sobre el TMABitmap
    // **************************************

        void lock(void);
        void unlock(void);

        bool makeDisplayCompatible(void);
        bool makeDisplayCompatibleWithAlpha(void);

        bool copyPalette(const PMABitmap);
        void setTransparentColor(Uint32 color);
        void unsetTransparentColor(void);
        bool isTransparent(void);
        
        void clear(Uint8 red,Uint8 green,Uint8 blue);
        void clear(Uint32 color);
        
        void draw(const PMABitmap,int px,int py);
        void draw(const PMABitmap,int ox,int oy,int width,int height,int dx,int dy);
        void drawSprite(const PMABitmap,int px,int py,bool flipx=false,bool flipy=false);
        void drawSpriteColorized(const PMABitmap,int px,int py,bool flipx=false,bool flipy=false,int r=255,int g=255,int b=255);
        void drawSpriteShadowed(const PMABitmap spr,int px,int py,bool flipx=false,bool flipy=false,int alpha=150);
        void drawLine(int ox,int oy,int dx,int dy,Uint32 color);
        void drawRect(int ox,int oy,int dx,int dy,Uint32 color);
        void drawRectFilled(int ox,int oy,int dx,int dy,Uint32 color);
        void drawCircle(int cx,int cy,int radio,Uint32 color);
        void drawCircleFilled(int cx,int cy,int radio,Uint32 color);               
        void drawEllipse(int cx,int cy,int radiox,int radioy,Uint32 color);
        void drawEllipseFilled(int cx,int cy,int radiox,int radioy,Uint32 color);

        void   setPixel(int px,int py,Uint32 color);
        Uint32 getPixel(int px,int py);        

        // ------------ Operaciones Alpha
        //
        bool isAlpha(void);
        void setAlpha(int alpha);
        void disableAlpha(void);
        
        // ------------ Operaciones de Resize y Filtrado
        //
        void bilinearStretch(const PMABitmap,int ox,int oy,int owidth,int oheight,
                            int dx,int dy,int dwidth,int dheight);
};

// ***********************************
// Clase principal del nucleo: TMAGame
// ***********************************
//
class TMAGame : public TMAObject
{
    REGISTER_CLASS protected:

        friend class TMABitmap;
        
        static TMAGame* oc_MAGame;
        static bool ci_endgame;
        static bool ib_soundAvailable;
        static bool ib_joystickAvailable;
        static SDL_Surface *ScreenSurf;
        static PMABitmap Screen;
        static int ii_last_ascii_key;

        int ii_game_speed;
                
        PMAScene io_current_scene;
        PMAScene io_next_scene;
        bool ib_remove_last_scene;
        
		#ifdef TARGET_GP2X
			void handleGP2XButtons(int key,bool down);
		#endif
		
		#ifdef TARGET_WII
			void handleWiiButtons();
		#endif
        
    public:
        PUBLIC_CLASS_ID;
        static const int KEY_MAX = 512;
        static bool KeyState[KEY_MAX];
        static long il_time_millis;
        static int ARGC;
        static char **ARGV;
        static TMAInputController inputController;

        // Constructor y Destructor
        //
        TMAGame(void);
        virtual ~TMAGame();
        
        // Devuelve un puntero a la instancia del juego actual.
        //
        static TMAGame *getCurrentGame(void);          
                
        // Detiene la ejecución durante ciertos milisegundos
        //
        static void sleep(int ms);
        
        // Devuelve el tiempo actual en milisegundos
        //
        static long getCPUTime(void);
        
        // Limpia el buffer de teclas y los flags de estados
        //
        void releaseKeys(void);
        
        // En este método especificarse la rutina de inicialización global 
        // del juego
        //
        virtual bool init(void) { return true; }
        
        // En este método especificarse la rutina de limpieza global 
        // del juego
        //
        virtual void cleanup(void);
    
        // Refresca la información de controles de movimiento
        //
        virtual void updateInputController(void){}
        virtual void updateInputController(SDL_Event&){}
                  
        // Este método se debe invocar para que comience el ciclo principal
        // del juego
        //
        void run(void);
        
        // Método para mostrar mensajes de Error
        //
        static void showAlert(const char *);      // Muestra una alerta.
        static void showLastAlert();        // Muestra la ultima que genero un error.
        void showFatalError(const char *);        // Muestra una alerta y cierra la aplicación.
         
        // Establece o Recupera el escenario del juego
        //
        bool setScene(PMAScene,const PMAObject params = NULL,bool remove_last=true);
        const PMAScene getScene(void) { return io_current_scene; }
         
    // ***********************************
    // Métodos de control sobre el entorno
    // *********************************** 
        
        // Incializa el modo grafico.
        //
        bool setGraphicsMode(int width,int height,int colordepth,bool fullscreen);
        bool setFullScreen(bool fs);
        bool isFullScreen(void);
        
        // Establece el titulo de la ventana principal.
        //   
        void setWindowTitle(const char *);
        
        // Devuelve el tamaño ancho/alto de pantalla establecido
        //
        const PMABitmap getScreen(void) { return Screen; }
        void getScreenSize(int& width,int& height);
        int getScreenWidth(void);
        int getScreenHeight(void);
        int getScreenDepth(void);
        void FlipScreen(void);
        
    // ***********************************
    // Métodos de control sobre el flujo
    // *********************************** 
    
        // Establece la velocidad de refresco del juego en Frames por Segundo
        // por defecto se asume 0 fps, lo que hace que exista la máxima 
        // velocidad posible.
        //
        void setGameFPS(int fps);

        // Este método se invoca en cada iteración del juego.
        // La idea es introducir aqui llamadas a calculos o controles.
        // Si existe una escena asignada, TMAScene, se invoca el doRun 
        // de la escena, en otro caso, se invoca el del juego.
        //
        virtual void doRun(void){};

        // Este método se invoca en cada iteración del juego para
        // que se dibuje lo que sea necesario.
        // Si existe una escena asignada, TMAScene, se invoca el doPaint
        // de la escena, en otro caso, se invoca el del juego.
        //
        virtual void doPaint(TMABitmap&) {};
        
        // Este método termina con la ejecución del juego.
        //
        static void endGame(void);

    // *******************************************
    // Métodos de control sobre sonido y joystick
    // *******************************************
    
        static bool isSoundAvailable(void) { return ib_soundAvailable; }
        static void setSoundAvailable(bool av) {  ib_soundAvailable=av;}

        static bool isJoystickAvailable(void) { return ib_joystickAvailable; }
        static void setJoystickAvailable(bool av) {  ib_joystickAvailable=av;}

    // *****************************
    // Métodos del control de idioma
    // *****************************
    
        static void setupLanguage(const char *domain,const char *locale);
        
    // Obtiene el valor ascii de la ultima tecla pulsada, si aun lo esta
    // en otro caso, de vuelve 0.
    
        static int getLastAsciiKeyPressed(void);
        static void releaseLastAsciiKeyPressed(void);
        
    // Establece el volumen
    
        void setVolume(int v);    
    
};

// ****************************************
// Clase que encapsula una escena: TMAScene
// ****************************************
//
class TMAScene : public TMAObject
{
    REGISTER_CLASS protected:
                
        bool ib_initialized;
        int ii_Estado;
        
    public:
        PUBLIC_CLASS_ID;
        TMAScene();
        
        virtual bool doInit(const PMAObject params=NULL);
        
        // Este método se invoca en cada iteración del juego.
        // La idea es introducir aqui llamadas a calculos o controles.
        //
        virtual bool doRun(void){ return false; };
        
        // Este método se invoca en cada iteración del juego para
        // que se dibuje lo que sea necesario.
        //
        virtual void doPaint(TMABitmap&){};
        
        bool isInitialized(void) { return ib_initialized; }
};        

// *************************************************
// Clase que encapsula un BANCO de IMAGENES: TMAGame
// *************************************************
//
class TMAImageBank : public TMAObject
{
    REGISTER_CLASS protected:
        
        TMAImageBank();
        TMAVector vector;
        PMABitmap imgsource;
        
    public:
        PUBLIC_CLASS_ID;
        
        ~TMAImageBank();
        
        // Crea un banco de imágenes de tamaño fijo a partir de un TMABitmap
        // La imagen original no se destruye, pero una vez creado el banco
        // tampoco se hace referencia a ella.
        //
        static PMAImageBank createStatic(TMABitmap&,int tx,int ty,int ax,int ay,bool separator=false);
        
        // Crea un banco de imágenes de tamaño fijo a partir de un archivo de imagen
        // 
        static PMAImageBank createStatic(const char *filename,int tx,int ty,int ax,int ay,bool separator=false);
        
        // Crea un banco de imágenes donde cada imagen puede ser de un tamaño, a partir
        // de un bitmap y un vector de objetos (TMARectangle)
        //
        static TMAImageBank *createDynamic(TMABitmap&,TMAVector& zonas);
        
        // Crea un banco de imágenes donde cada imagen puede ser de un tamaño, a partir
        // de un bitmap y un vector de objetos (TMARectangle)
        //
        static TMAImageBank *createDynamic(const char *filename,TMAVector& zonas);
        
        // Devuelve una imagen del banco de imágenes, que esta indexada
        // por el indice especificado.
        //
        const PMABitmap getBitmap(int index);
        
        // Devuelve el numero de entradas en el banco.
        //
        long size(void);
        
        // Devuelve una copia de este image bank
        //
        //PMAImageBank clone(void);
};

// ****************************************
// Clase que encapsula un sprite: TMASprite
// ****************************************
//
class TMASprite : public TMAObject
{
    REGISTER_CLASS protected:
 
        bool ib_valido;                 // Indica si es valido
        int  ii_Frame;                  // Fotograma actual
        int  ii_Retardo;                // Retardo de fotograma
        int  ii_RetardoPos;             // Contador de Retardo
        const int *ia_AnimSequence;     // Secuencia de animación actual
        int  ii_AnimSequenceLength;     // Secuencia de animación actual
        int  ii_EstadoAnim;             // Estado de la animación actual
        int  ii_Estado;                 // Estado general del Sprite
        int  ii_CurrentFotograma;       // Fotograma Actual
        bool ib_flip_x;                 // Sprite invertido X
        bool ib_flip_y;                 // Sprite invertido Y
        
        PMAImageBank io_images;   // Banco de Imágenes
        
    public:
        PUBLIC_CLASS_ID;
        TMARectangle position;        
        
        TMASprite(PMAImageBank);
        virtual ~TMASprite(){}
       
        bool isValid(void)      { return ib_valido;}
        void validate(void)     { ib_valido=true; }
        void invalidate() 		{ ib_valido=false; }
        void setFlipX(bool b)	{ ib_flip_x = b; }
        void setFlipY(bool b)	{ ib_flip_y = b; }
        bool isFlippedX(void)   { return ib_flip_x; }
        bool isFlippedY(void)   { return ib_flip_y; }
        
        virtual void animate(void);
        virtual bool isCollisioningWith(TMASprite& s);
        virtual void putAt(int x,int y) { position.x = x; position.y = y; }	
        virtual bool draw(TMABitmap&);
        
        void setAnimSequence(const int *,int length);
};

// *****************************************************
// Clase que encapsula un tipo de letra grafico: TMAFont
// *****************************************************
//
class TMAFont : public TMAObject
{
    REGISTER_CLASS protected:
        
        PMAImageBank io_bank;
        int width,height;
        int ii_spacex,ii_transcolor;
        const char *is_chars;
        
    public:
        PUBLIC_CLASS_ID;
        
        TMAFont();
        ~TMAFont();
        
        // Carga un tipo de letra.
        //
        bool load(const char *fontFile,int width,int height,int col,int row,
                  bool pixel_separator=false,int transcolor=0);
	        
        // Establece el espacio horizontal entre caracteres.
        //
        void setSpaceBetweenChars(int);
        
        // Establece el juego de caracteres
        //
        void setCharacters(const char *);
        
        // Devuelve la anchura de un texto
        //
        int getTextWidth(const char *);
        
        // Devuelve la altura de un texto
        //
        int getTextHeight(void);
        
        // Dibuja un texto sobre un bitmap.
        // Si X=-1, se centra el texto en horizontal, asumiendo que la anchura
        // de la pantalla se indica en el parametro "scrwidth"
        // El parametro offsety, puede apuntar a un array de enteros que se modificaran
        // la posición Y de cada letra. Debe contener tantos elementos como la anchura
        // de la pantalla.
        //
        void drawText(TMABitmap&,const char *text,int x, int y,int *offsety=NULL,
                      int scrwidth=0);
                      
        void setAlpha(int);
        void disableAlpha(void);
};

// ***************************************
// Clase que encapsula un sonido: TMASound
// ***************************************
//
class TMASound : public TMAObject
{
    REGISTER_CLASS protected:
        
        Mix_Chunk *psound; 
        int ii_voice;   
        
    public:
        PUBLIC_CLASS_ID;
        
        TMASound();
       ~TMASound();
       
        bool load(const char *filename);
        void unload(void);
        void play(bool loop=false,int volume=32,int pan=127);
        void stop(void);
        bool isPlaying(void);
};

// **************************************************
// Clase que encapsula un sonido Ogg en disco: TMAOgg
// **************************************************
//
class TMAOgg : public TMAObject
{
    REGISTER_CLASS protected:
                
        Mix_Music *psound; 
                
    public:
        PUBLIC_CLASS_ID;
        
        TMAOgg();
       ~TMAOgg();
       
        bool load(const char *filename);
        void close(void);
        void play(bool loop=false,int volume=32);
        void stop(void);
        bool isPlaying(void);
};

// **************************************************
// Clase que encapsula un sonido Ogg en disco: TMAOgg
// **************************************************
//
class TMAInputController : public TMAObject
{
    REGISTER_CLASS protected:
                
        int buffSize;
        bool *buffHoldDown;
        bool *buffPressDown;
        void clearBuff();
                
    public:
        PUBLIC_CLASS_ID;
        
        TMAInputController();
       ~TMAInputController();
       
        void setNumControls(int num);

        void clearStatus();
        void clearStatus(int num);
        void setStatus(int num,bool status);
        
        bool isHoldDown(int num);
        bool isAnyHoldDown(void);
        bool isPressDown(int num);
};

#endif
