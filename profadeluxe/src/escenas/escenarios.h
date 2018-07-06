#ifndef _ESCENARIOS_H_
#define _ESCENARIOS_H_

#include "../main/profanation.h"
#include "../sprites/sprites.h"

#define _MAX_SPRITES_       5
#define _MAX_ENEMIGOS_      3
#define _MAX_SPR_PARAMS_    7
#define _MAX_PANTALLAS_     45

typedef struct
{
    // Enemigos en las pantallas.
    //
    int enemigos[_MAX_ENEMIGOS_][_MAX_SPR_PARAMS_];

    // Indicador de visita de pantalla.
    //
    bool visitada;

    // Indicadores de control de tesoros.
    int  hay_tesoro;
    int  hay_poner_tesoro;
    bool tesoro_cogido;
    bool tesoro_puesto;
    
    // Conexion de pantallas.
    //
    int scrLeft,scrTop,scrRight,scrBottom;

} ScrInfo;

typedef struct
{
    const char *txt;
    int y;
    bool rainbow;
} TTextoScroll;


// Escenario de seleccion de idioma e historia
//
class TESC_Seleccion_Idioma:public TMAScene
{
    REGISTER_CLASS protected:
        
        static TMAString ia_himnos[4][2];
        static int ia_cursor_pos[4];
        
        TProfanationGame *miGame;        
        TMAGameMap map;
        PMAScreenMap io_Screen;
        
        TMAVector iv_Historia;
        PMABitmap masoft;
        int li_alpha;
        TMAOgg  io_ogg;
        TSprSeleccion* sprSeleccion;
        
        void scrollText(TMABitmap&);
        
    public:
        PUBLIC_CLASS_ID;
        TESC_Seleccion_Idioma();
        ~TESC_Seleccion_Idioma();
        
        bool doInit(const PMAObject params);
        bool doRun(void);
        void doPaint(TMABitmap&);
        
        void doRunLanguage(void);
        void doPaintLanguage(TMABitmap&);
        
        void playCountryMidi(void);
        void languageChanged(void);
        
        void gotoMainMenu(void);
        void gotoSelectLanguage(void);
};

class TESC_Juego:public TMAScene
{     
    REGISTER_CLASS protected:

    static ScrInfo ia_ScrInfo[_MAX_PANTALLAS_];
    static const char *ia_txt_sp[];
    static const char *ia_txt_en[];
    static const char *ia_txt_fr[];
    static const char *ia_txt_de[];
    static int ia_recorrido_pantallas[_MAX_PANTALLAS_];    

    int buffertesoro[2];
    TProfanationGame *miGame;

    // Estados del Juego
    //
    enum TGameState { ST_MENU=0,ST_GAME=7,ST_INSTRUCTIONS=500,ST_ABOUT=501,ST_ENDGAME=800,ST_SHOWSCREENS=1000,ST_CRACK=10000 };
    TGameState ii_EstadoJuego;
    void setState(TGameState st) { ii_EstadoJuego = st; }
    
    // Referencia al idioma seleccionado.
    const char **ia_txt;
    int ii_OpcionMenu;
    int ii_offsety_menutxt[640];
    int ii_texto_scroll,ii_texto_scroll1;
    int ii_texto_buff_index;
    TTextoScroll ia_texto_buff[30];

    TSpriteEnemigo *lst_Sprites[_MAX_SPRITES_];

    void pf_AnimaSprites(void);
    void pf_LimpiarSprites(void);
    void pf_CrearSprites(int pantalla);
    void pf_PrepararPantalla(int pantalla);
    void pf_PrepararScrollTesoro(void);
    void pf_PreparaTextoScroll(int nm);

    // Manejadores de los distintos estados del juego.
    //
    void pf_DibujaMenu(TMABitmap& buff);
    void pf_DibujaRecorridoPorPantallas(TMABitmap& buff);
    void pf_DibujaJuego(TMABitmap& buff);
    void pf_DibujaInstrucciones(TMABitmap& buff);
    void pf_DibujaFinalJuego(TMABitmap& buff);
    void pf_DibujaPantalla(TMABitmap& buff,bool johny);

    void pf_AnimInstrucciones();
    void pf_AnimFinalJuego();
    
    // Gestion de tabla de senos para menu
    //
    void pf_rellenaTablaSenosMenu(int radio,int arcos);
    void pf_rotarTablaSenosMenu(void);
    void pf_comenzarPartida(void);
    void pf_menuPrincipal(void);
    void pf_buscarPosicionInicialJohny(void);
    
    void pf_DetectCrack(void);
    
    // Gestión del paso de pantalla
    //
    bool pf_PasoPantalla(void);
    void pf_GestionaCrack(void);
    
    TSprJohny  sprJohny;
    TSprTesoro sprScroll;
    int ii_pantallas_visitadas,ii_pantalla;
    bool ib_transitando;

    long il_pausa_recorrido_pantalla;
    bool VICTOR[6];
    char ia_password[50];
    bool ib_inmune,ib_vidas_infinitas;
    bool ib_situando_a_johny;

    // Diamante Seleccionado
    //
    int ii_color_diamante;

    // Musica
    //
    TMAOgg  io_ogg;
    TMAScreenMap *io_current_screen;
    TMAGameMap GameMap;
        
public:			
	
	// Constructor / Destructor
	TESC_Juego();
   ~TESC_Juego();
	
	bool doInit(const PMAObject params);
    bool doRun(void);
    void doPaint(TMABitmap&);   
	
    bool AbiertaPuertaSecreta(void);
    void CogerTesoro(void);
    void PonerTesoro(void);
};

#endif
