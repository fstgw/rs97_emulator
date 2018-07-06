#ifndef _TMASTRING_CPP_
#define _TMASTRING_CPP_

#include "utils.h"
#include <string.h>
#include <ctype.h>

REGISTER_CLASS_ID(TMAString);

TMAString::TMAString()
{
    Dato=NULL;
    size=0;
}


TMAString::TMAString(const TMAString& str)
{
    Dato=NULL;
    size=0;
    if (str.size<=0) return;

    size=str.size;
    Dato=new char[size+1];
    memcpy(Dato,str.Dato,size+1);
}

TMAString::TMAString(const char *T)
{
    Dato=NULL;    
    size=strlen(T);
    if (size<=0) return;
    Dato=new char[size+1];
    memcpy(Dato,T,size+1);
};


TMAString::~TMAString()
{
    clear();
}

void TMAString::replaceChar(char origen,char destino)
{
    for (int i=0;i<size;i++)
    {
        if (Dato[i]==origen) Dato[i]=destino;
    }
}    

void TMAString::clear(void)
{
    if (Dato!=NULL)
    {
        delete Dato;
        Dato=NULL;
    }
    size=0;
}

const int TMAString::findStr(TMAString& Sub)
{
    int L1=size;
    int L2=Sub.length();
    int result=0,i,j;
    char *SS1=Dato,*S1;
    const char *S2;
    int Igual=1;
    
    if (L1>=L2)
    {
        for (i=0;((i<=(L1-L2))&(result==0));i++)
        {
            S1=SS1++; S2=*Sub; Igual=1;
            for (j=0;j<L2;j++)
            {
                if (*S1++!=*S2++) Igual=0;
            }
            if (Igual==1) result=i+1;
        }
    }

    return result;
}

TMAString TMAString::mid(int index,int numchar)
{
    TMAString aux;
    if (index<0 || index>size || numchar<=0)
    {
        return aux;
    }
    
    char *S1=new char[numchar+1];
    S1[numchar]=0;
    memcpy(S1,&Dato[index],numchar);
    aux=S1;
    delete S1;
    return aux;
}

TMAString TMAString::trim(void)
{
    int begin,end;
    begin = 0;
    end = size-1;
    while (Dato[begin]==' ' && begin<end) begin++;
    while (Dato[end]==' ' && end>begin) end--;
    return mid(begin,(end-begin+1));
}

TMAString TMAString::numToStr(long num,int ndig)
{
    int dec, sign;
    return TMAString("0.0");//fcvt(num, ndig, &dec, &sign));
}

const long TMAString::intValue(void)
{
    return atol(Dato);
}

TMAString TMAString::toUpperCase(void)
{
    TMAString aux(Dato);
    char *S=aux.Dato;
    while (*S!=0)
    {
        *S=toupper(*S); S++;
    }
    return aux;
}

TMAString TMAString::toLowerCase(void)
{
    TMAString aux(Dato);
    char *S=aux.Dato;
    while (*S!=0)
    {
        *S=tolower(*S); S++;
    }
    return aux;
}

int TMAString::compare(const TMAString& s)
{
    return strcmp(Dato,s.Dato);
}

TMAString TMAString::operator + (const char *str)
{
    char *buff;
    if (Dato!=NULL)
    {
        buff = new char [size + strlen(str) + 1];
        buff[0]=0;
        strcat(buff,Dato);
        strcat(buff,str);
    }
    else
    {
        buff = strdup(str);
    }
    TMAString ret(buff);
    if (buff!=NULL) delete buff;
    return ret;
}

TMAString TMAString::operator + (const TMAString& str)
{
    return (*this + str.Dato);
}

TMAString& TMAString::operator = (char *str)
{
    clear();
    if (str!=NULL)
    {    
        Dato = strdup(str);
        size = strlen(Dato);
    }
    return *this;
}

TMAString& TMAString::operator = (TMAString& str)
{
    *this = str.Dato;
    return *this;
}

TMAString& TMAString::operator = (TMAString str)
{
    *this = str.Dato;
    return *this;
}
        
#endif
