#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../ma_object.h"

class TMAVectorBase;
class TMAVector;
class TMAVectorOrdered;
class TMAItemComparator;
class TMAString;
class TMAFileReader;
class TMARectangle;
class TMARandom;
class TMAMsg;
class TMAMsgQueue;

typedef TMAVectorBase* PMAVectorBase;
typedef TMAVector* PMAVector;
typedef TMAVectorOrdered* PMAVectorOrdered;
typedef TMAItemComparator* PMAItemComparator;
typedef TMAString* PMAString;
typedef TMAFileReader* PMAFileReader;
typedef TMARectangle* PMARectangle;
typedef TMARandom* PMARandom;
typedef TMAMsg* PMAMsg;
typedef TMAMsgQueue *PMAMsgQueue;

// **************************************************
// Clase que implementa un vector dinamico de objetos
// **************************************************
//
class TMAVectorBase : public TMAObject
{
    REGISTER_CLASS protected:
                
        PMAObject *CItems;
        int ii_ngrow;
        long il_initsize,il_vsize,il_count;
        bool ib_delete_items;
        
        void grow_buffer(bool grow=true);
        void delete_objects();
        void swaps_element(long index1,long index2);
        bool findElement(PMAObject,long&);
        long add_element(PMAObject,long index);   
        
    public:
        PUBLIC_CLASS_ID;
        
        // Crea un vector con una determinada capacidad inicial
        // y con un factor de crecimimento.
        //
        TMAVectorBase(int elems=10,int grow=10,bool delete_items=true);
        virtual ~TMAVectorBase();
        
        // Métodos de manejo de elementos del vector
        //
        void redim(long initsize);
        void fillEmpty(long numelems);
        PMAObject elementAt(long index);
        bool removeElement(PMAObject,bool delobject=true);
        bool removeElementAt(long index,bool delobject=true);
        void clear(void);
        void pack(void);
        long size(void) { return il_count; }
        bool exists(PMAObject);
};

// ******************************
// Clase que implementa un vector 
// ******************************
//
class TMAVector : public TMAVectorBase
{
    REGISTER_CLASS protected:
                
    public:
        PUBLIC_CLASS_ID;
        
        TMAVector(int elems=10,int grow=10,bool delete_items=true):
            TMAVectorBase(elems,grow,delete_items){};
                
        // Métodos de manejo de elementos del vector
        //
        long addElement(PMAObject);
        long addElementAt(PMAObject,long index);
        bool replaceElementAt(PMAObject,long index);
};

// ***************************************
// Clase que implementa un vector ordenado
// ***************************************
//
class TMAVectorOrdered : public TMAVectorBase
{
    REGISTER_CLASS protected:

        PMAItemComparator io_comp;
                
    public:
        PUBLIC_CLASS_ID;
                
        TMAVectorOrdered(PMAItemComparator icomp=NULL,int elems=10,int grow=10,bool delete_items=true);
        ~TMAVectorOrdered();
        
        // Establece el objeto comparador
        //
        void setComparator(PMAItemComparator);
        
        // Inserta un elemento en el vector de forma ordenada
        //
        long addElement(PMAObject);
};

// **************************************************************
// Clase que implementa un interfaz para comparación de elementos
// **************************************************************
//
class TMAItemComparator : public TMAObject
{
    REGISTER_CLASS protected:
                
    public:
        PUBLIC_CLASS_ID;
                 
        // Comparación de dos objetos.
        // Retorna:
        //      -1 -> o1<o2
        //       0 -> o1=o2
        //       1 -> o1>o2
        //
        virtual int compare(TMAObject& o1,TMAObject& o2)=0;
};

// *****************************
// Clase que encapsula un String
// *****************************
//
class TMAString:public TMAObject
{
    REGISTER_CLASS protected:

        char *Dato;
        int size;
        void clear(void); // Borra el contenido.

    public:
        PUBLIC_CLASS_ID;
        
        ~TMAString ();
        TMAString ();
        TMAString (const TMAString&); // Constructor de Copia por referencia.
        TMAString (const char *);
        
        const int length(void) {return size;};
        const int findStr(TMAString& Sub);
        TMAString numToStr(long num,int ndig);
        const long intValue(void);
        TMAString toUpperCase(void);
        TMAString toLowerCase(void);
        
        TMAString mid(int Index,int numchar);
        TMAString trim(void);
        
        void replaceChar(char origen,char destino);
                
        const char* text(void)  {return Dato;};
        const char* operator *(void) {return Dato;};
        char operator [](int P) {return Dato[P];};
        
        TMAString operator + (const char *);
        TMAString operator + (const TMAString&);
        
        TMAString& operator = (char *);
        TMAString& operator = (TMAString&);
        TMAString& operator = (TMAString);        
        
        int compare(const TMAString&);
};


// **********************************************
// Interfaz para clases que trabajan con ficheros
// **********************************************
//
class TMAFileReader : public TMAObject
{
    REGISTER_CLASS protected:
        
    public:
        PUBLIC_CLASS_ID;
    
        long getCurrentOffset(FILE*);
        bool seekTo(FILE*,long);
        long getBytes(FILE *,void *,long size);
        unsigned char getByte(FILE*);
        unsigned int  get2BWord(FILE*);
        int  get2BWordSigned(FILE*);
        unsigned long get4BWord(FILE*);
        TMAString getString(FILE*,int size);        
    
        virtual bool readFromFile(FILE*)=0;
};

// ******************
// Clase TMARectangle
// ******************
//
class TMARectangle : public TMAObject
{
    REGISTER_CLASS protected:
        
    public:
        PUBLIC_CLASS_ID;
        int x,y;
        int width,height;
        
        TMARectangle();
        TMARectangle(int px,int py,int w,int h);
        TMARectangle(const TMARectangle& r);
        TMARectangle(int w, int h);
        TMARectangle& operator = (TMARectangle& r);
        TMARectangle& operator = (TMARectangle);
        
        void setBounds(TMARectangle& r);
        void setBounds(int px, int py, int pw, int ph);
        void setLocation(int px, int py);
        void translate(int px, int py);
        void setSize(int pw,int ph);
        bool contains(int px, int py);
        bool intersects(TMARectangle& r);
        TMARectangle intersection(TMARectangle& r);
        TMARectangle unionRect(TMARectangle& r);
        bool isEmpty();        
};

// ***************
// Clase TMARandom
// ***************
//
class TMARandom : public TMAObject
{
    REGISTER_CLASS protected:
        
    public:
        PUBLIC_CLASS_ID;
        
        static void init(unsigned long seed=0);
        static unsigned long nextInt(void);
        static unsigned long nextInt(unsigned long);
};

// ************
// Clase TMAMsg
// ************
//
class TMAMsg : public TMAObject
{
    REGISTER_CLASS protected:

        friend class TMAMsgQueue;

        int msgid;
        void *source;
        void *param;
        
        TMAMsg();
        TMAMsg(int id,void *psource=NULL,void *pparam=NULL);

    public:
        PUBLIC_CLASS_ID;
        
        int getID() { return msgid; }
        void *getSource() { return source; }
        void *getParam() { return param; }
};

// *****************
// Clase TMAMsgQueue
// *****************
//
class TMAMsgQueue : public TMAObject
{
    REGISTER_CLASS protected:

        TMAVector msgqueue;
        static TMAMsg NULL_MSG;
        
    public:
        PUBLIC_CLASS_ID;
        
        void putMessage(int id,void *source=NULL,void *param=NULL);

        bool hasMessage(void);
        TMAMsg& getMessage(void);
        void dispatchMessage(void);
        int getMessageCount(void);
        void clearQueue(void);
};

#endif
