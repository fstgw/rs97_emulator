
#include "../nx.h"
#include "pause.fdh"

bool pause_init(int param)
{
	memset(lastinputs, 1, sizeof(lastinputs));
	return 0;
}

void pause_tick()
{
	ClearScreen(BLACK);
	
	int cx = (SCREEN_WIDTH / 2) - (sprites[SPR_RESETPROMPT].w / 2);
	int cy = (SCREEN_HEIGHT / 2) - (sprites[SPR_RESETPROMPT].h / 2);
	draw_sprite(cx, cy, SPR_RESETPROMPT);
	
	const char *str = "Y:Options";
	cx = (SCREEN_WIDTH / 2) - (GetFontWidth(str, 0) / 2) - 4;
	cy = (SCREEN_HEIGHT - 8) - GetFontHeight();
	int f3wd = font_draw(cx, cy, "Y", 0);
	font_draw(cx + f3wd, cy, ":Options", 0, &bluefont);
	
	// resume
	if (justpushed(JUMPKEY))
	{
		lastinputs[JUMPKEY] = true;
		game.pause(false);
		return;
	}
	
	// reset
	if (justpushed(FIREKEY))
	{
		lastinputs[FIREKEY] = true;
		game.reset();
		return;
	}
	
	// exit
	if (justpushed(ESCKEY))
	{
		lastinputs[ESCKEY] = true;
		game.running = false;
		return;
	}
}






