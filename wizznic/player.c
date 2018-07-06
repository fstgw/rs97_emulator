#include "player.h"

#include <stdio.h>

#ifdef GP2X
#include "wiz.h"
#endif

static player_t playerInfo;

player_t* player()
{
  return(&playerInfo);
}

void initPlayer()
{
  char temp[16];

  playerInfo.bestScore = 0;
  playerInfo.bestLevel = 0;

  playerInfo.gameScore=0;
  playerInfo.boardScore=0;
  playerInfo.lives=3;
  playerInfo.retries=3;
  playerInfo.level=0;
  playerInfo.paused=0;
  playerInfo.gameOver=0;
  playerInfo.finishedLevel=0;

  //Read user.ini if it exists
  //First line is volume, next is highscore, and last is level
  FILE *f = fopen("user.ini", "r");
  if(f)
  {
    //Vol
    fgets( temp, 16, f);
    #ifdef GP2X
    WIZ_SetVolume( atoi( temp ) );
    #endif

    //Score
    fgets( temp, 16, f);
    playerInfo.bestScore = atoi( temp );

    //Level
    fgets( temp, 16, f);
    playerInfo.bestLevel = atoi( temp );

    if(playerInfo.bestLevel+1 > getNumLevels())
    {
      playerInfo.bestLevel=getNumLevels()-1;
    }

    //Close file
    fclose( f );
  }


}

//Saves score to file if better
void savePlayer()
{
  if(playerInfo.gameScore > playerInfo.bestScore) playerInfo.bestScore=playerInfo.gameScore;
  if(playerInfo.level > playerInfo.bestLevel) playerInfo.bestLevel=playerInfo.level;

  //Save to file.
  FILE *f = fopen("user.ini", "w");
  if(f)
  {
    int v=40;
    #ifdef GP2X
    v=WIZ_GetVolume();
    #endif

    fprintf(f, "%i\n%i\n%i\n", v, playerInfo.bestScore, playerInfo.bestLevel );

    fclose( f );
  }
}
