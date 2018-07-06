#ifndef _TMAIMAGEBANK_CPP_
#define _TMAIMAGEBANK_CPP_

#include "ma_classes.h"
#include "utils/utils.h"

REGISTER_CLASS_ID(TMAImageBank);

TMAImageBank::TMAImageBank()
{
    imgsource=NULL;
}

TMAImageBank::~TMAImageBank()
{
    vector.clear();
    if (imgsource!=NULL) delete imgsource;
}

TMAImageBank *TMAImageBank::createStatic(const char *filename,int tx,int ty,int ax,int ay,bool separator)
{
    TMABitmap *bmp = TMABitmap::loadFromFile(filename,true);
    if (bmp==NULL) return NULL;
    
    TMAImageBank *ibank = createStatic(*bmp,tx,ty,ax,ay,separator);
    
    return ibank;
}

TMAImageBank *TMAImageBank::createStatic(TMABitmap& bmp,int tx,int ty,int ax,int ay,bool separator)
{
    int size = tx*ty,index=0;
    TMAImageBank *ibank = new TMAImageBank();
    
    if (ibank==NULL) return NULL;
    ibank->vector.redim(size);
    ibank->vector.fillEmpty(size);
    ibank->imgsource=&bmp;
    
    for (int y=0;y<ty;y++)
    {
        for (int x=0;x<tx;x++)
        {
            PMABitmap img = (!separator)?(TMABitmap::create(&bmp,x*ax,y*ay,ax,ay)):(TMABitmap::create(&bmp,x*(ax+1),y*(ay+1),ax,ay));
            if (img==NULL)
            {
                delete ibank;
                return NULL;
            }
            ibank->vector.replaceElementAt(img,index++);
        }
    }
    return ibank;
}
            
TMAImageBank *TMAImageBank::createDynamic(const char *filename,TMAVector& zonas)
{
    TMABitmap *bmp = TMABitmap::loadFromFile(filename,true);
    if (bmp==NULL) return NULL;
    
    TMAImageBank *ibank = createDynamic((*bmp),zonas);
    
    return ibank;
}    

TMAImageBank *TMAImageBank::createDynamic(TMABitmap& bmp,TMAVector& zonas)
{
    TMAImageBank *ibank = new TMAImageBank();
    if (ibank==NULL) return NULL;
    
    ibank->vector.redim(zonas.size());
    ibank->vector.fillEmpty(zonas.size());
    ibank->imgsource=&bmp;
    
    for (int index=0;index<zonas.size();index++)
    {
        PMAObject obj = zonas.elementAt(index);
        if (obj!=NULL && obj->isInstanceOf(CLASS_ID(TMARectangle)))
        {
            PMARectangle rect = (PMARectangle)obj;   
            PMABitmap img = TMABitmap::create(&bmp,rect->x,rect->y,rect->width,rect->height);
            if (img==NULL)
            {
                delete ibank;
                return NULL;
            }
            ibank->vector.replaceElementAt(img,index);
        }
    }
    
    return ibank;    
}
    
// Devuelve una imagen del banco de imágenes, que esta indexada
// por el indice especificado.
//
const PMABitmap TMAImageBank::getBitmap(int index)
{
    return (PMABitmap)vector.elementAt(index);
}

long TMAImageBank::size(void) 
{ 
    return vector.size(); 
}

/*
PMAImageBank TMAImageBank::clone(void)
{
    PMAImageBank lbank = new TMAImageBank();
    
    for (int i=0;i<size();i++)
    {
        PMABitmap bmp = getBitmap(i);
        lbank->vector.addElement((bmp!=NULL)?bmp->clone():NULL);
    }
    return lbank;
}
*/

#endif
