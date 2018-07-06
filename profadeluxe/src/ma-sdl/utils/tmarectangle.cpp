#ifndef _TMARECTANGLE_CPP_
#define _TMARECTANGLE_CPP_

#include "utils.h"
#include "math.h"
#include "../ma_classes.h"

REGISTER_CLASS_ID(TMARectangle);

TMARectangle::TMARectangle()
{
    setBounds(0,0,0,0);
}

TMARectangle::TMARectangle(int px,int py,int w,int h)
{
    setBounds(px,py,w,h);
}

TMARectangle::TMARectangle(const TMARectangle& r) 
{
  	setBounds(r.x, r.y, r.width, r.height);
}
TMARectangle::TMARectangle(int w, int h)
{
    setBounds(0, 0, width, height);
}

TMARectangle& TMARectangle::operator = (TMARectangle& r)
{
    setBounds(r);
    return *this;
}

TMARectangle& TMARectangle::operator = (TMARectangle r)
{
    setBounds(r);
    return *this;
}
        
void TMARectangle::setBounds(TMARectangle& r)
{
    setBounds(r.x, r.y, r.width, r.height);
}	

void TMARectangle::setBounds(int px, int py, int pw, int ph)
{
    x=px; y=py; width=pw; height=ph;
}	

void TMARectangle::setLocation(int px, int py) 
{
    x=px; y=py;
}	

void TMARectangle::translate(int px, int py)
{
    x+=px; y+=py;
}	

void TMARectangle::setSize(int pw,int ph)
{
    width = pw; height = ph;
}	

bool TMARectangle::contains(int px, int py) 
{
    return (px >= x) && ((px - x) < width) && (py >= y) && ((py-y) < height);
}

bool TMARectangle::intersects(TMARectangle& r) 
{
    return !((r.x + r.width <= x) ||
        	 (r.y + r.height <= y) ||
        	 (r.x >= x + width) ||
        	 (r.y >= y + height));
}

TMARectangle TMARectangle::intersection(TMARectangle& r) 
{
    int x1 = max(x, r.x);
    int x2 = min(x + width, r.x + r.width);
    int y1 = max(y, r.y);
    int y2 = min(y + height, r.y + r.height);
    return TMARectangle(x1, y1, x2 - x1, y2 - y1);
}

TMARectangle TMARectangle::unionRect(TMARectangle& r)
{
    int x1 = min(x, r.x);
    int x2 = max(x + width, r.x + r.width);
    int y1 = min(y, r.y);
    int y2 = max(y + height, r.y + r.height);
    return TMARectangle(x1, y1, x2 - x1, y2 - y1);
}

bool TMARectangle::isEmpty() 
{
    return (width <= 0) || (height <= 0);
}

#endif
