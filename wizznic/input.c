#include "input.h"
#include "ticks.h"
#include <SDL/SDL.h>


#include "wiz.h"
#include "player.h"


static struct {
  int button;
  int state;
  int time;
} button[C_NUM];

int getButton(int btn)
{
  return(button[btn].state);
}

void resetBtnTimer(int btn)
{
  button[btn].time=0;
}

void resetBtn(int btn)
{
  button[btn].time=0;
  button[btn].state=0;
}

int getBtnTime(int btn)
{
  return(button[btn].time);
}

void runControls()
{
  SDL_Event event;
  int i;

  //Loop through buttons to update hold-down time
  for(i=0; i < C_NUM; i++)
  {
    if( button[i].state )
    {
      button[i].time += getTicks();
    }
  }

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {

        case SDL_JOYBUTTONDOWN:
          for(i=0; i < C_NUM; i++)
          {
            if( event.jbutton.button == button[i].button )
            {
              button[i].state=1;
              button[i].time=0;
            }
          }
          switch( event.jbutton.button )
          {
            case GP2X_BUTTON_UPLEFT:
              button[C_UP].state=1;
              button[C_UP].time=0;
              button[C_LEFT].state=1;
              button[C_LEFT].time=0;
            break;
            case GP2X_BUTTON_UPRIGHT:
              button[C_UP].state=1;
              button[C_UP].time=0;
              button[C_RIGHT].state=1;
              button[C_RIGHT].time=0;
            break;
            case GP2X_BUTTON_DOWNLEFT:
              button[C_DOWN].state=1;
              button[C_DOWN].time=0;
              button[C_LEFT].state=1;
              button[C_LEFT].time=0;
            break;
            case GP2X_BUTTON_DOWNRIGHT:
              button[C_DOWN].state=1;
              button[C_DOWN].time=0;
              button[C_RIGHT].state=1;
              button[C_RIGHT].time=0;
            break;
            #ifdef GP2X
            case GP2X_BUTTON_VOLDOWN:
              WIZ_AdjustVolume( VOLUME_DOWN );
              savePlayer();
            break;
            case GP2X_BUTTON_VOLUP:
              WIZ_AdjustVolume( VOLUME_UP );
              savePlayer();
            break;
            #endif

          }
        break;
        case SDL_JOYBUTTONUP:
          for(i=0; i < C_NUM; i++)
          {
            if( event.jbutton.button == button[i].button )
            {
              button[i].state=0;
              button[i].time=0;
            }
          }
          switch( event.jbutton.button )
          {
            case GP2X_BUTTON_UPLEFT:
              button[C_UP].state=0;
              button[C_UP].time=0;
              button[C_LEFT].state=0;
              button[C_LEFT].time=0;
            break;
            case GP2X_BUTTON_UPRIGHT:
              button[C_UP].state=0;
              button[C_UP].time=0;
              button[C_RIGHT].state=0;
              button[C_RIGHT].time=0;
            break;
            case GP2X_BUTTON_DOWNLEFT:
              button[C_DOWN].state=0;
              button[C_DOWN].time=0;
              button[C_LEFT].state=0;
              button[C_LEFT].time=0;
            break;
            case GP2X_BUTTON_DOWNRIGHT:
              button[C_DOWN].state=0;
              button[C_DOWN].time=0;
              button[C_RIGHT].state=0;
              button[C_RIGHT].time=0;
            break;
          }
        break;
        //Keyboard
        case SDL_KEYDOWN:
					if(event.key.keysym.sym == 51){
						event.key.keysym.sym = SDLK_RETURN;
					}
          for(i=0; i < C_NUM; i++)
          {
            if( event.key.keysym.sym == button[i].button )
            {
              button[i].state=1;
              button[i].time=0;
            }
          }
        break;
        case SDL_KEYUP:
					if(event.key.keysym.sym == 51){
						event.key.keysym.sym = SDLK_RETURN;
					}
          for(i=0; i < C_NUM; i++)
          {
            if( event.key.keysym.sym == button[i].button )
            {
              button[i].state=0;
              button[i].time=0;
            }
          }

        break;

    }
  }

}

void initControls()
{

/*  #ifdef GP2X
  button[C_UP].button = GP2X_BUTTON_UP;
  button[C_DOWN].button = GP2X_BUTTON_DOWN;
  button[C_LEFT].button =  GP2X_BUTTON_LEFT;
  button[C_RIGHT].button = GP2X_BUTTON_RIGHT;
  button[C_BTNY].button = GP2X_BUTTON_Y;
  button[C_BTNX].button = GP2X_BUTTON_X;
  button[C_BTNA].button = GP2X_BUTTON_A;
  button[C_BTNB].button = GP2X_BUTTON_B;
  button[C_SHOULDERA].button = GP2X_BUTTON_L; //Guess this is shoulder L
  button[C_SHOULDERB].button = GP2X_BUTTON_R;
  button[C_BTNMENU].button = GP2X_BUTTON_START;
  button[C_BTNSELECT].button = GP2X_BUTTON_SELECT;
  button[C_BTNVOLUP].button = GP2X_BUTTON_VOLUP;
  button[C_BTNCOLDOWN].button = GP2X_BUTTON_VOLDOWN;
  #else */
  button[C_UP].button = SDLK_UP;
  button[C_DOWN].button = SDLK_DOWN;
  button[C_LEFT].button = SDLK_LEFT;
  button[C_RIGHT].button = SDLK_RIGHT;
  button[C_BTNY].button = SDLK_LSHIFT;
  button[C_BTNX].button = SDLK_SPACE;
  button[C_BTNA].button = SDLK_LCTRL;
  button[C_BTNB].button = SDLK_LALT;
  button[C_SHOULDERA].button = SDLK_TAB;
  button[C_SHOULDERB].button = SDLK_BACKSPACE;
  button[C_BTNMENU].button = SDLK_RETURN;
  button[C_BTNSELECT].button = SDLK_ESCAPE;
  button[C_BTNVOLUP].button = SDLK_1;
  button[C_BTNCOLDOWN].button = SDLK_2;
//  #endif
}
