#include "game.h"


static playField pf;
static cursorType cur;
static int countdown;
static int countdownSeconds;
static char buf[32];
#define GAMESTATEPLAYING 0
#define GAMESTATEINIT 1
#define GAMESTATECLEANUP 2
#define GAMESTATEOUTOFTIME 3
#define GAMESTATECOUNTDOWN 4


static int gameState=GAMESTATEINIT;



void drawUi(SDL_Surface* screen)
{
   //Draw text
    char tempStr[16];

    txtWriteCenter(screen, FONTSMALL, "Time:", 46, 64);
    int secLeft = pf.timeLeft/1000;
    if(pf.timeLeft > 60000)
    {
      sprintf(tempStr,"%i;%1.2i",secLeft/60,secLeft%60);
    } else {
      sprintf(tempStr,"%i",secLeft);
    }
    txtWriteCenter(screen, FONTMEDIUM, tempStr,46, 76);


    txtWriteCenter(screen, FONTSMALL, "Level:", 46 /*13*/,120);

    sprintf(tempStr, "%i", player()->level  );
    txtWriteCenter(screen, FONTMEDIUM, tempStr, 46,132);


    txtWriteCenter(screen, FONTSMALL, "Score:", 46,176);
    sprintf(tempStr, "%i", player()->boardScore );
    txtWriteCenter(screen, FONTMEDIUM, tempStr, 46, 188);
}

int runGame(SDL_Surface* screen)
{
  if(gameState==GAMESTATEPLAYING)
  {


    //If it's ever paused when this is called, cleanup.
    if(player()->paused)
    {
      gameState=GAMESTATECLEANUP;
      return(STATEPLAY);
    }

    //Pause ?
    if( getButton( C_BTNMENU ) )
    {
      resetBtn( C_BTNMENU );
      player()->paused=1;
      return(STATEMENU);
    }

    //Handle input
    int lim=1; //Limit cursor travel...
    int goUp=0, goDown=0, goLeft=0, goRight=0;
    if( getButton( C_UP ) )
    {
      if( getBtnTime( C_UP ) > REPEATDELAY )
      {
        goUp=1;
      } else if(getBtnTime(C_UP)==0) {
        goUp=1;
        lim=0;
      }
    }

    if( getButton( C_DOWN ) )
    {
      if( getBtnTime( C_DOWN ) > REPEATDELAY )
      {
        goDown=1;
      } else if(getBtnTime(C_DOWN)==0) {
        goDown=1;
        lim=0;
      }
    }

    if( getButton( C_LEFT ) )
    {
      if( getBtnTime( C_LEFT ) > REPEATDELAY )
      {
        goLeft=1;
      } else if(getBtnTime(C_LEFT)==0) {
        goLeft=1;
        lim=0;
      }
    }

    if( getButton( C_RIGHT ) )
    {
      if( getBtnTime( C_RIGHT ) > REPEATDELAY )
      {
        goRight=1;
      } else if(getBtnTime(C_RIGHT)==0) {
        goRight=1;
        lim=0;
      }
    }

      //Drag
      if( getButton( C_BTNX ) || getButton( C_BTNB ) )
      {
        //Sound grab brick
        if(!cur.lock && pf.board[cur.x][cur.y] )
        {
          cur.lock=1;
          if(isBrick(pf.board[cur.x][cur.y]))
          {
            sndPlay( SND_BRICKGRAB, cur.px );
          }
        }

        if( goLeft )
        {
          if( pf.board[cur.x][cur.y] &&
              isBrick(pf.board[cur.x][cur.y]) &&
              !isBrickFalling(&pf, cur.x,cur.y) &&
              moveBrick(&pf, cur.x, cur.y, DIRLEFT,0, CURLOCK, CURSORMOVESPEED) )
          {
            sndPlay(SND_BRICKMOVE, cur.px);
          }
        }

        if( goRight )
        {
          if( pf.board[cur.x][cur.y] &&
          isBrick(pf.board[cur.x][cur.y]) &&
          !isBrickFalling(&pf, cur.x,cur.y) &&
          moveBrick(&pf, cur.x, cur.y, DIRRIGHT,0, CURLOCK, CURSORMOVESPEED) )
          {
            sndPlay(SND_BRICKMOVE, cur.px);
          }
        }
      } else {
        cur.lock=0;
        if( goLeft ) moveCursor(&cur, DIRLEFT, 0, lim);
        if( goRight ) moveCursor(&cur, DIRRIGHT, 0, lim);
        if( goUp ) moveCursor(&cur, 0, DIRUP, lim);
        if( goDown ) moveCursor(&cur, 0, DIRDOWN, lim);

      }


    //Sim first, so moving blocks get evaluated before getting moved again
    simField(&pf, &cur);

    //Do rules
    int ret=doRules(&pf);

    //Draw scene
    draw(&cur,&pf, screen);

    //If no more bricks, countdown time left.
    if(ret < 0)
    {
      pf.timeLeft -= 1000;
      player()->boardScore +=1;

      if(getButton(C_BTNX))
      {
        while(pf.timeLeft > 0)
        {
          player()->boardScore +=1;
          pf.timeLeft -= 1000;
        }
      }

      sndPlayOnce(SND_SCORECOUNT, 160);
      if(pf.timeLeft < 1)
      {
        pf.timeLeft=0;
        //Completed level
        player()->gameOver=0;
        player()->finishedLevel=1;
        gameState=GAMESTATECLEANUP;
        sndPlay(SND_VICTORY, 160);
      }
    } else if(ret > 0)
    {
      if(ret > 2)
      {
        printf("%i Combo!\n",ret);
      }
      player()->boardScore += ret*ret*11*(player()->level+1);
    }

    //Update time:
    pf.timeLeft -= getTicks();
    if(pf.timeLeft < 1 && !player()->finishedLevel && ret!=-1 )
    {
      countdown=4000;
      gameState=GAMESTATEOUTOFTIME;
      sndPlay(SND_TIMEOUT, 160);
    }

    //Draw text
    drawUi(screen);

  } else if(gameState==GAMESTATECOUNTDOWN)
  {

    draw(&cur,&pf, screen);
    countdown -=getTicks();

    if( getButton( C_BTNMENU ) )
    {
      player()->paused=1;
      resetBtn( C_BTNMENU );
      return(STATEMENU);
    }

    if( getButton( C_BTNX ) || getButton( C_BTNB ) )
    {
      countdownSeconds=0;
      countdown=500;
    }

    drawShowCountDown(screen, countdownSeconds);

/*    if(countdownSeconds==0)
    {
      sprintf(buf,"Start !",countdownSeconds);
    } else {
      sprintf(buf,"%i",countdownSeconds);
    }
    txtWriteCenter(screen, FONTMEDIUM, buf, 160,120-24);*/


    drawUi(screen);


    if(countdown < 1)
    {
      countdown=1000;
      countdownSeconds--;

      if(countdownSeconds == -1)
      {
        gameState=GAMESTATEPLAYING;
        return(STATEPLAY);
      }
      if(countdownSeconds==0)
      {
        countdown=500;
        sndPlay(SND_START, 160);
      } else {
        sndPlay(SND_COUNTDOWNTOSTART, 160);
      }
    }



  } else if(gameState==GAMESTATEINIT)
  {
    initCursor(&cur);

    if(!loadField(&pf, player()->levelFile ))
    {
      printf("Error: Couldn't init board.\n");
      gameState=GAMESTATECLEANUP;
      return(STATEPLAY);
    }

    if(!initDraw(pf.bgFile, pf.tileFile))
    {
      printf("Error: Couldn't init graphics.\n");
      gameState=GAMESTATECLEANUP;
      return(STATEPLAY);
    }
    pf.timeLeft *= 1000; //Convert seconds to ms
    countdown=500;
    countdownSeconds=3;
    gameState=GAMESTATECOUNTDOWN;
  } else if(gameState==GAMESTATECLEANUP)
  {
    //Add score to main score
    player()->gameScore += player()->boardScore;

    //Save player score (if best)
    savePlayer();

    resetBtn(C_UP);
    resetBtn(C_DOWN);
    resetBtn(C_LEFT);
    resetBtn(C_RIGHT);
    resetBtn(C_BTNX);
    resetBtn(C_BTNB);
    cleanUpDraw();
    freeField(&pf);
    gameState=GAMESTATEINIT;
    return(STATEMENU);
  } else if(gameState==GAMESTATEOUTOFTIME) //Menu was last in "Entering level" so it will return to that if timeout
  {

    draw(&cur,&pf, screen);
    drawUi(screen);

    countdown-=getTicks();


    if(countdown < 2000)
    {
      sprintf(buf, "Out Of Time!");
    } else if(countdown < 3000)
    {
      sprintf(buf, "Out Of");
    } else
    {
      sprintf(buf, "Out");
    }

    txtWriteCenter(screen, FONTMEDIUM, buf, 160,120-24);

    if(countdown < 1000)
    {
      //Wait for anykey
      if(getButton(C_BTNX) || countdown < -3000)
      {
        resetBtn(C_BTNX);
        //Subtract lives
        player()->lives--;
        if(player()->lives==0)
        {
          player()->gameOver=1;
        } else {
          player()->finishedLevel=0;
        }
        //Goto menu
        gameState=GAMESTATECLEANUP;
      }
    }

  }
  return(STATEPLAY);
}
