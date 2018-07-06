#ifndef _TMABITMAP_CPP_
#define _TMABITMAP_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMABitmap);

PMAGame TMABitmap::GMAGame = NULL;

TMABitmap::TMABitmap(SDL_Surface *bmp,bool shared)
{
    io_bmp = bmp;
    ib_destroy = (!shared);
}

PMABitmap TMABitmap::loadFromFile(const char *filename,bool compatible)
{    
    SDL_Surface *bmp = IMG_Load(filename);

    if (!bmp) return NULL;
    
    PMABitmap lbmp = new TMABitmap(bmp);
    if (!lbmp)
    {
        SDL_FreeSurface(bmp);
        return NULL;
    }
    else
    {
        if (compatible)
        {
            if (!lbmp->isAlpha()) 
                lbmp->makeDisplayCompatible();
            else
                lbmp->makeDisplayCompatibleWithAlpha();
        }
    }
    
    return lbmp;
}

PMABitmap TMABitmap::create(PMABitmap pbitmap,int x,int y,int width,int height)
{
    if (x<0 || y<0 || x>=pbitmap->io_bmp->w || y>=pbitmap->io_bmp->h) return NULL;
    
    int bpp = pbitmap->io_bmp->format->BytesPerPixel;
    Uint8 *pixels = (Uint8 *)pbitmap->io_bmp->pixels + (y * pbitmap->io_bmp->pitch) + (x * bpp);
    
    SDL_Surface *bmp = SDL_CreateRGBSurfaceFrom(pixels, width, height, 
        pbitmap->io_bmp->format->BitsPerPixel, 
        pbitmap->io_bmp->pitch,
        pbitmap->io_bmp->format->Rmask,
        pbitmap->io_bmp->format->Gmask,
        pbitmap->io_bmp->format->Bmask,
        pbitmap->io_bmp->format->Amask);    
    
    if (!bmp) return NULL;
    
    // Si el bitmap origen, es de 8 bits, hay que copiar la paleta indexada.
    //
    if (pbitmap->getColorDepth()<=8)
    {
        if (pbitmap->io_bmp->format->palette!=NULL)
        {
            SDL_SetColors(bmp,pbitmap->io_bmp->format->palette->colors,0,pbitmap->io_bmp->format->palette->ncolors);
        }                
    }

    PMABitmap lbitmap = new TMABitmap(bmp);
    if (!lbitmap)
    {
        SDL_FreeSurface(bmp);
        return NULL;
    }
    return lbitmap;
}

PMABitmap TMABitmap::create(int width,int height,bool videomem)
{
    PMABitmap lbitmap=NULL;
    SDL_Surface *lscr = (TMAGame::ScreenSurf==NULL)?SDL_GetVideoSurface():TMAGame::ScreenSurf;
  
    SDL_Surface *bmp = SDL_CreateRGBSurface((videomem)?SDL_HWSURFACE:SDL_SWSURFACE, width, height, 
        lscr->format->BitsPerPixel, 
        lscr->format->Rmask,
        lscr->format->Gmask,
        lscr->format->Bmask,
        lscr->format->Amask);
    
    if (!bmp) return NULL;
    
    lbitmap = new TMABitmap(bmp);
    if (!lbitmap)
    {
        SDL_FreeSurface(bmp);
        return NULL;
    }        
    return lbitmap;            
}
        
PMABitmap TMABitmap::create(int width,int height,int depth)
{
    PMABitmap lbitmap=NULL;
    SDL_Surface *bmp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, depth,0,0,0,0);
        
    if (!bmp) return NULL;    
    
    lbitmap = new TMABitmap(bmp);
    if (!lbitmap)
    {
        SDL_FreeSurface(bmp);
        return NULL;
    }        
    return lbitmap;            
}

PMABitmap TMABitmap::create(PMABitmap source)
{
    if (!source) return NULL;
    
    PMABitmap lbitmap=NULL;
    SDL_Surface *lscr = source->io_bmp;  
    SDL_Surface *bmp = SDL_CreateRGBSurface(lscr->flags, lscr->w, lscr->h, 
        lscr->format->BitsPerPixel, 
        lscr->format->Rmask,
        lscr->format->Gmask,
        lscr->format->Bmask,
        lscr->format->Amask);
    
    if (!bmp) return NULL;
    lbitmap = new TMABitmap(bmp);
    if (!lbitmap)
    {
        SDL_FreeSurface(bmp);
        return NULL;
    }        
    lbitmap->copyPalette(source);
    return lbitmap;   
}

PMABitmap TMABitmap::clone(void)
{
    SDL_Surface *surf = SDL_ConvertSurface(io_bmp,io_bmp->format,io_bmp->flags);
    
    if (surf!=NULL)
    {
        PMABitmap lclone = new TMABitmap(surf);
        if (isAlpha()) lclone->setAlpha(io_bmp->format->alpha);
        return lclone;
    }
    return NULL;
}

PMABitmap TMABitmap::cloneFlipX(void)
{
    PMABitmap surf = TMABitmap::create(this);
        
    if (surf!=NULL)
    {
        bool isalpha = isAlpha();
        Uint8 alpha = io_bmp->format->alpha;
        
        if (io_bmp->format->BitsPerPixel<=8) surf->copyPalette(this);
        if (isTransparent()) SDL_FillRect(surf->io_bmp,NULL,io_bmp->format->colorkey);
        if (isalpha) disableAlpha();
        SDL_Rect lrs,lrd;
        
        lrs.y=0;
        lrs.h=io_bmp->h;
        lrs.w=1;
        lrd.y=0;
        lrd.x=io_bmp->w-1;
        
        for (int x=0;x<io_bmp->w;x++)
        {
            lrs.x=x;
            SDL_BlitSurface(io_bmp, &lrs, surf->io_bmp, &lrd);
            lrd.x--;
        }
        
        if (isTransparent()) SDL_SetColorKey(surf->io_bmp,io_bmp->flags,io_bmp->format->colorkey);
        if (isalpha)
        {
            surf->setAlpha(alpha);
            setAlpha(alpha);
        }
    }
    return surf;
}

PMABitmap TMABitmap::cloneFlipY(void)
{
    PMABitmap surf = TMABitmap::create(this);
        
    if (surf!=NULL)
    {
        bool isalpha = isAlpha();
        Uint8 alpha = io_bmp->format->alpha;
        
        if (io_bmp->format->BitsPerPixel<=8) surf->copyPalette(this);
        if (isTransparent()) SDL_FillRect(surf->io_bmp,NULL,io_bmp->format->colorkey);
        if (isalpha) disableAlpha();

        SDL_Rect lrs,lrd;
        
        lrs.x=0;
        lrs.w=io_bmp->w;
        lrs.h=1;
        lrd.x=0;
        lrd.y=io_bmp->h-1;
        
        for (int y=0;y<io_bmp->h;y++)
        {
            lrs.y=y;
            SDL_BlitSurface(io_bmp, &lrs, surf->io_bmp, &lrd);
            lrd.y--;
        }
        
        if (isTransparent()) SDL_SetColorKey(surf->io_bmp,io_bmp->flags,io_bmp->format->colorkey);
        if (isalpha)
        {
            surf->setAlpha(alpha);
            setAlpha(alpha);
        }
    }
    return surf;
}

PMABitmap TMABitmap::cloneFlipXY(void)
{
    PMABitmap fx = cloneFlipX();
    if (!fx) return NULL;
    
    PMABitmap fyx = fx->cloneFlipY();
    if (!fyx)
    {
        delete fx;
        return NULL;
    }
    
    delete fx;
    return fyx;
}

bool TMABitmap::copyPalette(const PMABitmap source)
{
    // Si el bitmap origen, es de 8 bits, hay que copiar la paleta indexada.
    //
    if (source->getColorDepth()<=8 && getColorDepth()<=8)
    {
        if (source->io_bmp->format->palette->ncolors==io_bmp->format->palette->ncolors)
        {
            SDL_SetColors(io_bmp,source->io_bmp->format->palette->colors,0,source->io_bmp->format->palette->ncolors);
            return true;
        }                
    }   
    return false;
}

bool TMABitmap::saveToFile(const char *filename)
{
    return (SDL_SaveBMP(io_bmp,filename)==0);
}

TMABitmap::~TMABitmap()
{
    if (ib_destroy && (io_bmp!=NULL))
    {
        SDL_FreeSurface(io_bmp);
    }
}       

int TMABitmap::getColorDepth(void)
{
    return io_bmp->format->BitsPerPixel;
}

int TMABitmap::getWidth(void)
{
    return io_bmp->w;
}

int TMABitmap::getHeight(void) 
{
    return io_bmp->h;
}

void TMABitmap::getSize(int& width,int& height)
{
    width = io_bmp->w;
    height = io_bmp->h;
}

void TMABitmap::draw(const PMABitmap origen,int px,int py)
{
    SDL_Rect rdest;
    rdest.x = px; rdest.y = py;
    SDL_BlitSurface(origen->io_bmp, NULL, io_bmp, &rdest);
}

void TMABitmap::draw(const PMABitmap origen,int ox,int oy,int width,int height,
                     int dx,int dy)
{
    SDL_Rect rsource;
    SDL_Rect rdest;
    rsource.x = ox; rsource.y = oy;
    rsource.w = width; rsource.h = height;
    rdest.x = dx; rdest.y = dy;
    
    SDL_BlitSurface(origen->io_bmp, &rsource, io_bmp, &rdest);
}

void TMABitmap::drawSprite(const PMABitmap origen,int px,int py,bool flipx,bool flipy)
{
    PMABitmap spr=NULL;
    SDL_Rect lrs,lrd;
        
    if (!(flipx || flipy))
    {
        draw(origen,px,py);
    }
    else 
    {        
        if (flipx && flipy) 
        {
            spr = origen->cloneFlipXY();
            if (spr)
            {
                draw(spr,px,py);
                delete spr;
            }
        }
        else if (flipx) 
        {            
            lrs.y=0;
            lrs.h=origen->io_bmp->h;
            lrs.w=1;
            lrd.y=py;
            lrd.x=px+origen->io_bmp->w-1;
            
            for (int x=0;x<origen->io_bmp->w;x++)
            {
                lrs.x=x;
                SDL_BlitSurface(origen->io_bmp, &lrs,io_bmp , &lrd);
                lrd.x--;
            }
        }
        else 
        {
            lrs.x=0;
            lrs.w=origen->io_bmp->w;
            lrs.h=1;
            lrd.x=px;
            lrd.y=py+origen->io_bmp->h-1;
            
            for (int y=0;y<origen->io_bmp->h;y++)
            {
                lrs.y=y;
                SDL_BlitSurface(origen->io_bmp, &lrs,io_bmp , &lrd);
                lrd.y--;
            }
        }
        
    }
}

void TMABitmap::drawSpriteColorized(const PMABitmap spr,int px,int py,bool flipx,bool flipy,int r,int g,int b)
{
    PMABitmap bmp = NULL;
    
    if (flipx && flipy) bmp = spr->cloneFlipXY();
    else if (flipx) bmp = spr->cloneFlipX();
    else if (flipy) bmp = spr->cloneFlipY();
    else bmp = spr->clone();

    if (bmp)
    {    
        Uint8 tr,tg,tb;
        Uint32 trans = spr->io_bmp->format->colorkey;
        SDL_GetRGB(trans, bmp->io_bmp->format, &tr,&tg,&tb);
        trans = MAKERGBCOLOR(tr,tg,tb);
            
        for (int x=0;x<bmp->io_bmp->w;x++)
        for (int y=0;y<bmp->io_bmp->h;y++)
        {
            Uint32 color_value = bmp->getPixel(x, y);
            if (color_value!=trans)
            {
                int r1 = GET_REDVALUE(color_value)*r/255;
                int g1 = GET_GREENVALUE(color_value)*g/255;
                int b1 = GET_BLUEVALUE(color_value)*b/255;
                bmp->setPixel(x,y,MAKERGBACOLOR(r1,g1,b1,GET_ALPHAVALUE(color_value)));
            }
        }
        
        SDL_Rect rdest;
        rdest.x = px;
        rdest.y = py;
        SDL_BlitSurface(bmp->io_bmp, NULL, io_bmp, &rdest);
        delete bmp;
    }
}       

void TMABitmap::drawSpriteShadowed(const PMABitmap spr,int px,int py,bool flipx,bool flipy,int alpha)
{
    PMABitmap bmp = NULL;
    
    if (flipx && flipy) bmp = spr->cloneFlipXY();
    else if (flipx) bmp = spr->cloneFlipX();
    else if (flipy) bmp = spr->cloneFlipY();
    else bmp = spr->clone();

    if (bmp)
    {    
        Uint8 tr,tg,tb;
        Uint32 trans = bmp->io_bmp->format->colorkey;
        SDL_GetRGB(trans, bmp->io_bmp->format, &tr,&tg,&tb);
        trans = MAKERGBCOLOR(tr,tg,tb);
            
        for (int x=0;x<bmp->io_bmp->w;x++)
        for (int y=0;y<bmp->io_bmp->h;y++)
        {
            Uint32 color_value = bmp->getPixel(x, y);
            if (color_value!=trans)
            {
                bmp->setPixel(x,y,MAKERGBCOLOR(0,0,0));
            }
        }
        
        SDL_Rect rdest;
        rdest.x = px;
        rdest.y = py;
        bmp->setAlpha(alpha);
        SDL_BlitSurface(bmp->io_bmp, NULL, io_bmp, &rdest);
        delete bmp;
    }
}

bool TMABitmap::isAlpha(void)
{
    return (io_bmp->flags & SDL_SRCALPHA)>0;
}

void TMABitmap::setAlpha(int alpha)
{
    SDL_SetAlpha(io_bmp,SDL_SRCALPHA,alpha);
}

void TMABitmap::disableAlpha(void)
{
    SDL_SetAlpha(io_bmp,0,0);
}

void TMABitmap::lock(void)
{
    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        SDL_LockSurface(io_bmp);
    }
}

void TMABitmap::unlock(void)
{
    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        SDL_UnlockSurface(io_bmp);
    }
}

bool TMABitmap::makeDisplayCompatible(void)
{
    SDL_Surface *surf = SDL_DisplayFormat(io_bmp);
    if (surf)
    {
        SDL_FreeSurface(io_bmp);
        io_bmp=surf;
        return true;
    }
    return false;
}

bool TMABitmap::makeDisplayCompatibleWithAlpha(void)
{
    SDL_Surface *surf = SDL_DisplayFormatAlpha(io_bmp);
    if (surf)
    {
        SDL_FreeSurface(io_bmp);
        io_bmp=surf;
        return true;
    }
    return false;
}

void TMABitmap::clear(Uint8 red,Uint8 green,Uint8 blue)
{
    SDL_FillRect(io_bmp, NULL, SDL_MapRGB(io_bmp->format,red,green,blue));
}

void TMABitmap::clear(Uint32 color)
{
    SDL_FillRect(io_bmp, NULL, SDL_MapRGB(io_bmp->format,GET_REDVALUE(color),GET_GREENVALUE(color),GET_BLUEVALUE(color)));
}

Uint32 TMABitmap::getPixel(int px,int py)
{
    Uint32 ret;

    if (px<0 || py<0 || px>=io_bmp->w || py>=io_bmp->h) return 0;
    
    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        if ( SDL_LockSurface(io_bmp) < 0 ) return 0;
    }

    int bpp = io_bmp->format->BytesPerPixel;
    
    /* Here p is the address to the pixel we want to retrieve */
    
    Uint8 *p = (Uint8 *)io_bmp->pixels + py * io_bmp->pitch + px * bpp;

    switch(bpp) {
    case 1:
        ret = *p;
        break;

    case 2:
        ret = *(Uint16 *)p;
        break;
        
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            ret = p[0] << 16 | p[1] << 8 | p[2];
        else
            ret = p[0] | p[1] << 8 | p[2] << 16;
        break;
        
    case 4:
        ret = *(Uint32 *)p;
        break;

    default:
        ret = 0;       /* shouldn't happen, but avoids warnings */
    }
    
    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        SDL_UnlockSurface(io_bmp);
    }
    
    Uint8 r,g,b;
    SDL_GetRGB(ret, io_bmp->format, &r, &g, &b);
    
    return MAKERGBCOLOR(r,g,b);
}

void TMABitmap::setPixel(int px,int py,Uint32 color)
{
    SDL_Rect lrect;
    
    SDL_GetClipRect(io_bmp,&lrect);
    if (px<lrect.x || py<lrect.y || px>=lrect.w|| py>=lrect.h) return;

    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        if ( SDL_LockSurface(io_bmp) < 0 ) return;
    }

    int bpp = io_bmp->format->BytesPerPixel;
    
    Uint8 *p = (Uint8 *)io_bmp->pixels + py * io_bmp->pitch + px * bpp;

    switch(bpp) {
    case 1:
        color = SDL_MapRGBA(io_bmp->format, GET_REDVALUE(color),GET_GREENVALUE(color),GET_BLUEVALUE(color),GET_ALPHAVALUE(color));
        *p = color;
        break;

    case 2:
        color = SDL_MapRGBA(io_bmp->format, GET_REDVALUE(color),GET_GREENVALUE(color),GET_BLUEVALUE(color),GET_ALPHAVALUE(color));
        *(Uint16 *)p = color;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = GET_REDVALUE(color);
            p[1] = GET_GREENVALUE(color);
            p[2] = GET_BLUEVALUE(color);
        } else {
            p[2] = GET_REDVALUE(color);
            p[1] = GET_GREENVALUE(color);
            p[0] = GET_BLUEVALUE(color);
        }
        break;

    case 4:
        color = SDL_MapRGBA(io_bmp->format, GET_REDVALUE(color),GET_GREENVALUE(color),GET_BLUEVALUE(color),GET_ALPHAVALUE(color));
        *(Uint32 *)p = color;
        break;
    }

    if ( SDL_MUSTLOCK(io_bmp) ) 
    {
        SDL_UnlockSurface(io_bmp);
    }
}

void TMABitmap::drawLine(int ox,int oy,int dx,int dy,Uint32 color)
{
    lineColor(io_bmp,ox,oy,dx,dy,color);
}

void TMABitmap::drawRect(int ox,int oy,int dx,int dy,Uint32 color)
{
    rectangleColor(io_bmp,ox,oy,dx,dy,color);
}

void TMABitmap::drawRectFilled(int ox,int oy,int dx,int dy,Uint32 color)
{
    boxColor(io_bmp,ox,oy,dx,dy,color);
}

void TMABitmap::drawCircle(int cx,int cy,int radio,Uint32 color)
{
    circleColor(io_bmp,cx,cy,radio,color);
}

void TMABitmap::drawCircleFilled(int cx,int cy,int radio,Uint32 color)
{
    filledCircleColor(io_bmp,cx,cy,radio,color);
}

void TMABitmap::drawEllipse(int cx,int cy,int radiox,int radioy,Uint32 color)
{
    ellipseColor(io_bmp,cx,cy,radiox,radioy,color);
}

void TMABitmap::drawEllipseFilled(int cx,int cy,int radiox,int radioy,Uint32 color)
{
    filledEllipseColor(io_bmp,cx,cy,radiox,radioy,color);
}

void TMABitmap::setTransparentColor(Uint32 color)
{
   color = SDL_MapRGB(io_bmp->format,GET_REDVALUE(color),GET_GREENVALUE(color),GET_BLUEVALUE(color));
   SDL_SetColorKey(io_bmp, SDL_SRCCOLORKEY, color);
}    

bool TMABitmap::isTransparent(void)
{
    return (io_bmp->flags & SDL_SRCCOLORKEY)>0;
}

void TMABitmap::unsetTransparentColor(void)
{
   SDL_SetColorKey(io_bmp, 0, 0);
}    

void TMABitmap::bilinearStretch(const PMABitmap origen,int ox,int oy,int owidth,int oheight,
        int dx,int dy,int dwidth,int dheight)
{
    double fraction_x, fraction_y, one_minus_x, one_minus_y;
    int ceil_x, ceil_y, floor_x, floor_y;
    unsigned char red, green, blue;
    unsigned char b1, b2;
    Uint32 c1,c2,c3,c4;

    double nXFactor = (double)owidth/(double)dwidth;
    double nYFactor = (double)oheight/(double)dheight;
        
    for (int x = 0; x < dwidth; ++x)
    {
        for (int y = 0; y < dheight; ++y)
        {
            // Setup

            floor_x = (int)floor(x * nXFactor);
            floor_y = (int)floor(y * nYFactor);
            ceil_x = floor_x + 1;
            if (ceil_x >= owidth) ceil_x = floor_x;
            ceil_y = floor_y + 1;
            if (ceil_y >= oheight) ceil_y = floor_y;
            fraction_x = x * nXFactor - floor_x;
            fraction_y = y * nYFactor - floor_y;
            one_minus_x = 1.0 - fraction_x;
            one_minus_y = 1.0 - fraction_y;

            c1 = origen->getPixel(ox+floor_x, oy+floor_y);
            c2 = origen->getPixel(ox+ceil_x, oy+floor_y);
            c3 = origen->getPixel(ox+floor_x, oy+ceil_y);
            c4 = origen->getPixel(ox+ceil_x, oy+ceil_y);

            // Blue
            b1 = (unsigned char)(one_minus_x * GET_BLUEVALUE(c1) + fraction_x * GET_BLUEVALUE(c2));
            b2 = (unsigned char)(one_minus_x * GET_BLUEVALUE(c3) + fraction_x * GET_BLUEVALUE(c4));
            blue = (unsigned char)(one_minus_y * (double)(b1) + fraction_y * (double)(b2));

            // Green
            b1 = (unsigned char)(one_minus_x * GET_GREENVALUE(c1) + fraction_x * GET_GREENVALUE(c2));
            b2 = (unsigned char)(one_minus_x * GET_GREENVALUE(c3) + fraction_x * GET_GREENVALUE(c4));
            green = (unsigned char)(one_minus_y * (double)(b1) + fraction_y * (double)(b2));

            // Red
            b1 = (unsigned char)(one_minus_x * GET_REDVALUE(c1) + fraction_x * GET_REDVALUE(c2));
            b2 = (unsigned char)(one_minus_x * GET_REDVALUE(c3) + fraction_x * GET_REDVALUE(c4));            
            red = (unsigned char)(one_minus_y * (double)(b1) + fraction_y * (double)(b2));

            this->setPixel(dx+x,dy+y, MAKERGBCOLOR(red,green,blue));
        }
    }
}

#endif
