#ifndef _MAPAS_H_
#define _MAPAS_H_

#include "../ma_classes.h"
#include "../utils/utils.h"

// **********
// Prototipos
// **********

class TMAScreenIndex;
class TMAGraphBank;
class TMAGraphOperation;
class TMAGraphAnimation;
class TMAScreenMap;
class TMAGameMap;

typedef TMAScreenIndex* PMAScreenIndex;
typedef TMAGraphBank* PMAGraphBank;
typedef TMAGraphOperation* PMAGraphOperation;
typedef TMAGraphAnimation* PMAGraphAnimation;
typedef TMAScreenMap* PMAScreenMap;
typedef TMAGameMap* PMAGameMap;

// **************************************************************************
// Clase: TMAScreenIndex
//        Implementa un indice para acceder fisicamente a la pantalla dentro 
//        del archivo de mapa.
// **************************************************************************
//
class TMAScreenIndex : public TMAObject
{
    REGISTER_CLASS protected:
        
        friend class TMAGameMap;
        
        TMAScreenIndex(){};
         
    public:
        PUBLIC_CLASS_ID;
        TMAString name;
        int id;
        long offset;	   
};

// **************************************************************************
// Clase: TMAGraphBank
//        Implementa un objeto banco de imagen dentro de la jerarquia de la
//        estructura de mapa de juego
// **************************************************************************
//
class TMAGraphBank : public TMAFileReader
{
    REGISTER_CLASS protected:
    
        friend class TMAGameMap;
    
        TMAString Name;
        const char *is_basedir;
        int BankID;
        int Tipo,TileAX,TileAY;
        int TransColor;
        int Transparente;
        PMAImageBank io_bank;
            
    public:
        PUBLIC_CLASS_ID;
        
        enum TransMode { T_NONE=0,T_TRANSPARENT,T_ALPHA };
        
        static const int SIZE_STATIC = 0;
        static const int SIZE_DYNAMIC = 1;
        
        TMAGraphBank();
        ~TMAGraphBank();

        bool readFromFile(FILE*);
        const PMAImageBank getImageBank(void) { return io_bank; }
        const PMABitmap getImage(int index);
        long size() { return (io_bank==NULL)?0:io_bank->size(); }
        
        void setTransparentMode(TransMode tm) { Transparente = tm; }
        bool isTransparent() { return (Transparente == T_TRANSPARENT); }
        bool isAlpha() { return (Transparente == T_ALPHA); }
};

// **************************************************************************
// Clase: TMAGraphOperation
//        Implementa la superclase operaciones graficas que contiene el mapa
// **************************************************************************
//
class TMAGraphOperation : public TMAFileReader
{
    REGISTER_CLASS protected:
        
        friend class TMAGraphAnimation;
        friend class TMAScreenMap;
        friend class TMAGameMap;
        
        int BankID,TileID;
        int PosX,PosY;
        int RepeatX,RepeatY;
        int StepX,StepY;
        bool AlignGrid;
        int Tipo; // 0->Normal, 1-> Por delante, etc...
        int InitFrame,EndFrame,PauseFrame,PauseAnim;
        bool PingPong;
	    TMAGraphOperation(){};
        
    public:
        PUBLIC_CLASS_ID;
        
        static const int OP_NORMAL = 0;
        static const int OP_FRONT = 1;
        static const int OP_ANIM_FRONT = 2;
        static const int OP_ANIM_NORMAL = 3;

    	int getBankID() { return BankID; }
    	int getTileID() { return TileID; }
    	int getPosX()   { return PosX; }
    	int getPosY()   { return PosY; }
    	int getType()   { return Tipo; }

        bool isGridAligned() { return AlignGrid; }
    	
    	void setBankID(int id) { BankID = id; }
        void setTileID(int id) { TileID = id; }
        void setPosition(int px,int py) { PosX = px; PosY = py; }
        void setPosX(int px) { PosX = px; }
        void setPosY(int py) { PosY = py; }
        void setType(int t) { Tipo = t; }

    	bool readFromFile(FILE*);
};

// **************************************************************************
// Clase: TMAGraphAnimation
//        Extiende la superclase operaciones graficas para animaciones
// **************************************************************************
//
class TMAGraphAnimation : public TMAGraphOperation 
{
    REGISTER_CLASS protected:

        friend class TMAScreenMap;
        friend class TMAGameMap;
    
    	int a_CurFrame;
    	int a_PauseFrame;
    	int a_PauseAnim;
    	bool a_Down;
    	TMAGraphAnimation(TMAGraphOperation& go);

    public:
        PUBLIC_CLASS_ID;

};    

// ***************************************************************************
// Clase: TMAScreenMap
//        Define la clase que encapsula la definición de una pantalla del mapa
// ***************************************************************************
//
class TMAScreenMap : public TMAFileReader
{
    REGISTER_CLASS protected:

        friend class TMAGameMap;
 
        unsigned char *MaskBuff;

        int _GetMask_lbits;  
        int _GetMask_width;  
        int _GetMask_height; 
        int _GetMask_mask;   
        	
        int ScreenID,MaskCol,MaskRow;
        
        TMAVector iv_OpNormal;      // Operaciones Graficas de fondo.
        TMAVector iv_OpFront;       // Operaciones Graficas de por delante.	
        TMAVector iv_OpAnimNormal;  // Animaciones que deben dibujarse de fondo.
        TMAVector iv_OpAnimFront;   // Animaciones que deben dibujarse por delante.
        	
        TMAScreenMap(int id);
    
    public:
        PUBLIC_CLASS_ID;
        ~TMAScreenMap();
        
        int getID() { return ScreenID; }
        TMAVector& getGraphicsOperationsForType(int);
        void deleteGraphOperation(int tipo,int bankid,int tileid);
        unsigned char getMask(int X,int Y);        
        bool readFromFile(FILE*);
};    

// ***************************************************************************
// Clase: TMAGameMap
//        Define la clase que encapsula la definición de un mapa
// ***************************************************************************
//
class TMAGameMap : public TMAFileReader
{
    REGISTER_CLASS 
        
        bool ib_iniciado;
        TMAString is_FileName;
        TMAString is_BaseDir;
        
    protected:

        void clear();
 	
        int ScreenX,ScreenY;
        int TilesAX,TilesAY;
        int BitMask;        
        int ColorFondo;
        
        TMAVector iv_Bancos;
        TMAVector iv_Screen;
        PMABitmap io_FastBuffer;
        
        int nBits(int valores);
        int nBitsMask(int bits);
        void drawGraphOperation(TMABitmap&,TMAGraphOperation&);	
  
    public:
        PUBLIC_CLASS_ID;
        TMAGameMap();
        ~TMAGameMap();
        
        int getGridAX() { return TilesAX; }
        int getGridAY() { return TilesAY; }
        int getScreenX() { return ScreenX; }
        int getScreenY() { return ScreenY; }
        int getBackgroundColor() { return ColorFondo; }
        
        bool setMapFile(const char *,const TMAString& basedir);
        PMAScreenMap getScreen(int id);
        const PMAGraphBank getGraphBank(int index);
        const PMAImageBank getImageBank(int index);
        bool createBufferForFastDrawing(int width,int height);
        void drawScreenGraphOperations(TMABitmap&,const PMAScreenMap,int tipo);
        void animateGraphOperations(const PMAScreenMap,int tipo);
        void drawFastBuffer(const PMAScreenMap,int ColorBack);
        void drawScreen(TMABitmap&,const PMAScreenMap,bool use_fast_buffer=false);
        const PMABitmap getFastScreenBuffer(void) {return io_FastBuffer;}
        
        bool readFromFile(FILE*);
};

#endif
