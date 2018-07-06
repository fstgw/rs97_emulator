#ifndef _TMAFONT_CPP_
#define _TMAFONT_CPP_

#include "ma_classes.h"
#include <string.h>

REGISTER_CLASS_ID(TMAFont);

TMAFont::TMAFont()
{
    io_bank=NULL;
    width=0; height=0; ii_spacex=0;
    is_chars="";
}

TMAFont::~TMAFont()
{
    if (io_bank!=NULL)
    {
        delete io_bank;
        io_bank=NULL;
    }
}

bool TMAFont::load(const char *fontFile,int width,int height,int col,int row,
                   bool pixel_separator,int transcolor)
{
    if (io_bank!=NULL)
    {
        delete io_bank;
        io_bank=NULL;
    }
    io_bank = TMAImageBank::createStatic(fontFile,col,row,width,height,pixel_separator);
    if (io_bank!=NULL)
    {
        this->width = width;
        this->height = height;
        if (transcolor!=0) 
        {
            for (int i=0;i<io_bank->size();i++)
            {
                const PMABitmap bmp = io_bank->getBitmap(i);
                if (bmp!=NULL) bmp->setTransparentColor(transcolor);
            }
        }
        ii_transcolor = transcolor;
        return true;
    }
    return false;
}

void TMAFont::setSpaceBetweenChars(int sp)
{
    ii_spacex = sp;
}

void TMAFont::setCharacters(const char *chars)
{
    is_chars = chars;
}

int TMAFont::getTextWidth(const char *txt)
{
    int sz=strlen(txt);
    return (sz*(width+ii_spacex)) - ii_spacex;
}

int TMAFont::getTextHeight(void)
{
    return height;
}

void TMAFont::setAlpha(int alpha)
{
    for (int i=0;i<io_bank->size();i++)
    {
        const PMABitmap bmp = io_bank->getBitmap(i);
        if (bmp!=NULL) bmp->setAlpha(alpha);
    }
}

void TMAFont::disableAlpha(void)
{
    for (int i=0;i<io_bank->size();i++)
    {
        const PMABitmap bmp = io_bank->getBitmap(i);
        if (bmp!=NULL) bmp->disableAlpha();
    }
}

void TMAFont::drawText(TMABitmap& bmp,const char *text,int x, int y,
                        int *offsety,int scrwidth)
{
    if (io_bank==NULL) return;
    
	int i,j,sz=strlen(text);
	int ix=x,iy=y;
	
	if (x==-1)
	{
		ix = (scrwidth - getTextWidth(text)) / 2;
	}				
		
	for (i=0;i<sz;i++)
	{
        j = (strchr(is_chars,text[i]) - is_chars);
		
        if (j>=0)
		{			
			if (offsety!=NULL)
			{
				if (ix<0 || (ix>scrwidth-1) ) iy = y;
				else iy = y + offsety[ix];
			}
            bmp.draw(io_bank->getBitmap(j),ix,iy);
		}
		ix+=(width + ii_spacex);
	}
}


#endif
