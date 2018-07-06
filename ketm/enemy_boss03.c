#include "enemy.h"

extern SPRITE *player;
extern double fps_factor;
extern SDL_Surface *screen;

typedef struct _boss03_data {
	ENEMY_BASE b;
	int state;
	int wait1;
	int wait2;
	int level;
} BOSS03_DATA;

void enemy_boss03_add(int lv)
{
	BOSS03_DATA *b;
	SPRITE *s;

	s=sprite_add_file("data/galaxy.bmp",36,PR_ENEMY);
	s->flags|=(SP_FLAG_VISIBLE|SP_FLAG_COLCHECK);
	s->anim_speed=-2;
	s->aktframe=0;
	s->type=SP_EN_BOSS03;
	b=mmalloc(sizeof(BOSS03_DATA));
	s->data=b;
	b->b.health=20;
	b->b.score=500;
	b->state=0;
	b->wait1=50*fps_factor;
	b->wait2=0;
	b->level=lv;
	s->mover=enemy_boss03_move;
	s->x=(screen->w/2)-(s->w/2);
	s->y=100;

	((PLAYER_DATA *)player->data)->bossmode=1;
}

void enemy_boss03_move(SPRITE *s)
{
	// BOSS03_DATA *b=(BOSS03_DATA *)s->data;
		
}
