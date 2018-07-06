#ifndef _TMAVECTOR_CPP_
#define _TMAVECTOR_CPP_

#include "utils.h"
#include "string.h"

REGISTER_CLASS_ID(TMAItemComparator);
REGISTER_CLASS_ID(TMAVectorBase);

// *******************
// Clase TMAVectorBase
// *******************
//
TMAVectorBase::TMAVectorBase(int elems,int grow,bool delete_items)
{
    il_initsize = elems;
    il_vsize = elems;
    ii_ngrow = grow;
    CItems = NULL;
    ib_delete_items=delete_items;
    clear();
}

TMAVectorBase::~TMAVectorBase()
{
    if (CItems!=NULL)
    {
        clear();
        delete CItems;
        CItems=NULL;
    }
}

void TMAVectorBase::delete_objects(void)
{
    // Si el vector no requiere que se eliminen los items... salimos
    //
    if (!ib_delete_items || CItems==NULL) return;
    
    // Eliminamos cada item
    //
    for(int i =  0; i < il_count; i++ )
    {
        if (CItems[i]!=NULL)
        {
            delete (CItems[i]);
            CItems[i]=NULL;
        }
    }
}

void TMAVectorBase::swaps_element(long index1,long index2)
{
    PMAObject T;
    if (index1>=0 && index2>=0 && index1<il_count && index2<il_count && index1!=index2)
    {
        T=CItems[index1];
        CItems[index1]=CItems[index2];
        CItems[index2]=T;
    }        
}

void TMAVectorBase::clear(void)
{
    delete_objects();
    if (CItems) delete CItems;
    CItems = new PMAObject[il_initsize];
    for (int i=0;i<il_initsize;i++) CItems[i]=NULL;
    il_vsize=il_initsize;
    il_count=0;
}

void TMAVectorBase::grow_buffer(bool grow)
{
    long i;
    PMAObject *aItems;
    
    if (grow) il_vsize += ii_ngrow;
    aItems = new PMAObject[il_vsize];
    for(i=0;i<il_vsize;i++) aItems[i]=NULL;
    
    if( il_count !=  0 )
    {
        memcpy( &aItems[0], &CItems[0], il_count*sizeof(PMAObject) );
    }
    delete CItems;
    CItems = aItems;
}

void TMAVectorBase::redim(long initsize)
{
    il_initsize = initsize;
    pack();
}

void TMAVectorBase::pack(void)
{
    il_vsize = (il_count / ii_ngrow);
    if ((il_count % ii_ngrow)>0) il_vsize++;
    il_vsize*=ii_ngrow;
    if (il_vsize<il_initsize) il_vsize=il_initsize;
    grow_buffer(false);
}

void TMAVectorBase::fillEmpty(long numelems)
{
    while (numelems>0)
    {
        add_element(NULL,il_count);
        numelems--;
    }
}

bool TMAVectorBase::findElement(PMAObject obj,long& index)
{
    for (int i=0;i<il_count;i++)
    {
        if (CItems[i]==obj) 
        {
            index=i;
            return true;
        }
    }
    return false;
}

bool TMAVectorBase::exists(PMAObject obj)
{
    long index;
    return findElement(obj,index);
}

bool TMAVectorBase::removeElement(PMAObject obj,bool delobject)
{
    long index;
    if (findElement(obj,index))
    {
        return removeElementAt(index,delobject);
    }
    return false;
}

bool TMAVectorBase::removeElementAt(long index,bool delobject)
{
    if( index < 0 || index >= il_count ) return false;

    PMAObject obj = CItems[index];    
    memmove( &CItems[index], &CItems[index+1], (il_count-index-1)*sizeof(PMAObject) );
    CItems[--il_count]=NULL;
    
    if (ib_delete_items && delobject) delete obj;
    return true;
}

long TMAVectorBase::add_element(PMAObject item,long index)
{
    if ( index < 0 ) return -1; // Error.
    if ( il_count == il_vsize ) grow_buffer();

    memmove( &CItems[index+1], &CItems[index], (il_count-index)*sizeof(PMAObject) );
    il_count++;

    CItems[index] = item;
    return index;
}

PMAObject TMAVectorBase::elementAt(long index)
{
    if( index < 0 || index >= il_count ) return NULL;
    return CItems[index];
}

// ***************
// Clase TMAVector
// ***************
//
REGISTER_CLASS_ID(TMAVector);

long TMAVector::addElement(PMAObject obj)
{
    return add_element(obj,size());
}

long TMAVector::addElementAt(PMAObject obj,long index)
{
    return add_element(obj,index);
}

bool TMAVector::replaceElementAt(PMAObject obj,long index)
{
    if (index>=0 && index<il_count)
    {
        if (ib_delete_items && CItems[index]!=NULL) delete CItems[index];
        CItems[index]=obj;
        return true;
    }
    return false;
}

// **********************
// Clase TMAVectorOrdered
// **********************
//
REGISTER_CLASS_ID(TMAVectorOrdered);

TMAVectorOrdered::~TMAVectorOrdered()
{
    if (io_comp!=NULL) delete io_comp;
}        

TMAVectorOrdered::TMAVectorOrdered(PMAItemComparator icomp,int elems,int grow,bool delete_items):
    TMAVectorBase(elems,grow,delete_items)
{
    io_comp=NULL;
    setComparator(icomp);
}

void TMAVectorOrdered::setComparator(PMAItemComparator icomp)
{
    if (io_comp) delete io_comp;
    io_comp = icomp;
}

long TMAVectorOrdered::addElement(PMAObject obj)
{
    // Si no hay elementos, insertamos directamente.
    //
    if (size()==0) return add_element(obj,0);
    
    // En otro caso ordenamos.
    //
    long index_izq=0,index_der=il_count-1,index=0;
    
    while (index_izq<=index_der)
    {
        index = (index_izq + index_der)/2;
        PMAObject obj1 = CItems[index];
        switch (io_comp->compare(*obj,*obj1))
        {
            case -1: // obj<obj1
                index_der=index-1;
                break;
                
            case 0: // obj=obj1
                index_izq=index+1;
                break;
                
            case 1: // obj>obj1
                index_izq=index+1;
                break;
        }        
    }        
    if (index>il_count) index=il_count;
    if (index<0) index=0;
    
    return add_element(obj,index);
}

#endif
