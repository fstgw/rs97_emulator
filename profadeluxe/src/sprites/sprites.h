#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "../ma-sdl/ma_classes.h"
#include "../ma-sdl/maps/mapas.h"

#ifdef SMALL_GAME
    #define _RadioSaltoLargo   90
    #define _RadioSaltoCorto    5
    #define _TileAX 10
    #define _TileAY 10
#else
    #define _RadioSaltoLargo   180
    #define _RadioSaltoCorto    10
    #define _TileAX 20
    #define _TileAY 20
#endif

// -------------- Prototipos
//
class TESC_Seleccion_Idioma;
class TESC_Juego;



// -------------- TSpriteSeleccion
//
class TSprSeleccion : public TMASprite
{
    REGISTER_CLASS protected:

    	static const int ia_anim_idioma[2];
    	static const int ia_anim_game[2];
    	
        TMARectangle ir_destino;
        TESC_Seleccion_Idioma *notify;
    	bool ib_moviendo;
    	int ii_vel;
	
	public:
        PUBLIC_CLASS_ID;
        
        int gi_idioma;
        
        TSprSeleccion(PMAImageBank,bool idioma,TESC_Seleccion_Idioma* esc=NULL);
        void moveTo(int x,int y);
        void animate(void);
        bool isMoving(void) { return ib_moviendo; }	
};

//-----------------------------------------------------------------------------
// Tipos de Sprites
//-----------------------------------------------------------------------------

typedef enum {
    TSPR_SPRITE             = 0,
    TSPR_JOHNY              = 1,
    
    TSPR_GOTA_ROJA          = 2,
    TSPR_GOTA_VERDE         = 3,
    TSPR_GOTA_AZUL          = 4,
    TSPR_GOTA_AMARILLA      = 5,

    TSPR_SERPIENTE_ROSA     = 6,
    TSPR_SERPIENTE_AMARILLA = 7,
    TSPR_SERPIENTE_VERDE    = 8,
    TSPR_SERPIENTE_AZUL     = 9,

    TSPR_HBABOSA_AMARILLA   = 10,
    TSPR_HBABOSA_VERDE      = 11,
    TSPR_HBABOSA_ROJA       = 12,

    TSPR_MOMIA_AZUL         = 13,
    TSPR_MOMIA_VERDE        = 14,
    TSPR_MOMIA_ROJA         = 15,

    TSPR_RAYO_MORADO        = 16,
    TSPR_RAYO_AMARILLO      = 17,
    TSPR_RAYO_VERDE         = 18,
    TSPR_RAYO_AZUL          = 19,

    TSPR_VTABLA_ROJA        = 20,
    TSPR_VTABLA_MARRON      = 21,
    TSPR_VTABLA_MORADA      = 22,

    TSPR_VSPIDER_VERDE      = 23,
    TSPR_VSPIDER_ROJO       = 24,
    TSPR_VSPIDER_AZUL       = 25,

    TSPR_VTORNILLO_AZUL     = 26,
    TSPR_VTORNILLO_AMARILLO = 27,

    TSPR_HPELOTA_ROJA       = 29,
    TSPR_HPELOTA_AMARILLA   = 30,
    TSPR_HPELOTA_VERDE      = 40,
    TSPR_HPELOTA_AZUL       = 50,

    TSPR_HTORNILLO_AZUL     = 51,
    TSPR_HTORNILLO_AMARILLO = 52,

    TSPR_HPALO_AZUL         = 53,
    TSPR_HPALO_AMARILLO     = 54,
    TSPR_HPALO_VERDE        = 55,

    TSPR_HSPIDER_VERDE      = 56,
    TSPR_HSPIDER_ROJO       = 57,
    TSPR_HSPIDER_AZUL       = 58,

    TSPR_HARO_AMARILLO      = 59,
    TSPR_HARO_ROJO          = 60,
    TSPR_HARO_MORADO        = 61,

    TSPR_HBOLAPINCHO_ROJA   = 62,
    TSPR_HBOLAPINCHO_AZUL   = 63,

    TSPR_HTABLA_ROJA        = 64,
    TSPR_HTABLA_MARRON      = 65,
    TSPR_HTABLA_MORADA      = 66,

    TSPR_VBABOSA_AMARILLA   = 67,
    TSPR_VBABOSA_VERDE      = 68,
    TSPR_VBABOSA_ROJA       = 69,

    TSPR_PEZ_AMARILLO       = 70,
    TSPR_PEZ_AZUL           = 71,
    TSPR_PEZ_VERDE          = 72,

    TSPR_VPELOTA_ROJA       = 73,
    TSPR_VPELOTA_AMARILLA   = 74,
    TSPR_VPELOTA_VERDE      = 75,
    TSPR_VPELOTA_AZUL       = 76,

    TSPR_VARO_AMARILLO      = 77,
    TSPR_VARO_ROJO          = 78,
    TSPR_VARO_MORADO        = 79,

    TSPR_ROCA_BLANCA        = 80,
    TSPR_ROCA_MARRON        = 81,

    TSPR_HORMIGUERO         = 82,
    TSPR_FLECHA             = 83,
    TSPR_PELOTABOTA         = 84,

    TSPR_VBOLAPINCHO_ROJA   = 85

} TTipoSprite;

// **************************
//  CLASE BASE PARA ENEMIGOS
// **************************

class TSpriteEnemigo:public TMASprite
{
REGISTER_CLASS protected:

public:
    PUBLIC_CLASS_ID;
    TSpriteEnemigo(PMAImageBank b);
    virtual void getCollisionRectangle(TMARectangle&);
};


// --------------- PROTAGONISTA

#define ANIM_ANDANDO  1
#define ANIM_PARADO   2
#define ANIM_SALTANDO 3
#define ANIM_MURIENDO 4

class TProfanationGame;
class TSpriteEnemigo;

class TSprJohny:public TMASprite
{
    REGISTER_CLASS protected:

    // Guardar Estado.
    //
	TMARectangle est_MemPos;
	TProfanationGame *miGame;
    bool est_izquierda,est_derecha,est_saltando,est_flip;
    int est_longitud_salto,est_tiempo_salto;
    int est_longitud_animacion,est_retardo_animacion;
    const int *est_animacion;
    int ii_tilesx,ii_tilesy;

	bool ib_andando_izquierda,ib_andando_derecha;
	bool ib_saltando;           // Indica que el personaje esta saltando.
    int  il_longitud_salto;     // Inicialmente tiene la máxima altura del salto.
    int  il_tiempo_salto;       // Indica cuanto tiempo debe estar subiendo el personaje.

    bool ib_suelo_mortal;       // Indica si el suelo que se pisa, mata.

	static int ia_AnimAndando[48];
    static int ia_AnimParado[12];
    static int ia_AnimSaltando[12];
	
	void pf_ControlMovimiento(void);
    void pf_DoJump(void);
    void pf_EstablecerAnimacion(int tipo);

    // Comprueba si puede caminar a derecha/izquierda
	//
	bool pf_CanMove(bool derecha);
	void pf_MoveLeft(void);
	void pf_MoveRight(void);

	bool pf_CanJump(void);
	void pf_MoveUp(void);

	bool pf_CanFallDown(void);
	void pf_MoveDown(void);
    
    PMAGameMap map;
    
public:
     PUBLIC_CLASS_ID;

     PMAScreenMap screen;
	 TSprJohny();
          
     void init(TMAGameMap&,int pbank);
	 void animate(bool control);
	 bool draw(TMABitmap&);

     bool isCollisioningWith(TSpriteEnemigo&);
     void Morir(void);
	 void Disparar(void);
     void GuardarPosicion(void);
     void RestaurarPosicion(void);
     void Matar(bool m);

     // Posicionar en una coordenada.
     //
     void putAt(int px,int py);

     // Rutinas de Paso de Pantalla
     //
     void enterLeft(void);
     void enterUp(void);
     void enterRight(void);
     void enterDown(void);

     bool isEnterLeft(void);
     bool isEnterRight(void);
     bool isEnterUp(void);
     bool isEnterDown(void);

     bool estaMuriendo(void) { return ii_Estado>0; }
     void detenerSalto(void);
     bool SueloMortal(void) { return ib_suelo_mortal; }

	 short ii_vidas;
};

// **************************
//        SCROLL TESORO
// **************************

class TSprTesoro:public TMASprite
{
REGISTER_CLASS protected:

    int velocidad;
    int ii_posy;
    int ii_pantalla;
    PMABitmap bmp;

public:
     PUBLIC_CLASS_ID;
	 TSprTesoro();
     void init(TMAGameMap&,int banco,int grafico,int posx,int posy,int vel,int p_pantalla=0);
	 bool draw(TMABitmap&);
	 void animate(void);
     int  getPantalla(void) { return ii_pantalla; }
     void setPantalla(int p) { ii_pantalla=p; }
};


// ------------------ ENEMIGOS DEL JUEGO

// **************************
//          LA GOTA
// **************************

class TSprGota:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    static int AnimRojo[7];
    static int AnimAmarillo[7];
    static int AnimVerde[7];
    static int AnimAzul[7];

    int init_y;
    int end_y;
    int velocidad;
    int pausa_rotura;
    int pausa_caida;
    TProfanationGame *miGame;

public: 
    PUBLIC_CLASS_ID;
    TSprGota(PMAImageBank,int tipo,int posx,int posy,int pinity,int pendy,int vel,int pausa_rota);
    void animate(void);
    bool draw(TMABitmap&);
    void getCollisionRectangle(TMARectangle&);
};

// **************************
//          LA FLECHA
// **************************

class TSprFlecha:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    static int Anim[4];
    
    int init_x;
    int end_x;
    int velocidad;

public:
    PUBLIC_CLASS_ID;
	TSprFlecha(PMAImageBank,int posx,int posy,int pinitx,int pendx,int vel,int retardo);
    void animate(void);
};

// **************************
//     LA PELOTA QUE BOTA
// **************************

class TSprPelotaBota:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    static int Anim[4];
    
    int init_x,init_y;
    int end_x,end_y;
    int vx,vy;

public:
    PUBLIC_CLASS_ID;
	TSprPelotaBota(PMAImageBank,int pinitx,int pinity,int pendx,int pendy,int vel,int retardo);
    bool draw(TMABitmap&);
    void animate(void);
};

// **************************
//      LA ROCA QUE CAE
// **************************

class TSprRoca:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    static int AnimBlanca[6];
    static int AnimMarron[6];
    
    int init_y;
    int end_y;
    int velocidad;
    int pausa_rotura;
    TProfanationGame* miGame;

public:
    PUBLIC_CLASS_ID;
	TSprRoca(PMAImageBank,int tipo,int posx,int posy,int pinity,int pendy,int vel,int pausa_rota);
    void animate(void);
};

// *******************************
//   ENEMIGO HORIZONTAL CON FLIP
// *******************************

class TSprHorizontalConFlip:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    
    // Serpientes
    //
    static int AnimSerpienteRosa[6];
    static int AnimSerpienteAmarilla[6];
    static int AnimSerpienteVerde[6];
    static int AnimSerpienteAzul[6];

    // Babosa
    //
    static int AnimBabosaAmarilla[8];
    static int AnimBabosaVerde[8];
    static int AnimBabosaRoja[8];

    // Momia
    //
    static int AnimMomiaAzul[6];
    static int AnimMomiaVerde[6];
    static int AnimMomiaRoja[6];

    int init_x;
    int end_x;
    int velocidad;

public:
    PUBLIC_CLASS_ID;
	TSprHorizontalConFlip(PMAImageBank,int tipo,int posx,int posy,int pxmin,int pxmax,int vel,int retardo);
    bool draw(TMABitmap&);
    void animate(void);
};

// *******************************
//   ENEMIGO VERTICAL SIN FLIP
// *******************************

class TSprVertical:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    
    // Rayos
    //
    static int AnimRayoMorado[3];
    static int AnimRayoAmarillo[3];
    static int AnimRayoVerde[3];
    static int AnimRayoAzul[3];

    // Tablas
    //
    static int AnimTablaRoja[8];
    static int AnimTablaMarron[8];
    static int AnimTablaMorada[8];

    // Arañas
    //
    static int AnimSpiderAzul[8];
    static int AnimSpiderVerde[8];
    static int AnimSpiderRoja[8];

    // Tornillos
    //
    static int AnimTornilloAzul[8];
    static int AnimTornilloAmarillo[8];

    // Pelota
    //
    static int AnimPelotaRoja[4];
    static int AnimPelotaAmarilla[4];
    static int AnimPelotaVerde[4];
    static int AnimPelotaAzul[4];

    // Aro
    //
    static int AnimAroAmarillo[6];
    static int AnimAroRojo[6];
    static int AnimAroMorado[6];

    // Bolas de Pinchos
    //
    static int AnimBolaPinchoRoja[10];

    int init_y;
    int end_y;
    int velocidad;
    bool bajando;
    int it_tipo;
    int pausa_movimiento,mpausa;

public:
    PUBLIC_CLASS_ID;
	TSprVertical(PMAImageBank,int tipo,int posx,int posy,int pymin,int pymax,int vel,int retardo);
    bool draw(TMABitmap&);
	void animate(void);
    void getCollisionRectangle(TMARectangle&);
};

// *******************************
//   ENEMIGO VERTICAL CON FLIP
// *******************************

class TSprVerticalFlip:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    
    // Babosa
    //
    static int AnimBabosaAmarilla[8];
    static int AnimBabosaVerde[8];
    static int AnimBabosaRoja[8];

    // Peces
    //
    static int AnimPezAmarilloS[4];
    static int AnimPezAmarilloB[4];
    static int AnimPezAzulS[4];
    static int AnimPezAzulB[4];
    static int AnimPezVerdeS[4];
    static int AnimPezVerdeB[4];

    const int *anim;
    int init_y;
    int end_y;
    int velocidad;
    int bajando;

public:
    PUBLIC_CLASS_ID;
    TSprVerticalFlip(PMAImageBank,int tipo,int posx,int posy,int pymin,int pymax,int vel,int retardo);
    bool draw(TMABitmap&);
	void animate(void);
};

// *******************************
//   ENEMIGO HORIZONTAL SIN FLIP
// *******************************

class TSprHorizontal:public TSpriteEnemigo
{
REGISTER_CLASS protected:
    
    // Pelota
    //
    static int AnimPelotaRoja[4];
    static int AnimPelotaAmarilla[4];
    static int AnimPelotaVerde[4];
    static int AnimPelotaAzul[4];

    // Tornillos
    //
    static int AnimTornilloAzul[8];
    static int AnimTornilloAmarillo[8];

    // Palos
    //
    static int AnimPaloAzul[8];
    static int AnimPaloAmarillo[8];
    static int AnimPaloVerde[8];
 
    // Arañas
    //
    static int AnimSpiderAzul[8];
    static int AnimSpiderVerde[8];
    static int AnimSpiderRoja[8];

    // Aro
    //
    static int AnimAroAmarillo[6];
    static int AnimAroRojo[6];
    static int AnimAroMorado[6];

    // Tablas
    //
    static int AnimTablaRoja[8];
    static int AnimTablaMarron[8];
    static int AnimTablaMorada[8];

    // Bolas de Pinchos
    //
    static int AnimBolaPinchoRoja[10];
    static int AnimBolaPinchoAzul[10];

    // Hormiguero
    //
    static int AnimHormiguero[6];

    int init_x;
    int end_x;
    int velocidad;
    bool derecha;
    int it_tipo;
    int pausa_movimiento,mpausa;

public:
    PUBLIC_CLASS_ID;
	TSprHorizontal(PMAImageBank,int tipo,int posx,int posy,int pxmin,int pxmax,int vel,int retardo);
    bool draw(TMABitmap&);
    void animate(void);
};

#endif

