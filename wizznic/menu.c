#include "menu.h"
#include "sound.h"
#include "ticks.h"
#include "input.h"

#include "states.h"
#include "game.h"
#include "levelselector.h"

static float rot=0;
static float rot2=0;
static float rot3=0;
static float rot4=0;



#define MENUGFXINTRO 0
#define MENUGFXNUM 1

static SDL_Surface* menuBg[MENUGFXNUM];


static int menuState=menuStateIntro;

static int selectedMenuItem=0;
static int dir=0;
static int countdown=0;
static int selMax=3;

static int undocumented=0;


int initMenu()
{

  menuBg[MENUGFXINTRO] = loadImg( "data/menu/intro.png" );

  return(1);
}


void setMenu(int mstate)
{
  selectedMenuItem=0;
  menuState=mstate;
  dir=0;
  countdown=0;
}

int runMenu(SDL_Surface* screen)
{
  char buf[64];

  if(!dir)
  {
    countdown+=getTicks();
    if(countdown > 250)
      dir=1;
  } else {
    countdown-=getTicks();
    if(countdown < 1)
      dir=0;
  }

  if(getButton(C_BTNX))
  {
    sndPlayOnce(SND_CLICK, 160);
  }

  if(getButton(C_UP) || getButton(C_LEFT) )
  {
    resetBtn(C_UP);
    resetBtn(C_LEFT);
    sndPlay(SND_MENUMOVE, 160);
    countdown=0;
    dir=0;
    selectedMenuItem--;
    if(selectedMenuItem < 0)
      selectedMenuItem=selMax;
  }
  if(getButton(C_DOWN) || getButton(C_RIGHT) )
  {
    resetBtn(C_DOWN);
    resetBtn(C_RIGHT);
    sndPlay(SND_MENUMOVE, 160);
    countdown=0;
    dir=0;
    selectedMenuItem++;
    if(selectedMenuItem > selMax)
      selectedMenuItem=0;
  }

  //Gameover
  if(player()->gameOver && menuState!=menuStateGameOver)
  {
    if(menuState==menuStateUserLevels)
    {
      initPlayer();
      selectedMenuItem=0;
    } else {
      setMenu(menuStateGameOver);
    }
  }

  //Finished Level
  if(player()->finishedLevel && menuState!=menuStateFinishedLevel && menuState!=menuStateUserLevels)
  {
    player()->finishedLevel=0;
    setMenu(menuStateFinishedLevel);
  }

  //Paused
  if(player()->paused && menuState!=menuStatePaused && menuState!=menuStateRestart && !player()->gameOver && menuState!=menuStateOutro)
  {
    setMenu(menuStatePaused);
    selectedMenuItem=2;
  }

  switch(menuState)
  {
    case menuStateIntro:
      //Show background image
      starField(screen,1);
      waveImg(screen, menuBg[MENUGFXINTRO], 11,40);
     // SDL_BlitSurface(menuBg[MENUGFXINTRO] , NULL, screen, NULL );

      //Show "Best scores!"
      if(player()->bestScore > 500)
      {
        txtWriteCenter(screen, FONTSMALL, "Best Score:", 160, 130);

        //Show the highest score
        sprintf(buf, "%i", player()->bestScore);
        txtWave(screen, FONTMEDIUM, buf, 160, 150, &rot);
      }

      //Blink "Press X"
      if(dir) txtWriteCenter(screen, FONTSMALL, "Press X", 160, 190);

      //Show version
      txtWrite(screen, FONTSMALL, "v 0.5creators_edition", 10,220);

      //Wait for keypress
      if( getButton( C_BTNX ) )
      {
        resetBtn( C_BTNX );
        menuState=menuStateNewGame;
        SDL_FreeSurface(menuBg[MENUGFXINTRO]);
        menuBg[MENUGFXINTRO]=loadImg("data/menu/bye.png");
        selectedMenuItem=player()->bestLevel;
      }
    break; //Intro screen

    case menuStateNewGame: //Start new game (select starting level)
      starField(screen,1);

      selMax=player()->bestLevel+1;

      if(selectedMenuItem == selMax)
      {
        if(selectedMenuItem - player()->bestLevel > 1) selectedMenuItem--;
        levelSelector(screen,selectedMenuItem, 0);
        resetBtn(C_BTNX);

      } else {
        levelSelector(screen,selectedMenuItem, 1);
        txtWriteCenter(screen, FONTSMALL, "Press X to play", 160,240-12 );

        if(getButton(C_BTNX) && selectedMenuItem!=getNumLevels())
        {
          resetBtn(C_BTNX);

          initPlayer(); //New game = score = 0, lives=3
          player()->levelFile = levelInfo( selectedMenuItem )->file;
          player()->level = selectedMenuItem;
          menuState=menuStateNextLevel;
          // Show help if it's the first level
          if(selectedMenuItem == 0)
          {
            menuState=menuStateHowto;
          }
        }
      }

      if(selectedMenuItem-1 < player()->bestLevel && selectedMenuItem!=getNumLevels())
        txtWrite(screen, FONTMEDIUM, ">>", 320-40,120-12);

      if(selectedMenuItem > 0)
        txtWrite(screen, FONTMEDIUM, "<<", 5, 120-12);

      txtWriteCenter(screen, FONTMEDIUM, "New Game!", 160, 20);
    break; // New game

    case menuStateNextLevel:
      starField(screen,1);
      sprintf(buf, "Entering Level %i", player()->level);
      txtWave(screen, FONTMEDIUM,buf, 160, 35, &rot);

      sprintf(buf, "Time: %i:%01.2i", levelInfo( player()->level )->time/60, levelInfo( player()->level )->time%60 );
      txtWriteCenter(screen, FONTSMALL, buf, 160, 80);

      sprintf(buf, "Lives Left: %i", player()->lives);
      txtWriteCenter(screen, FONTSMALL, buf, 160, 100);

      sprintf(buf, "Score: %i",  player()->gameScore);
      txtWriteCenter(screen, FONTSMALL, buf, 160, 120);

      if(dir) txtWriteCenter(screen, FONTSMALL, "Press X", 160, 180);

      if(getButton(C_BTNX))
      {
        resetBtn(C_BTNX);
        return(STATEPLAY);
      }
    break;

    case menuStateFinishedLevel:
      //Check if the player compleated all levels
      if(player()->level+1 == getNumLevels())
      {
        //Go to "You beat the game"
        setMenu(menuStateBeatGame);
      }

      SDL_FillRect(screen, NULL, 0x00);
      fireWorks(screen);
      sprintf(buf, "Finished Level %i", player()->level);
      txtWave(screen, FONTMEDIUM,buf, 160, 35, &rot);

      sprintf(buf, "Lives Left: %i", player()->lives);
      txtWriteCenter(screen, FONTSMALL, buf, 160, 100);

      sprintf(buf, "Earned: %i",  player()->boardScore);
      txtWriteCenter(screen, FONTSMALL, buf, 160, 120);

      sprintf(buf, "Score: %i",  player()->gameScore);
      txtWriteCenter(screen, FONTSMALL, buf, 160, 140);


      if(dir) txtWriteCenter(screen, FONTSMALL, "Press X", 160, 180);
      if(getButton(C_BTNX))
      {
        resetBtn(C_BTNX);

        //Reset board score
        player()->boardScore=0;

        //Inc to next lvl
        player()->level++;

        //Set new level
        player()->levelFile = levelInfo( player()->level )->file;

        //Entering screen
        menuState=menuStateNextLevel;
        return(STATEMENU);
      }

    break;

    case menuStatePaused:
      selMax = 6;
      starField(screen,1);
      txtWave(screen, FONTMEDIUM, "Pause!", 160, 35, &rot);

      if(dir || selectedMenuItem!= 0) txtWriteCenter(screen, FONTSMALL, "New Game", 160, 80);
      if(dir || selectedMenuItem!= 1) txtWriteCenter(screen, FONTSMALL, "Restart", 160, 100);
      if(dir || selectedMenuItem!= 2) txtWriteCenter(screen, FONTSMALL, "Resume", 160, 120);
      if(dir || selectedMenuItem!= 3) txtWriteCenter(screen, FONTSMALL, "Help", 160, 140);
      if(dir || selectedMenuItem!= 4) txtWriteCenter(screen, FONTSMALL, "User Levels", 160, 160);
      if(dir || selectedMenuItem!= 5) txtWriteCenter(screen, FONTSMALL, "About", 160, 180);
      if(dir || selectedMenuItem!= 6) txtWriteCenter(screen, FONTSMALL, "Exit Program", 160, 200);

      sprintf(buf, "Lives: %i Restarts: %i",player()->lives, player()->retries);
      txtWave(screen, FONTSMALL, buf, 160, 220, &rot2);

      if( getButton( C_BTNX ) )
      {
        resetBtn( C_BTNX );
        switch(selectedMenuItem)
        {
          case 0: //Newgame: Return to game with paused set, it will cleanup, set gameover.
            //Cleanup will save scores
            player()->gameOver=1;
            return(STATEPLAY);
          break;
          case 1: //restart current level
            player()->paused=1; //This makes the gamecode reset
            player()->boardScore=0; //He won't earn any points
            setMenu(menuStateRestart);
            return(STATEPLAY);
          break;
          case 2: //Resume, unset paused, return to game
            player()->paused=0;
            return(STATEPLAY);
          break;
          case 3: //Switch to help screen
            player()->paused=0;
            menuState=menuStateHowto;
          break;
          case 4: //UserLevels
            player()->gameOver=1;
            menuState=menuStateUserLevels;
            return(STATEPLAY);
          break;
          case 5: //Switch to about screen
            player()->paused=0;
            menuState=menuStateAbout;
          break;
          case 6: //Save scores, Exit program without cleaning up (OS job :P)
            player()->gameScore += player()->boardScore;
            savePlayer();
            setMenu(menuStateOutro);
          break;
        }
      }
      break;

      case menuStateHowto:
        SDL_FillRect(screen, 0,0);

        txtWriteCenter(screen, FONTMEDIUM,"Instructions", 160, 5);
        txtWrite(screen, FONTSMALL,
                         "Objective: Destroy all bricks in\n"
                         " the level. This is done by moving\n"
                         " bricks of the same kind together.\n"
                         "\n"
                         "Controls:\n"
                         " Start - Pause and show pausemenu.\n"
                         " Up/Down/Left/Right - Move cursor\n"
                         " B - Lock cursor to brick.\n"
                       //" Vol+/- -Adjust volume.\n"
                         "\n"
                         "To move a brick:\n"
                         " Move the cursor over it and\n"
                         " hold down B, then move left or\n"
                         " right to push it that direction.\n"
                         "\n"
                         "To quit the game, press start.\n"
                         , 5, 35);


        if(dir) txtWriteCenter(screen, FONTSMALL, "Press X play.", 160, 240-12);

        if( getButton( C_BTNX ) )
        {
          resetBtn( C_BTNX );
          menuState=menuStatePaused;
          player()->paused=0;
          return(STATEPLAY);
        }
      break;

      case menuStateAbout:
        starField(screen, 1);
        fireWorks(screen);

        if(getButton(C_BTNA) && (undocumented==0 || undocumented==3) )
        {
          resetBtn(C_BTNA);
          undocumented++;
        } else if(getButton(C_BTNB) && (undocumented==1 || undocumented==2) )
        {
          resetBtn(C_BTNB);
          undocumented++;
        } else if(getButton(C_BTNY) && (undocumented>3))
        {
          resetBtn(C_BTNY);
          undocumented++;
        }
        if(undocumented==10)
        {
          sndPlay(SND_SCORECOUNT,160);
          undocumented=0;
          player()->bestLevel=getNumLevels();
          player()->bestScore=0;
          player()->gameScore=0;
          player()->boardScore=0;
        }

        txtWriteCenter(screen, FONTMEDIUM,"About Wizznic!", 160, 15);

        txtWrite(screen, FONTSMALL,
                         "Wizznic is an arcade game based on\n"
                         "the Taito classic \"Puzznic\" (1989)\n"
                         "\n"
                         "Wizznic was written in C with SDL.\n"
                         "Sfx: See data/media-licenses.txt\n"
                         "Gfx/Code: Jimmy Christensen\n"
                         "It is Free OpenSource Software\n"
                         "licensed under the GPLv3.\n\n"
                         "If you like this game, please\n"
                         "show your appreciation\n"
                         "by creating levels and/or\n"
                         "sound-effects or gfx themes!\n"
                         ".... or donate something :P"
                         , 5, 40);
       txtWave(screen, FONTSMALL, "http://wizznic.sf.net/", 160, 240-24,&rot);


        if( getButton( C_BTNX ) )
        {
          resetBtn( C_BTNX );
          menuState=menuStatePaused;
        }

      break;

      case menuStateGameOver:
        starField(screen,0);
        txtWriteCenter(screen, FONTMEDIUM,"Game Over", 160, 35);
        sprintf(buf, "Score: %i", player()->gameScore);
        txtWriteCenter(screen, FONTSMALL, buf, 160, 120-12);
        if(dir) txtWriteCenter(screen, FONTSMALL, "Press X", 160, 180);
        if( getButton( C_BTNX ) )
        {
          initPlayer();
          menuState=menuStateNewGame;
          resetBtn( C_BTNX );
        }
      break;

      case menuStateRestart:
        player()->retries -=1;
        if(player()->retries==0)
        {
          player()->lives -=1;
          player()->retries=3;
          if(player()->lives==0)
          {
            player()->gameOver=1;
            player()->paused=1;
            return(STATEPLAY);
          }
        }
        player()->paused=0;
        setMenu(menuStatePaused);
        selectedMenuItem=2;
        return(STATEPLAY);
      break;

      case menuStateBeatGame:
        starField(screen, 1);
        fireWorks(screen);

        txtWave(screen, FONTMEDIUM, "You beat the Game!", 160, 15, &rot);
        sprintf(buf, "%i Points", player()->gameScore);
        txtWrite(screen, FONTMEDIUM, buf, 5, 40);
        txtWrite(screen, FONTSMALL,
                         "Whoa! How awesome are you?\n"
                         "Well... I KNOW how awesome!!\n"
                         "Fairly awesome! :D You beat all\n"
                         "the levels so.. I guess there's\n"
                         "nothing more for you here... Maybe\n"
                         "you should go outside and enjoy\n"
                         "the nice weather, and the nature!\n"
                         "I hope you had a good time playing\n"
                         "my game.. I know I had a good\n"
                         "time making it..\n"
                         "If you want to show me that you\n"
                         "liked it, donate $1 to me!!! ;)\n\n"
                         "                 - Quoth the Raven", 5, 70);

        if(getButton(C_BTNX))
        {
          resetBtn(C_BTNX);

          //Reset board score
          player()->boardScore=0;

          //Inc to next lvl
          player()->level=0;

          //Set new level
          player()->levelFile = levelInfo( player()->level )->file;

          //Entering screen
          menuState=menuStateNextLevel;
          return(STATEMENU);
        }
      break;

      case menuStateOutro:

        //Show background image
        SDL_BlitSurface(menuBg[MENUGFXINTRO] , NULL, screen, NULL );
        //Blink "Press X"
        if(dir) txtWriteCenter(screen, FONTSMALL, "Press X", 160, 180);

        if(getButton(C_BTNX))
        {
          resetBtn(C_BTNX);
          return(STATEQUIT);
        }
      break;

      case menuStateUserLevels:
        starField(screen, 1);
        fireWorks(screen);
        txtWave(screen, FONTMEDIUM, "User Levels!", 160, 15, &rot);
        selMax=getNumUserLevels()+1;

        //Show the first level (which is special because it will start editor)
        if(dir || selectedMenuItem!= 0) txtWriteCenter(screen, FONTSMALL, "Create (X)",160,50);
        if(dir || selectedMenuItem!= 1) txtWriteCenter(screen, FONTSMALL, "Exit (X)",160,60);

        //List levels
        int ul=0;
        while(ul < getNumUserLevels())
        {
          sprintf(buf, "UserLevel %i (X=edit) (Y=play)", ul);
          if(dir || selectedMenuItem!= ul+2) txtWriteCenter(screen, FONTSMALL, buf, 160, 70+(10*ul));
          ul++;
        }

        //Edit levels/select
        if(getButton(C_BTNX))
        {
          resetBtn(C_BTNX);

          if(selectedMenuItem==0)
          {
            //Load empty, set name to something diffrent
            editorLoad("data/levels/empty.wzp");

            sprintf(buf, "data/userlevels/userlevel%i.wzp", getNumUserLevels());
            printf("Starting editor with new level %s\n", buf);
            editorFileName(buf);

            return(STATEEDIT);
          } else if(selectedMenuItem==1)
          {
            menuState=menuStateNewGame;
          } else {
            editorLoad(userLevelFile(selectedMenuItem-2));
            return(STATEEDIT);
          }
        }

        if(getButton(C_BTNY))
        {
          resetBtn(C_BTNY);
          if(selectedMenuItem > 1)
          {
            player()->levelFile = userLevelFile(selectedMenuItem-2);
            player()->level = 0;
            initPlayer(); //New game = score = 0, lives=3
            return(STATEPLAY);
          }
        }

      break;

  }
  return(STATEMENU);
}
