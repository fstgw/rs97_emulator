#include "main.h"

extern SDL_Surface *screen;
extern int keyboard[];

GAMESTATE state;
GAMESTATE laststate;

int score;
int lives;
int volume=2; /* 0-3 */
int difficulty=DIFF_EASY;
extern SDL_Surface *ScreenSurface;
int main(int argc, char *argv[])
{

	game_init(argc, argv);
	while (state.mainstate!=ST_GAME_QUIT) {
		keyboard_poll();

		switch(state.mainstate) {
			case ST_START_INTRO:
				if(state.newstate) {
					startintro_init();
					state.newstate=0;
				}
				startintro_work();
				break;
			case ST_INTRO:
				if(state.newstate) {
					intro_init();
					state.newstate=0;
				}
				intro_work();
				break;
			case ST_GAME_PLAY:
				if(state.newstate) {
					thegame_init();
					state.newstate=0;
				}
				thegame_work();
				break;
			case ST_GAME_OVER:
				if(state.newstate) {
					gameover_init();
					state.newstate=0;
				}
				gameover_work();
				break;
			case ST_MENU:
				if(state.newstate) {
					menu_init();
					state.newstate=0;
				}
				menu_work();
				break;
			case ST_SHOW_HCLIST:
				if(state.newstate) {
					hsc_show_init();
					state.newstate=0;
				}
				hsc_show_work();
				break;
			case ST_ENTRY_HCLIST:
				if(state.newstate) {
					hsc_entry_init();
					state.newstate=0;
				}
				hsc_entry_work();
				break;
		}
		
		fps_show();
		//SDL_Flip(screen);
    {
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_LockSurface(ScreenSurface);
      int x, y;
      uint32_t *s = (uint32_t*)screen->pixels;
      uint32_t *d = (uint32_t*)ScreenSurface->pixels;
      for(y=0; y<240; y++){
        for(x=0; x<160; x++){
          *d++ = *s++;
        }
        d+= 160;
      }
      if(SDL_MUSTLOCK(ScreenSurface)) SDL_UnlockSurface(ScreenSurface);
      SDL_Flip(ScreenSurface);
    }
		fps_newframe();
	}

	/* TODO: Free everything (memory, SDL_Surfaces, Joysticks...) */

	fprintf(stdout,"Thank you for playing\n");
	exit(0);
}
