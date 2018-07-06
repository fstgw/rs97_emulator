#include "support.h"

SDL_Surface *screen;
SDL_Surface *ScreenSurface;
int keyboard[SDLK_LAST];
int debug=0;
int use_joystick=0;
IMGLIST *img_list=NULL;
KEYCONFIG keyconfig;
Uint32 videoflags=SDL_SWSURFACE;
int depth=16;

extern GAMESTATE state;
extern GAMESTATE laststate;

void game_init(int argc, char *argv[])
{
	Uint32 initflags=0;
	int i;
	SDL_Joystick *joy;

	for(i=2;i<=argc;i++) {
		if(!strncmp(argv[i-1],"-d",2)) {
			debug=1;
			error(ERR_DEBUG,"debug-mode enabled");
		} else if(!strncmp(argv[i-1],"-f",2)) {
			/* videoflags|=SDL_FULLSCREEN;
			 * SDL_FULLSCREEN doesn't work well with SDL_DOUBLEBUF in DGA mode,
			 * so I set them ex-or */
			videoflags=SDL_FULLSCREEN;
		} else if(!strncmp(argv[i-1],"-j",2)) {
			use_joystick=1;
		} else if(!strncmp(argv[i-1],"-16",3)) {
			depth=16;
		} else if(!strncmp(argv[i-1],"-24",3)) {
			depth=24;
		} else if(!strncmp(argv[i-1],"-32",3)) {
			depth=32;
		} else if(!strncmp(argv[i-1],"-h",2)) {
			error(ERR_INFO,"%s:  a shoot-em-all game",argv[0]);
			error(ERR_INFO,"-h:  get this help");
			error(ERR_INFO,"-f:  fullscreen mode");
			error(ERR_INFO,"-j:  enable joystick-support (preliminary)");
			error(ERR_INFO,"-d:  enable debug messages");
			error(ERR_INFO,"-16: force 16 bit screen (default)");
			error(ERR_INFO,"-24: force 24 bit screen");
			error(ERR_INFO,"-32: force 32 bit screen");
			exit(0);
		} else {
			error(ERR_WARN,"unknown command line option: %s (try -h to get help)",argv[i-1]);
		}
	}

	fprintf(stdout,"FYI: very early prepreprealpha, debug-mode forced\n"); debug=1;

	initflags=SDL_INIT_VIDEO;
	if(use_joystick)
		initflags|=SDL_INIT_JOYSTICK;


	if(SDL_Init(initflags)<0) {
		CHECKPOINT;
		error(ERR_FATAL,"cant init SDL: %s",SDL_GetError());
	}

	if(atexit(SDL_Quit)) {
		CHECKPOINT;
		error(ERR_WARN,"atexit dont returns zero");
	}

  ScreenSurface = SDL_SetVideoMode(320, 480, 16, videoflags);
  screen = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH,HEIGHT,depth,0,0,0,0);
	//if((screen=SDL_SetVideoMode(WIDTH,HEIGHT,depth,videoflags))==NULL) {
		//CHECKPOINT;
		//error(ERR_FATAL,"cant open screen: %s",SDL_GetError());
	//}
	display_vidinfo(screen);
	/*
	if(depth==0) {
		error(ERR_DEBUG,"we want the current screen bit-depth...");
	} else {
		error(ERR_DEBUG,"we want a %d bpp screen...",depth);
	}
	error(ERR_DEBUG,"... and got a %d bpp surface",screen->format->BitsPerPixel);
	*/

	if(use_joystick) {
		if(debug) {
			error(ERR_DEBUG,"%i joysticks found",SDL_NumJoysticks());
			for(i=0;i<SDL_NumJoysticks();i++) {
				error(ERR_DEBUG,"stick %d: %s",i,SDL_JoystickName(i));
			}
		}
		if(SDL_NumJoysticks()>0) {
			joy=SDL_JoystickOpen(0);
			if(joy) {
				error(ERR_DEBUG,"Joystick 0:");
				error(ERR_DEBUG,"Name: %s",SDL_JoystickName(0));
				error(ERR_DEBUG,"Axes: %d",SDL_JoystickNumAxes(joy));
				error(ERR_DEBUG,"Buttons: %d",SDL_JoystickNumButtons(joy));
				error(ERR_DEBUG,"Balls: %d",SDL_JoystickNumBalls(joy));
			} else {
				error(ERR_WARN,"could not open joystick #0");
			}
		}
	}

	/* Tastenbelegung initialisieren */
	keyconfig.u=SDLK_UP;
	keyconfig.d=SDLK_DOWN;
	keyconfig.l=SDLK_LEFT;
	keyconfig.r=SDLK_RIGHT;
	keyconfig.f=SDLK_SPACE;
	keyconfig.e=SDLK_ESCAPE;

	/*
	error(ERR_DEBUG,"Key-configuration:");
	error(ERR_DEBUG,"up-key    : %s",SDL_GetKeyName(keyconfig.u));
	error(ERR_DEBUG,"down-key  : %s",SDL_GetKeyName(keyconfig.d));
	error(ERR_DEBUG,"left-key  : %s",SDL_GetKeyName(keyconfig.l));
	error(ERR_DEBUG,"right-key : %s",SDL_GetKeyName(keyconfig.r));
	error(ERR_DEBUG,"fire-key  : %s",SDL_GetKeyName(keyconfig.f));
	error(ERR_DEBUG,"escape-key: %s",SDL_GetKeyName(keyconfig.e));
	*/

	SDL_ShowCursor(0);
	SDL_WM_SetCaption("killeverythingthatmoves","ketm");

	keyboard_clear();
	preload_gfx();
	font_init();
	menusystem_init();
	hsc_init();
	fps_init();
	newstate(ST_START_INTRO,0,1);
}

//void toggle_fullscreen()
//{
	//SDL_Surface *tmp;

	//if(videoflags==SDL_DOUBLEBUF)
		//videoflags=SDL_FULLSCREEN;
	//else
		//videoflags=SDL_DOUBLEBUF;

	//tmp=SDL_ConvertSurface(screen,screen->format,screen->flags);
	//if(tmp==NULL) {
		//CHECKPOINT;
		//error(ERR_FATAL,"cant copy screen");
	//}
	//if((screen=SDL_SetVideoMode(WIDTH,HEIGHT,depth,videoflags))==NULL) {
		//CHECKPOINT;
		//error(ERR_FATAL,"cant open change fullscreen/window: %s",SDL_GetError());
	//}
	//SDL_BlitSurface(tmp,NULL,screen,NULL);
	//SDL_FreeSurface(tmp);
	//// display_vidinfo();
//}

void error(int errorlevel, char *msg, ...)
{
	char msgbuf[512];
	va_list argptr;

	va_start(argptr, msg);
	vsprintf(msgbuf, msg, argptr);
	va_end(argptr);

	switch(errorlevel) {
		case ERR_DEBUG: if(debug) { fprintf(stdout,"DEBUG: %s\n",msgbuf); } break;
		case ERR_INFO: fprintf(stdout,"INFO: %s\n",msgbuf); break;
		case ERR_WARN: fprintf(stdout,"WARNING: %s\n",msgbuf); break;
		case ERR_FATAL: fprintf(stdout,"FATAL: %s\n",msgbuf); break;
	}

	if(errorlevel==ERR_FATAL) exit(1);
}


SDL_Surface *loadbmp(char *filename)
{
	SDL_Surface *s1,*s2;

	if((s1=imglist_search(filename))!=NULL) {
		return s1;
	}

	if((s1=SDL_LoadBMP(filename))==NULL) {
		CHECKPOINT;
		error(ERR_FATAL,"cant load image %s: %s",filename,SDL_GetError());
	}
	if((s2=SDL_DisplayFormat(s1))==NULL) {
		CHECKPOINT;
		error(ERR_FATAL,"cant convert image %s to display format: %s",filename,SDL_GetError());
	}
	SDL_FreeSurface(s1);
	s1=NULL;
	imglist_add(s2,filename);
	return(s2);
}

void unloadbmp_by_surface(SDL_Surface *s)
{
	IMGLIST *i=img_list;

	while(i!=NULL) {
		if(s==i->img) {
			if(!i->refcount) {
				CHECKPOINT;
				error(ERR_WARN,"unloadbmp_by_surface: refcount for object %s is already zero",i->name);
			} else {
				i->refcount--;
			}
			return;
		}
		i=i->next;
	}
	CHECKPOINT;
	error(ERR_WARN,"unloadbmp_by_surface: object not found");
}

void unloadbmp_by_name(char *name)
{
	IMGLIST *i=img_list;

	while(i!=NULL) {
		if(!strcmp(i->name,name)) {
			if(!i->refcount) {
				CHECKPOINT;
				error(ERR_WARN,"unloadbmp_by_name: refcount for object %s is already zero",i->name);
			} else {
				i->refcount--;
			}
			return;
		}
		i=i->next;
	}
	CHECKPOINT;
	error(ERR_WARN,"unloadbmp_by_name: object not found");
}

void imglist_add(SDL_Surface *s, char *name)
{
	IMGLIST *new;

	new=mmalloc(sizeof(IMGLIST));
	strcpy(new->name,name);
	new->refcount=1;
	new->img=s;

	if(img_list==NULL) {
		img_list=new;
		new->next=NULL;
	} else {
		new->next=img_list;
		img_list=new;
	}
}

SDL_Surface *imglist_search(char *name)
{
	IMGLIST *i=img_list;

	while(i!=NULL) {
		if(!strcmp(name,i->name)) {
			i->refcount++;
			return (i->img);
		}
		i=i->next;
	}
	return(NULL);
}

void imglist_garbagecollect()
{
	IMGLIST *s=img_list,*p=NULL,*n=NULL;

	while(s!=NULL) {
		n=s->next;

		if(s->refcount==0) {
			if(p==NULL) {
				img_list=n;
			} else {
				p->next=n;
			}
			SDL_FreeSurface(s->img);
			free(s);
		} else {
			p=s;
		}
		s=n;
	}
}

/* dont forget to lock surface when using get/putpixel! */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp=surface->format->BytesPerPixel;
	Uint8 *p=(Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

	if(x>=clip_xmin(surface) && x<=clip_xmax(surface) && y>=clip_ymin(surface) && y<=clip_ymax(surface)){
		switch(bpp) {
			case 1:
				return *p;
			case 2:
				return *(Uint16 *)p;
			case 3:
				if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
					return p[0]<<16|p[1]<<8|p[2];
				else
					return p[0]|p[1]<<8|p[2]<<16;
			case 4:
				return *(Uint32 *)p;
			default:
				return 0;
		}
	} else return 0;
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp=surface->format->BytesPerPixel;
	Uint8 *p=(Uint8 *)surface->pixels+y*surface->pitch+x*bpp;
	if(x>=clip_xmin(surface) && x<=clip_xmax(surface) && y>=clip_ymin(surface) && y<=clip_ymax(surface)){
		switch(bpp) {
			case 1:
				*p=pixel;
				break;
			case 2:
				*(Uint16 *)p=pixel;
				break;
			case 3:
				if(SDL_BYTEORDER==SDL_BIG_ENDIAN) {
					p[0]=(pixel>>16)&0xff;
					p[1]=(pixel>>8)&0xff;
					p[2]=pixel&0xff;
				} else {
					p[2]=(pixel>>16)&0xff;
					p[1]=(pixel>>8)&0xff;
					p[0]=pixel&0xff;
				}
				break;
			case 4:
				*(Uint32 *)p=pixel;
		}
	}
}

void draw_line(SDL_Surface *s, int x1, int y1, int x2, int y2, Uint32 farbe1, Uint32 farbe2)
{
	int dx,dy,dxabs,dyabs,i,px,py,sdx,sdy,x,y;

	dx=x2-x1;
	dy=y2-y1;
	sdx=sign(dx);
	sdy=sign(dy);
	dxabs=abs(dx);
	dyabs=abs(dy);
	x=0;
	y=0;
	px=x1;
	py=y1;

	if(SDL_MUSTLOCK(s))
		SDL_LockSurface(s);

	if(dxabs>=dyabs) {
		for(i=0;i<dxabs;i++) {
			y+=dyabs;
			if(y>=dxabs) {
				y-=dxabs;
				py+=sdy;
			}
			putpixel(s,px,py-1,farbe2);
			putpixel(s,px,py,farbe1);
			putpixel(s,px,py+1,farbe2);
			px+=sdx;
		}
	} else {
		for(i=0;i<dyabs;i++) {
			x+=dxabs;
			if(x>=dyabs) {
				x-=dyabs;
				px+=sdx;
			}
			putpixel(s,px-1,py,farbe2);
			putpixel(s,px,py,farbe1);
			putpixel(s,px+1,py,farbe2);
			py+=sdy;
		}
	}
	if(SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}

void draw_line_simple(SDL_Surface *s, int x1, int y1, int x2, int y2, Uint32 farbe1)
{
	int dx,dy,dxabs,dyabs,i,px,py,sdx,sdy,x,y;

	dx=x2-x1;
	dy=y2-y1;
	sdx=sign(dx);
	sdy=sign(dy);
	dxabs=abs(dx);
	dyabs=abs(dy);
	x=0;
	y=0;
	px=x1;
	py=y1;

	if(SDL_MUSTLOCK(s))
		SDL_LockSurface(s);

	if(dxabs>=dyabs) {
		for(i=0;i<dxabs;i++) {
			y+=dyabs;
			if(y>=dxabs) {
				y-=dxabs;
				py+=sdy;
			}
			putpixel(s,px,py,farbe1);
			px+=sdx;
		}
	} else {
		for(i=0;i<dyabs;i++) {
			x+=dxabs;
			if(x>=dyabs) {
				x-=dyabs;
				px+=sdx;
			}
			putpixel(s,px,py,farbe1);
			py+=sdy;
		}
	}
	if(SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}

void blit_scaled(SDL_Surface *src, SDL_Rect *src_rct, SDL_Surface *dst, SDL_Rect *dst_rct)
{
	Sint32 x, y;
	Sint32 u, v;
	Uint32 col, key;

	key=src->format->colorkey;

	if(SDL_MUSTLOCK(src))
		SDL_LockSurface(src);
	if(SDL_MUSTLOCK(dst))
		SDL_LockSurface(dst);

	for(y = 0; y<dst_rct->h; y++) {
		for(x = 0; x<dst_rct->w; x++) {
			u = src_rct->w * x / dst_rct->w;
			v = src_rct->h * y / dst_rct->h;
			col=getpixel(src, u + src_rct->x, v + src_rct->y);
			if(col!=key)
				putpixel(dst, x + dst_rct->x, y + dst_rct->y, col);
		}
	}

	if(SDL_MUSTLOCK(src))
		SDL_UnlockSurface(src);
	if(SDL_MUSTLOCK(dst))
		SDL_UnlockSurface(dst);
}

/* just a quick hack - dont know if i will use it in the final game...
 * blits only every 2nd pixel, to archive a cheap 50%-alpha effect.
 */
void blit_calpha(SDL_Surface *src, SDL_Rect *src_rct, SDL_Surface *dst, SDL_Rect *dst_rct)
{
	Sint32 x, y;
	Uint32 col, key;

	Uint16 *ps,*pd;
	Uint16 *sps,*spd;

	if(src->format->BitsPerPixel!=dst->format->BitsPerPixel) {
		CHECKPOINT;
		error(ERR_FATAL,"cant handle different pixelformats (yet?)");
	}
	if(src->format->BitsPerPixel!=16) {
		CHECKPOINT;
		error(ERR_FATAL,"can only handle 16bit-pixelformat");
	}
	key=src->format->colorkey;

	if(SDL_MUSTLOCK(src))
		SDL_LockSurface(src);
	if(SDL_MUSTLOCK(dst))
		SDL_LockSurface(dst);

	ps=(Uint16 *)src->pixels+src_rct->y*src->pitch/2+src_rct->x;
	pd=(Uint16 *)dst->pixels+dst_rct->y*dst->pitch/2+dst_rct->x;

	for(y=0;y<src_rct->h;y++) {
		sps=ps;
		spd=pd;

		if(y%2) {
			ps++;
			pd++;
		}

		for(x=0;x<src_rct->w;x+=2) {

			if((x+dst_rct->x>=0) &&
			   (x+dst_rct->x<dst->w) &&
			   (y+dst_rct->y>=0) &&
			   (y+dst_rct->y<dst->h)) {

				col=*(ps);
				if(col!=key)
					*(pd)=col;
			}
			pd+=2;
			ps+=2;
		}
		ps=sps+src->pitch/2;
		pd=spd+dst->pitch/2;
	}

	if(SDL_MUSTLOCK(src))
		SDL_UnlockSurface(src);
	if(SDL_MUSTLOCK(dst))
		SDL_UnlockSurface(dst);
}

void keyboard_clear()
{
	int i;

	for(i=0;i<SDLK_LAST;i++) {
		keyboard[i]=0;
	}
}

void keyboard_poll()
{
	SDL_Event event;

	if(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				keyboard[event.key.keysym.sym]=1;
				break;
			case SDL_KEYUP:
				keyboard[event.key.keysym.sym]=0;
				break;

			if(use_joystick) {
				case SDL_JOYAXISMOTION:
					if(event.jaxis.axis==0) {
						if(event.jaxis.value <= -3200) {
							keyboard[keyconfig.l]=1;
						} else {
							keyboard[keyconfig.l]=0;
						}
						if(event.jaxis.value >= 3200) {
							keyboard[keyconfig.r]=1;
						} else {
							keyboard[keyconfig.r]=0;
						}
					}
					if(event.jaxis.axis==1) {
						if(event.jaxis.value <= -3200) {
							keyboard[keyconfig.u]=1;
						} else {
							keyboard[keyconfig.u]=0;
						}
						if(event.jaxis.value >= 3200) {
							keyboard[keyconfig.d]=1;
						} else {
							keyboard[keyconfig.d]=0;
						}
					}
					break;
					break;

				case SDL_JOYBUTTONDOWN:
					if(event.jbutton.button==0) {
						keyboard[keyconfig.f]=1;
					}
					break;

				case SDL_JOYBUTTONUP:
					if(event.jbutton.button==0) {
						keyboard[keyconfig.f]=0;
					}
					break;
			}

			case SDL_QUIT:
				newstate(ST_GAME_QUIT,0,1);
				break;
		}
	}
}

int keyboard_keypressed()
{
	int i;
	for(i=0;i<SDLK_LAST;i++) {
		if(keyboard[i]) return 1;
	}
	return 0;
}

void newstate(int m, int s, int n)
{
	laststate=state;
	if(m>=0) state.mainstate=m;
	if(s>=0) state.substate=s;
	if(n>=0) state.newstate=n;
}

void *mmalloc(size_t size)
{
	void *ptr;

	ptr=malloc(size);
	if(ptr==NULL) {
		error(ERR_WARN,"can't alloc %d bytes, trying garbage collection",size);
		imglist_garbagecollect();
		ptr=malloc(size);
		if(ptr==NULL) {
			error(ERR_FATAL,"I'm sorry, but you're out of memory!");
		}
	}

	return ptr;
}

void preload_gfx()
{
	SDL_Surface *tmp;

	tmp=loadbmp("data/12side.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/badblocks.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/bonus_f.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/bonus_p.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/bonus_s.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-lo.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-lu.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-mo.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-mu.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-ro.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss01-ru.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss02_v2.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/boss02_v2x.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/coin.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/crusher.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/cube.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/ex.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/eyefo.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/fireball.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/firebomb.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/font01.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/font02.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/font03.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/font04.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/font05.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/iris.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/ketm.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/killray-b.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/killray-r.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/kugel.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/moon.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/plasma.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/plate.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/plus1000.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/rotating_rocket.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/rwingx.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/ship-med.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/speed.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/weapon.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/wolke01.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/wolke02.bmp"); unloadbmp_by_surface(tmp);
	tmp=loadbmp("data/wolke03.bmp"); unloadbmp_by_surface(tmp);
	/* alle benoetigten Bilder in den Cache laden */
}










void display_vidinfo()
{
	const SDL_VideoInfo *s;
	char driver[256];
	SDL_Rect **modes;
	int i;

	error(ERR_DEBUG,"============ SDL VideoInfo ============");

	s=SDL_GetVideoInfo();

	if(SDL_VideoDriverName(driver,256)==NULL)
		error(ERR_WARN,"couldn't get video driver name");
	else
		error(ERR_DEBUG,"Video Driver: %s",driver);

	error(ERR_DEBUG,"BitsPerPixel: %d",s->vfmt->BitsPerPixel);
	if(s->vfmt->palette==NULL) {
		error(ERR_DEBUG,"R Mask      : 0x%.8x",s->vfmt->Rmask);
		error(ERR_DEBUG,"G Mask      : 0x%.8x",s->vfmt->Gmask);
		error(ERR_DEBUG,"B Mask      : 0x%.8x",s->vfmt->Bmask);
	}
	error(ERR_DEBUG,"HW Surface  : %savailable",s->hw_available ? "" : "not ");
	error(ERR_DEBUG,"Win-Manager : %savailable",s->wm_available ? "" : "not ");
	error(ERR_DEBUG,"H->H Blit   : %savailable",s->blit_hw ? "" : "not ");
	error(ERR_DEBUG,"H->H Blit CC: %savailable",s->blit_hw_CC ? "" : "not ");
	error(ERR_DEBUG,"H->H Blit A : %savailable",s->blit_hw_A ? "" : "not ");
	error(ERR_DEBUG,"S->H Blit   : %savailable",s->blit_sw ? "" : "not ");
	error(ERR_DEBUG,"S->H Blit CC: %savailable",s->blit_sw_CC ? "" : "not ");
	error(ERR_DEBUG,"S->H Blit A : %savailable",s->blit_sw_A ? "" : "not ");
	error(ERR_DEBUG,"Color Fill  : %savailable",s->blit_fill ? "" : "not ");
	error(ERR_DEBUG,"Video-Mem   : %d",s->video_mem);

	error(ERR_DEBUG,"Available Fullscreen modes:");
	modes=SDL_ListModes(NULL,SDL_FULLSCREEN);
	for(i=0;modes[i];i++) {
		error(ERR_DEBUG,"%d: %dx%d",i+1,modes[i]->w,modes[i]->h);
	}
	error(ERR_DEBUG,"Available HW-surfaces modes:");
	modes=SDL_ListModes(NULL,SDL_FULLSCREEN|SDL_HWSURFACE);
	for(i=0;modes[i];i++) {
		error(ERR_DEBUG,"%d: %dx%d",i+1,modes[i]->w,modes[i]->h);
	}
	error(ERR_DEBUG,"=======================================");
}

