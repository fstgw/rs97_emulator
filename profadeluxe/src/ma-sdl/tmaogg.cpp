#ifndef _TMAOGG_CPP_
#define _TMAOGG_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMAOgg);

TMAOgg::TMAOgg()
{
    psound=NULL;
}

TMAOgg::~TMAOgg()
{
    close();
}

void TMAOgg::close() 
{
    if (psound!=NULL) 
    {
        stop();
        Mix_FreeMusic(psound);
        psound=NULL;
    }
}
 
bool TMAOgg::load(const char *filename)
{
  // Si hay un archivo previo abierto, lo cerramos.
  //
  close();
  psound = Mix_LoadMUS(filename);
  return (psound!=NULL);
}

void TMAOgg::play(bool loop,int volume)
{
    if (psound!=NULL)
    {
        Mix_PlayMusic(psound,(loop)?(-1):1);
        Mix_VolumeMusic(volume);
    }        
}

void TMAOgg::stop(void)
{
    if (psound!=NULL) Mix_HaltMusic();
}

bool TMAOgg::isPlaying(void)
{
    if (psound!=NULL) return Mix_PlayingMusic();
    return false;
}
           
#endif
