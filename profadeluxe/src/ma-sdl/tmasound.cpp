#ifndef _TMASOUND_CPP_
#define _TMASOUND_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMASound);

TMASound::TMASound()
{
    psound=NULL;
    ii_voice=-1;
}

TMASound::~TMASound()
{
    unload();
}

void TMASound::unload(void)
{
    if (psound!=NULL) 
    {
        stop();
        Mix_FreeChunk(psound);
        psound=NULL;
    }
}
 
bool TMASound::load(const char *filename)
{
    unload();
    psound = Mix_LoadWAV(filename);
    return (psound!=NULL);
}

void TMASound::play(bool loop,int volume,int pan)
{
    if (psound!=NULL)
    {
        if (volume>128) volume=128;
        Mix_VolumeChunk(psound,volume);
        ii_voice = Mix_PlayChannel(-1,psound,(loop)?(-1):0);
        //if (pan!=127) voice_set_pan(ii_voice,pan);
    }        
}

void TMASound::stop(void)
{
    if (isPlaying()) 
    {
        Mix_HaltChannel(ii_voice);
        ii_voice=-1;
    }
}

bool TMASound::isPlaying(void)
{
    if (ii_voice>=0)
    {
        return (Mix_Playing(ii_voice)!=0);
    }
    return false;
}
            
#endif
