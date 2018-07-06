#include "score.h"

extern HSC_LIST hsc_table[];
extern SDL_Surface *screen;
extern SPRITE *player;


void score_display()
{
	PLAYER_DATA *p=(PLAYER_DATA *)player->data;
	char buffer[100];

	sprintf(buffer,"SCORE : %06d   HI-SCORE: %06d",p->score,
			p->score>=hsc_table[0].score ? p->score : hsc_table[0].score);
	font_print(buffer,FONT07,0,0);

	sprintf(buffer,"SHIPS : %d",p->lives);
	font_print(buffer,FONT07,0,10);

	sprintf(buffer,"SPEED : %d",p->player_speed);
	font_print(buffer,FONT07,0,20);

	sprintf(buffer,"STAGE : %d",p->level);
	font_print(buffer,FONT07,0,30);

	sprintf(buffer,"WEAPON: ");
	switch(p->weapon) {
	case WP_PLASMA:
		strcat(buffer,"PLASMA");
		break;
	case WP_DOUBLEPLASMA:
		strcat(buffer,"DOUBLE-PLASMA");
		break;
	case WP_QUADPLASMA:
		strcat(buffer,"QUAD-PLASMA");
		break;
	case WP_FIREBALL:
		strcat(buffer,"FIRERAY");
		break;
	case WP_DOUBLEFIREBALL:
		strcat(buffer,"DOUBLE-FIRERAY");
		break;
	case WP_QUADFIREBALL:
		strcat(buffer,"QUAD-FIRERAY");
		break;
	case WP_KILLRAY:
		strcat(buffer,"KILLRAY");
		break;
	default:
		strcat(buffer,"UNKNOWN ???");
		break;
	}
	font_print(buffer,FONT07,0,40);
	
	if(p->extra!=PLX_NONE) {
		sprintf(buffer,"EXTRA : ");
		switch(p->extra) {
		case PLX_HOMING:
			strcat(buffer,"HOMING MISSILE");
			break;
		case PLX_SHIELD:
			strcat(buffer,"SHIELD");
			break;
		case PLX_HLASER:
			strcat(buffer,"HOMING LASER");
			break;
		default:
			strcat(buffer,"UNKNOWN ???");
			break;
		}
		font_print(buffer,FONT07,0,50);
		sprintf(buffer,"X-TIME: %d",(int)p->extra_time/10);
		font_print(buffer,FONT07,0,60);
	}

}

void score_cleanup()
{
}
