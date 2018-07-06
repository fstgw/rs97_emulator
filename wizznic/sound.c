#include "sound.h"

#include <SDL/SDL_mixer.h>

int initSound()
{
  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 1024;
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
  {
    return(0);
  }
  Mix_AllocateChannels(16);

  if(loadSamples())
    return(1);
  else
    return(0);
}



static Mix_Chunk *samples[NUMSAMPLES];
static int lastPlayed[NUMSAMPLES];

int loadSample(const char* fileName, int index)
{
  lastPlayed[index]=0;
  samples[index] = NULL;
  samples[index] = Mix_LoadWAV(fileName);
  if(!samples[index])
  {
    printf("Error: Couldn't load %s\n",fileName);
    return(0);
  }
  return(1);
}

int loadSamples()
{

#if 1
  if(! loadSample( "data/snd/click.ogg", SND_CLICK ) ) return(0);
  if(! loadSample( "data/snd/brickmove.ogg", SND_BRICKMOVE ) ) return(0);
  if(! loadSample( "data/snd/brickgrab.ogg", SND_BRICKGRAB ) ) return(0);
  if(! loadSample( "data/snd/brickbreak.ogg", SND_BRICKBREAK ) ) return(0);
  if(! loadSample( "data/snd/scoretick.ogg", SND_SCORECOUNT ) ) return(0);
  if(! loadSample( "data/snd/rocketboom.ogg", SND_ROCKETBOOM ) ) return(0);
  if(! loadSample( "data/snd/rocketlaunch.ogg", SND_ROCKETLAUNCH ) ) return(0);
  if(! loadSample( "data/snd/countdown.ogg", SND_COUNTDOWNTOSTART ) ) return(0);
  if(! loadSample( "data/snd/start.ogg", SND_START ) ) return(0);
  if(! loadSample( "data/snd/timeout.ogg", SND_TIMEOUT ) ) return(0);
  if(! loadSample( "data/snd/menumove.ogg", SND_MENUMOVE ) ) return(0);
  if(! loadSample( "data/snd/victory.ogg", SND_VICTORY ) ) return(0);
#else
  if(! loadSample( "data/snd/click.wav", SND_CLICK ) ) return(0);
  if(! loadSample( "data/snd/brickmove.wav", SND_BRICKMOVE ) ) return(0);
  if(! loadSample( "data/snd/brickgrab.wav", SND_BRICKGRAB ) ) return(0);
  if(! loadSample( "data/snd/brickbreak.wav", SND_BRICKBREAK ) ) return(0);
  if(! loadSample( "data/snd/scoretick.wav", SND_SCORECOUNT ) ) return(0);
  if(! loadSample( "data/snd/rocketboom.wav", SND_ROCKETBOOM ) ) return(0);
  if(! loadSample( "data/snd/rocketlaunch.wav", SND_ROCKETLAUNCH ) ) return(0);
  if(! loadSample( "data/snd/countdown.wav", SND_COUNTDOWNTOSTART ) ) return(0);
  if(! loadSample( "data/snd/start.wav", SND_START ) ) return(0);
  if(! loadSample( "data/snd/timeout.wav", SND_TIMEOUT ) ) return(0);
  if(! loadSample( "data/snd/menumove.wav", SND_MENUMOVE ) ) return(0);
  if(! loadSample( "data/snd/victory.wav", SND_VICTORY ) ) return(0);
#endif

  return(1);
}

void sndPlay(int sample, int posX)
{
  int freeChannel=-1;
  int i;

  //Find free channel
  for(i=0;i<16;i++)
  {
    if(!Mix_Playing(i))
    {
      freeChannel=i;
      break;
    }
  }

  int right = (posX*255)/320;
  Mix_SetPanning(freeChannel, 255-right, right );

  Mix_PlayChannel(freeChannel, samples[sample], 0);
}

//Only play if sample was not played the last couple of frames
void sndPlayOnce(int sample, int posX)
{
  int ticks=SDL_GetTicks();
  if(ticks-lastPlayed[sample] < 50) return;

  lastPlayed[sample]=ticks;
  sndPlay(sample, posX);
}
