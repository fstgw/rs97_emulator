/***************************************************************************
                                          
 This is the SDL XMAME display driver.
 FIrst incarnation by Tadeusz Szczyrba <trevor@pik-nel.pl>,
 based on the Linux SVGALib adaptation by Phillip Ezolt.

 updated and patched by Ricardo Calixto Quesada (riq@core-sdi.com)

 patched by Patrice Mandin (pmandin@caramail.com)
  modified support for fullscreen modes using SDL and XFree 4
  added toggle fullscreen/windowed mode (Alt + Return)
  added title for the window
  hide mouse cursor in fullscreen mode
  added command line switch to start fullscreen or windowed
  modified the search for the best screen size (SDL modes are sorted by
    Y size)

 patched by Dan Scholnik (scholnik@ieee.org)
  added support for 32bpp XFree86 modes
  new update routines: 8->32bpp & 16->32bpp

 TODO: Test the 16bpp->24bpp update routine
       Test the 16bpp->32bpp update routine
       Improve performance.
       Test mouse buttons (which games use them?)

***************************************************************************/
#define __SDL_C

#undef SDL_DEBUG

#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <SDL.h>
#include "xmame.h"
#include "devices.h"
#include "keyboard.h"
#include "driver.h"
#include "SDL-keytable.h"
//#include "effect.h"

static int Display_pitch;   /* Added for IPU_SCALER support; used by IPU and Software scalers */
static int Display_BytesPerPixel;
static int Display_width;
static int Display_height;
static int Display_depth;
static int Display_centering_offset;
static int Display_centering_scaled_width = 0;
static int Display_centering_scaled_height = 0;
static int doublebuf;
static int dirty;
static int hardware;
static int mode_number;
static int start_fullscreen;
#ifdef IPU_SCALER
static int ipu_scaler;
static char *ipu_scaler_file;
static char *ipu_aspect_ratio_file;
#endif
static SDL_Surface* Surface;
SDL_Color *Colors=NULL;
static int cursor_state; /* previous mouse cursor state */

typedef void (*update_func_t)(struct mame_bitmap *bitmap);

update_func_t update_function;

static int sdl_mapkey(struct rc_option *option, const char *arg, int priority);

static int list_sdl_modes(struct rc_option *option, const char *arg, int priority);

struct rc_option display_opts[] = {
    /* name, shortname, type, dest, deflt, min, max, func, help */
   { "SDL Related",  NULL,    rc_seperator,  NULL,
       NULL,         0,       0,             NULL,
       NULL },
   { "fullscreen",   NULL,    rc_bool,       &start_fullscreen,
      "1",           0,       0,             NULL,
      "Start fullscreen" },
   { "listmodes",    NULL,    rc_use_function_no_arg,       NULL,
      NULL,           0,       0,             list_sdl_modes,
      "List all posible fullscreen modes" },
   { "doublebuf",   "triplebuf", rc_bool,    &doublebuf,
      "0",           0,       0,             NULL,
      "Use double buffering to reduce flicker/tearing" },
#ifdef IPU_SCALER
   { "ipu_scaler",  "ipu",    rc_int,       &ipu_scaler,
     "1",            0,       2,             NULL,
     "Use the GCW-Zero IPU to perform hardware scaling." },
   { "ipu_scaler_file","isf", rc_string,     &ipu_scaler_file,
     "/sys/devices/platform/jz-lcd.0/allow_downscaling", 0, 0, NULL,
     "Filename to allow GCW-Zero IPU scaling" },
   { "ipu_aspect_ratio_file","iarf", rc_string,     &ipu_aspect_ratio_file,
     "/sys/devices/platform/jz-lcd.0/keep_aspect_ratio", 0, 0, NULL,
     "Filename to determine type of GCW-Zero IPU scaling" },
#endif

   { "dirty",       NULL,    rc_bool,       &dirty,
      "0",           0,       0,             NULL,
      "Deprecated, no longer used" },
   { "modenumber",   NULL,    rc_int,        &mode_number,
      "-1",          0,       0,             NULL,
      "Try to use the fullscreen mode numbered 'n' (see the output of -listmodes)" },
   { "sdlmapkey",	"sdlmk",	rc_use_function,	NULL,
     NULL,		0,			0,		sdl_mapkey,
     "Set a specific key mapping, see xmamerc.dist" },
   { NULL,           NULL,    rc_end,        NULL,
      NULL,          0,       0,             NULL,
      NULL }
};


/* The following are used by the fitscale blitter */
unsigned int iAddX = 1, iModuloX = 1, iAddY = 1, iModuloY = 1;
/* These macros are used by the resizing blitters */
/* These have values specific to a 32-bit destination pixel xxxxxxxxRRRRRRRRGGGGGGGGBBBBBBBB */
#define VIDEO_GETR32(C) ((C)&0xFF0000)
#define VIDEO_GETG32(C) ((C)&0x00FF00)
#define VIDEO_GETB32(C) ((C)&0x0000FF)
#define VIDEO_COLOR32(R,G,B) ((VIDEO_GETR32(R))|(VIDEO_GETG32(G))|(VIDEO_GETB32(B)))
#define R_G_B_MASK32  0x00FEFEFE
INLINE unsigned int mix_color32 (unsigned int color1, unsigned int color2)
{
        unsigned int expanded_pixel1 = (color1 & R_G_B_MASK32);
        unsigned int expanded_pixel2 = (color2 & R_G_B_MASK32);
	unsigned int averaged_pixel = (expanded_pixel1+expanded_pixel2)>>1;
	averaged_pixel &= R_G_B_MASK32;
	return averaged_pixel;
        //return VIDEO_COLOR32((VIDEO_GETR32(color1)+VIDEO_GETR32(color2))>>1,(VIDEO_GETG32(color1)+VIDEO_GETG32(color2))>>1,(VIDEO_GETB32(color1)+VIDEO_GETB32(color2))>>1);
}
/* These have values specific to a 16-bit destination pixel RRRRRGGGGGGBBBBB */
#define VIDEO_GETR16(C) ((C)&0xF800)
#define VIDEO_GETG16(C) ((C)&0x07E0)
#define VIDEO_GETB16(C) ((C)&0x001F)
#define VIDEO_COLOR16(R,G,B) ((VIDEO_GETR16(R))|(VIDEO_GETG16(G))|(VIDEO_GETB16(B)))
#define G_R_B_MASK16  0x07E0F81F
INLINE unsigned short mix_color16 (unsigned short color1, unsigned short color2)
{
        unsigned int expanded_pixel1 = (color1 | (color1 << 16)) & G_R_B_MASK16;
        unsigned int expanded_pixel2 = (color2 | (color2 << 16)) & G_R_B_MASK16;
	unsigned int averaged_pixel = (expanded_pixel1+expanded_pixel2)>>1;
	averaged_pixel &= G_R_B_MASK16;
	return averaged_pixel | (averaged_pixel >>16);
        //return VIDEO_COLOR16((VIDEO_GETR16(color1)+VIDEO_GETR16(color2))>>1,(VIDEO_GETG16(color1)+VIDEO_GETG16(color2))>>1,(VIDEO_GETB16(color1)+VIDEO_GETB16(color2))>>1);
}

void sdl_update_16_to_16bpp_rot0_1_2(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_fitscale_rot90_1_2(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot180_1_2(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot0_fast(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot0(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot90(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot180(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_rot270(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_flipx(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_flipy(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_horzscale(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_horzscale_1_2(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_fitscale_rot0(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_fitscale_rot90(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_fitscale_rot180(struct mame_bitmap *bitmap);
void sdl_update_16_to_16bpp_fitscale_rot270(struct mame_bitmap *bitmap);
void sdl_update_rgb_direct_16bpp(struct mame_bitmap *bitmap);
void sdl_update_rgb_direct_32bpp(struct mame_bitmap *bitmap);
void sdl_update_rgb_direct_32bpp_rot90(struct mame_bitmap *bitmap);

static inline void CalcCenterDisplay(void)
{
	int offset_x = 0;
	int offset_y = 0;
#ifdef IPU_SCALER
    if (ipu_scaler)
    {
#ifdef SDL_DEBUG
        printf("SDL_SetVideoMode() returned w:%d h:%d pitch:%d\n", Surface->w,Surface->h,Surface->pitch);
#endif
        Display_centering_offset = 0;
        if (Display_pitch/Display_BytesPerPixel > Display_width)
        {
            Display_centering_offset += ((Display_pitch/Display_BytesPerPixel - Display_width)/2);
        }
    }
    else
#endif
    {
	    offset_x = (Display_width - Display_centering_scaled_width*widthscale ) / 2;
	    offset_y = (Display_height - Display_centering_scaled_height*heightscale ) / 2;

	    if (offset_x < 0) offset_x = 0;
	    if (offset_y < 0) offset_y = 0;

	    Display_centering_offset = offset_x + (Display_width * offset_y);
    }

#ifdef SDL_DEBUG
printf("Display_centering_offset = %d (x:%d y:%d)\n", Display_centering_offset, offset_x, offset_y);
printf("Display_height %d Display_centering_scaled_height %d heightscale %d\n", Display_height, Display_centering_scaled_height, heightscale);
printf("Display_width %d Display_centering_scaled_width %d widthscale %d\n", Display_width, Display_centering_scaled_width, widthscale);
#endif
}

static inline void ChooseBlitter(void)
{
    /* Check for 1:2 ratio games.
     * ie 640x240 which are just double horizontal resolution
     * Note: no 2:1 ratio games exist so not checking for VIDEO_PIXEL_ASPECT_RATIO_2_1
     */
    if (Machine->drv->video_attributes & VIDEO_PIXEL_ASPECT_RATIO_1_2)
	{
		Display_centering_scaled_width = visual_width/2;
		Display_centering_scaled_height = visual_height;
		heightscale=1;// reset back to 1

		// If the game's width fits (when horizontal resolution is halved)
		// use a standard blitter (but skip every other SRC pixel)
		if (Display_width < (visual_width/2))
		{
			update_function = &sdl_update_16_to_16bpp_horzscale_1_2;
			printf("BLIT: sdl_update_16_to_16bpp_horzscale_1_2\n");
		}
		else
		{
			// Use one of the other bltters
			// Only supporting the ones that are needed for 1:2 ratio games
			// 1:1 ratio games have a much fuller library of required blits
			if (blit_swapxy && blit_flipx)
			{
				Display_centering_scaled_height = visual_height/2;
				Display_centering_scaled_width = (visual_width * Display_height + (visual_height/2) - 1) / (visual_height/2);
				iAddY = Display_height;
				iModuloY = visual_height/2;
				iAddX = iAddY;
				iModuloX = iModuloY;
				update_function = &sdl_update_16_to_16bpp_fitscale_rot90_1_2;
				printf("BLIT: sdl_update_16_to_16bpp_fitscale_rot90_1_2\n");
			}
			else if (blit_flipx && blit_flipy)
			{
				update_function = &sdl_update_16_to_16bpp_rot180_1_2;
				printf("BLIT: sdl_update_16_to_16bpp_rot180_1_2\n");
			}
			else
			{
				update_function = &sdl_update_16_to_16bpp_rot0_1_2;
				printf("BLIT: sdl_update_16_to_16bpp_rot0_1_2\n");
			}
		}
	}
    else
	{
		if (Display_width < visual_width)
		{
			iAddX = Display_width;
			iModuloX = visual_width;
			Display_centering_scaled_width = Display_width;
		}
		if (Display_height < visual_height)
		{
			iAddY = Display_height;
			iModuloY = visual_height;
			Display_centering_scaled_height = Display_height;
		}
		// If either the game's width or height is greater than the display ...
		// ... use a scaling blitter
		if (Display_width < visual_width || Display_height < visual_height)
		{
			if (visual_width > Display_width && ((Display_width/(visual_width-Display_width))*(visual_width-Display_width)==Display_width) && (!(Machine->drv->video_attributes & VIDEO_DUAL_MONITOR)) && visual_height <=256)
			{
				// If width is greater than the display AND
				// the game's resolution is cleanly divisibly 
				// and the height is less than or equal to 256
				// ... use a speed optimized horizontal scaling blitter
				Display_centering_scaled_height = visual_height;
				printf("BLIT: sdl_update_16_to_16bpp_horzscale\n");
				update_function = &sdl_update_16_to_16bpp_horzscale;
			}
			else
			{
				// Otherwise use the other blitter
				// This blitter should be able to handle any resolution (larger than the display)
				// and scale it down to fit keeping the original aspect ration
				if (visual_height * Display_width < Display_height * visual_width)
				{
					// scale is determined by horizontal scale
					{
					iAddY = iAddX;
					iModuloY = iModuloX;
					Display_centering_scaled_height = (visual_height * Display_width + visual_width - 1) / visual_width;
					}
				}
				else
				{
					// Scale is determined by vertical scale
					{
					iAddX = iAddY;
					iModuloX = iModuloY;
					Display_centering_scaled_width = (visual_width * Display_height + visual_height - 1) / visual_height;
					}
				}
	printf("Display_centering_scaled_width %d Display_centering_scaled_height %d\n", Display_centering_scaled_width, Display_centering_scaled_height);
				if (blit_swapxy && blit_flipx)
				{
				update_function = &sdl_update_16_to_16bpp_fitscale_rot90;
				printf("BLIT: sdl_update_16_to_16bpp_fitscale_rot90\n");
				}
				else if (blit_swapxy && blit_flipy)
				{
				update_function = &sdl_update_16_to_16bpp_fitscale_rot270;
				printf("BLIT: sdl_update_16_to_16bpp_fitscale_rot270\n");
				}
				else if (blit_flipx && blit_flipy)
				{
				update_function = &sdl_update_16_to_16bpp_fitscale_rot180;
				printf("BLIT: sdl_update_16_to_16bpp_fitscale_rot180\n");
				}
				else 
				{
				update_function = &sdl_update_16_to_16bpp_fitscale_rot0;
				printf("BLIT: sdl_update_16_to_16bpp_fitscale_rot0\n");
				}
			}
		}
		else
		{
			// Used by screen centering code later...
			Display_centering_scaled_width = visual_width;
			Display_centering_scaled_height = visual_height;

			if (blit_flipx && blit_flipy)
			{
				printf("BLIT: sdl_update_16_to_16bpp_rot180\n");
				update_function = &sdl_update_16_to_16bpp_rot180;
			}
			else
			if (blit_flipx)
			{
				printf("BLIT: sdl_update_16_to_16bpp_flipx\n");
				update_function = &sdl_update_16_to_16bpp_flipx;
			}
			else
			if (blit_flipx && blit_flipy)
			{
				printf("BLIT: sdl_update_16_to_16bpp_flipy\n");
				update_function = &sdl_update_16_to_16bpp_flipy;
			}
			else
			{
				// If width divisible by 8 use the quicker version of the blitter
				if ((visual_width % 8) == 0)
				{
					printf("BLIT: sdl_update_16_to_16bpp_rot0_fast\n");
					update_function = &sdl_update_16_to_16bpp_rot0_fast;
				}
				else
				{
					printf("BLIT: sdl_update_16_to_16bpp_rot0\n");
					update_function = &sdl_update_16_to_16bpp_rot0;
				}

			}
		}
	}

    /* Centering limits */
    if (Display_centering_scaled_width > Display_width)
    {
	Display_centering_scaled_width = Display_width;
    }
    if (Display_centering_scaled_height > Display_height)
    {
	Display_centering_scaled_height = Display_height;
    }
}

void sysdep_ipu_aspect_ratio(int keep_aspect_ratio)
{
    FILE* aspect_ratio_file = fopen(ipu_aspect_ratio_file, "w");
    if (aspect_ratio_file)
    {
        fwrite(keep_aspect_ratio?"1":"0", 1, 1, aspect_ratio_file);
        fclose(aspect_ratio_file);
    }
}

void sysdep_ipu_scaler(int enable_ipu_scaler)
{
    FILE* scaler_file = fopen(ipu_scaler_file, "w");
    if (scaler_file)
    {
        fwrite(enable_ipu_scaler?"1":"0", 1, 1, scaler_file);
        fclose(scaler_file);
    }
}


int sysdep_init(void)
{
   /* This needs to be set before SDL_Init() is called */
   if (ipu_scaler)
   {
      sysdep_ipu_scaler(1);
      /* Setup the IPU scaler */
      if (ipu_scaler==2 /* fullscreen */)
         sysdep_ipu_aspect_ratio(0);
      else
         sysdep_ipu_aspect_ratio(1);
   }
   else
   {
      sysdep_ipu_scaler(0);
   }

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf (stderr, "SDL: Error: %s\n",SDL_GetError());
      return OSD_NOT_OK;
   } 
#ifdef SDL_DEBUG
   fprintf (stderr, "SDL: Info: SDL initialized\n");
#endif
   atexit (SDL_Quit);
   return OSD_OK;
}

void sysdep_close(void)
{
   SDL_Quit();
}

int sysdep_create_display(int width, int height, int depth, int using_15bpp_rgb_direct)
{
   SDL_Rect** vid_modes;
   const SDL_VideoInfo* video_info;
   int vid_modes_i;
   int vid_mode_flag; /* Flag to set the video mode */

#ifdef SDL_DEBUG
   printf("sysdep_create_display(%d,%d,%d)\n", width, height, depth);
#endif

   video_info = SDL_GetVideoInfo();

#ifdef SDL_DEBUG
   fprintf (stderr,"SDL: create_display(%d): \n",depth);
   fprintf (stderr,"SDL: Info: HW blits %d\n"
      "SDL: Info: SW blits %d\n"
      "SDL: Info: Vid mem %d\n"
      "SDL: Info: Best supported depth %d\n",
      video_info->blit_hw,
      video_info->blit_sw,
      video_info->video_mem,
      video_info->vfmt->BitsPerPixel);
#endif

#ifdef GCW0
   if (depth == 32 && Machine->drv->video_attributes & (VIDEO_RGB_DIRECT | VIDEO_NEEDS_6BITS_PER_GUN))
      Display_depth = 32;  // One exception, see above condition
   else
      Display_depth = 16;  // pretty much always 16-bit depth
#else
   Display_depth = video_info->vfmt->BitsPerPixel;
#endif

#ifdef IPU_SCALER
   if (ipu_scaler)
   {
		/* Default landscape orientation */
        Display_width = width;
        Display_height = height;

        /* Define the blitter */
        switch( depth )
        {
            case 32:
		if (blit_swapxy && blit_flipx)
		{
		    printf("BLIT: sdl_update_rgb_direct_32bpp_rot90\n");
		    update_function = &sdl_update_rgb_direct_32bpp_rot90;
		}
		else
		{
		    printf("BLIT: sdl_update_rgb_direct_32bpp\n");
		    update_function = &sdl_update_rgb_direct_32bpp;
		}
                break;
            case 16:
			{

				if (blit_swapxy && blit_flipx)
				{
					update_function = &sdl_update_16_to_16bpp_rot90;
					printf("BLIT: sdl_update_16_to_16bpp_rot90\n");
				}
				else if (blit_swapxy && blit_flipy)
				{
					update_function = &sdl_update_16_to_16bpp_rot270;
					printf("BLIT: sdl_update_16_to_16bpp_rot270\n");
				}
				else if (blit_flipx && blit_flipy)
				{
					printf("BLIT: sdl_update_16_to_16bpp_rot180\n");
					update_function = &sdl_update_16_to_16bpp_rot180;
				}
				else if (blit_flipx)
				{
					printf("BLIT: sdl_update_16_to_16bpp_flipx\n");
					update_function = &sdl_update_16_to_16bpp_flipx;
				}
				else if (blit_flipy)
				{
					printf("BLIT: sdl_update_16_to_16bpp_flipy\n");
					update_function = &sdl_update_16_to_16bpp_flipy;
				}
				else
				{
					// If width divisible by 8 use the quicker version of the blitter
					if ((visual_width % 8) == 0)
					{
						if (using_15bpp_rgb_direct)
						{
							printf("BLIT: sdl_update_rgb_direct_16bpp\n");
							update_function = &sdl_update_rgb_direct_16bpp;
						}
						else
						{
							printf("BLIT: sdl_update_16_to_16bpp_rot0_fast\n");
							update_function = &sdl_update_16_to_16bpp_rot0_fast;
						}
					}
					else
					{
						printf("BLIT: sdl_update_16_to_16bpp_rot0\n");
						update_function = &sdl_update_16_to_16bpp_rot0;
					}

				}
				break;
			}
			default:
				printf("BLIT: Unsupported depth: %d\n", depth);
        }
   }
   else
#endif
   {
	   vid_modes = SDL_ListModes(NULL,SDL_FULLSCREEN);
	   vid_modes_i = 0;

	   hardware = video_info->hw_available;

	   if ( (! vid_modes) || ((long)vid_modes == -1)) {
	#ifdef SDL_DEBUG
		  fprintf (stderr, "SDL: Info: Possible all video modes available\n");
	#endif
		  Display_height = visual_height*heightscale;
		  Display_width = visual_width*widthscale;
	   } else {
		  int best_vid_mode; /* Best video mode found */
		  int best_width,best_height;
		  int i;

	#ifdef SDL_DEBUG
		  fprintf (stderr, "SDL: visual w:%d visual h:%d\n", visual_width, visual_height);
	#endif
		  best_vid_mode = 0;
		  best_width = vid_modes[best_vid_mode]->w;
		  best_height = vid_modes[best_vid_mode]->h;
		  for (i=0;vid_modes[i];++i)
		  {
			 int cur_width, cur_height;

			 cur_width = vid_modes[i]->w;
			 cur_height = vid_modes[i]->h;

		 /* If there is only one mode - like on most handheld devices - use first found! */
		 if (i==0)
		 {
				best_vid_mode = i;
				best_width = cur_width;
				best_height = cur_height;
		 }

	#ifdef SDL_DEBUG
			 fprintf (stderr, "SDL: Info: Found mode %d x %d\n", cur_width, cur_height);
	#endif /* SDL_DEBUG */

			 /* If width and height too small, skip to next mode */
			 if ((cur_width < visual_width*widthscale) || (cur_height < visual_height*heightscale)) {
				continue;
			 }

			 /* If width or height smaller than current best, keep it */
			 if ((cur_width < best_width) || (cur_height < best_height)) {
				best_vid_mode = i;
				best_width = cur_width;
				best_height = cur_height;
			 }
		  }

	#ifdef SDL_DEBUG
		  fprintf (stderr, "SDL: Info: Best mode found : %d x %d\n",
			 vid_modes[best_vid_mode]->w,
			 vid_modes[best_vid_mode]->h);
	#endif /* SDL_DEBUG */

		  vid_modes_i = best_vid_mode;

		  /* mode_number is a command line option */
		  if( mode_number != -1) {
			 if( mode_number >vid_modes_i)
				fprintf(stderr, "SDL: The mode number is invalid... ignoring\n");
			 else
				vid_modes_i = mode_number;
		  }
		  if( vid_modes_i<0 ) {
			 fprintf(stderr, "SDL: None of the modes match :-(\n");
			 Display_height = visual_height*heightscale;
			 Display_width = visual_width*widthscale;
		  } else {
			 if(*(vid_modes+vid_modes_i)==NULL) 
				vid_modes_i--;

			 Display_width = (*(vid_modes + vid_modes_i))->w;
			 Display_height = (*(vid_modes + vid_modes_i))->h;
		  }
	   }

	   if( depth == 16 ) {
		 // Set the blitter, either scaling or straight copy
		 ChooseBlitter();
	   }
	   else if( depth == 15 ) 
	   {
		 printf("BLIT: sdl_update_rgb_direct_32bpp\n");
			 update_function = &sdl_update_rgb_direct_32bpp;
	   }
	   else
	   {
		  fprintf (stderr, "SDL: Unsupported depth=%d\n", depth);
		  SDL_Quit();
		  exit (OSD_NOT_OK);
	   }
   }

   /* Set video mode according to flags */
   vid_mode_flag = SDL_HWSURFACE;
   if (start_fullscreen) {
      vid_mode_flag |= SDL_FULLSCREEN;
   }
   if (doublebuf) {
      vid_mode_flag |= SDL_TRIPLEBUF;	/* Triple buffer on the GCW0 */
   }

   printf("SDL_SetVideoMode(%d,%d,%d,%u)\n", Display_width, Display_height,Display_depth, vid_mode_flag);

   if(! (Surface = SDL_SetVideoMode(Display_width, Display_height,Display_depth, vid_mode_flag))) {
      fprintf (stderr, "SDL: Error: Setting video mode failed\n");
      SDL_Quit();
      exit (OSD_NOT_OK);
   } else {
      fprintf (stderr, "SDL: Info: Video mode set as %d x %d, depth %d\n", Display_width, Display_height, Display_depth);
   }

   /* When using the IPU_SCALER mode sometimes what is requested isn't exactly what we get */
   Display_pitch = Surface->pitch;
   Display_BytesPerPixel = Surface->format->BytesPerPixel;

   /* Center the display */
   CalcCenterDisplay();

   /* Creating event mask */
   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
   SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
   SDL_EnableUNICODE(1);
   
    /* fill the display_palette_info struct */
    memset(&display_palette_info, 0, sizeof(struct sysdep_palette_info));
    display_palette_info.depth = Display_depth;
    if (Display_depth == 8)
         display_palette_info.writable_colors = 256;
    else if (Display_depth == 16) {
      display_palette_info.red_mask = 0xF800;
      display_palette_info.green_mask = 0x07E0;
      display_palette_info.blue_mask   = 0x001F;
    }
    else {
      display_palette_info.red_mask   = 0x00FF0000;
      display_palette_info.green_mask = 0x0000FF00;
      display_palette_info.blue_mask  = 0x000000FF;
    };

   /* Hide mouse cursor and save its previous status */
   cursor_state = SDL_ShowCursor(0);

   /* Set window title */
   SDL_WM_SetCaption(title, NULL);

   // There's not enough resolution for effects
   // However effect.c also does the rotation if we a displaying a 
   // "portrait" monitor on our landscape device...
   // So, we either need the blitters to do rotations.
   // or keep the effects in... which aren't very efficient.
   // effect_init2(depth, Display_depth, Display_width);

   return OSD_OK;
}

/*
 *  keyboard remapping routine
 *  invoiced in startup code
 *  returns 0-> success 1-> invalid from or to
 */
static int sdl_mapkey(struct rc_option *option, const char *arg, int priority)
{
   unsigned int from, to;
   /* ultrix sscanf() requires explicit leading of 0x for hex numbers */
   if (sscanf(arg, "0x%x,0x%x", &from, &to) == 2)
   {
      /* perform tests */
      /* fprintf(stderr,"trying to map %x to %x\n", from, to); */
      if (from >= SDLK_FIRST && from < SDLK_LAST && to >= 0 && to <= 127)
      {
         klookup[from] = to;
	 return OSD_OK;
      }
      /* stderr_file isn't defined yet when we're called. */
      fprintf(stderr,"Invalid keymapping %s. Ignoring...\n", arg);
   }
   return OSD_NOT_OK;
}

/* Update routines */
/* Special fast scaler to downsize larger than 320x240 screens*/
#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define SRC_INC 1
#define MY_FUNCTION sdl_update_16_to_16bpp_horzscale
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#include "blit_horzscale.h"
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_INC
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef DEST_PIXEL
#undef SRC_PIXEL

#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define SRC_INC 2
#define MY_FUNCTION sdl_update_16_to_16bpp_horzscale_1_2
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#include "blit_horzscale.h"
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_INC
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef DEST_PIXEL
#undef SRC_PIXEL

#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define MY_FUNCTION sdl_update_16_to_16bpp_fitscale_rot0
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#define SRC_INC 1
#define SRC_INC_LINE (bitmap->line[1] - bitmap->line[0])>>1
#define MODX iModuloX
#define MODY iModuloY
#define ADDX iAddX
#define ADDY iAddY
#include "blit_scale.h"
#undef ADDY
#undef ADDX
#undef MODY
#undef MODX
#undef SRC_INC_LINE
#undef SRC_INC
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL

#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
//#define SRC ((SRC_PIXEL *)bitmap->line[visual.max_x]+ visual.min_y)
#define SRC ((SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_x] + visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define MY_FUNCTION sdl_update_16_to_16bpp_fitscale_rot90
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#define SRC_INC -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC_LINE 1
#define MODX iModuloY
#define MODY iModuloX
#define ADDX iAddY
#define ADDY iAddX
#include "blit_scale.h"
#undef ADDY
#undef ADDX
#undef MODY
#undef MODX
#undef SRC_INC_LINE
#undef SRC_INC
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL

#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_y] + bitmap->width - 1 - visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define MY_FUNCTION sdl_update_16_to_16bpp_fitscale_rot180
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#define SRC_INC -1
#define SRC_INC_LINE -((bitmap->line[1] - bitmap->line[0])>>1)
#define MODX iModuloY
#define MODY iModuloX
#define ADDX iAddX
#define ADDY iAddY
#include "blit_scale.h"
#undef ADDY
#undef ADDX
#undef MODY
#undef MODX
#undef SRC_INC_LINE
#undef SRC_INC
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL

#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
//#define SRC ((SRC_PIXEL *)bitmap->line[visual.min_x]+ visual.max_y)
#define SRC ((SRC_PIXEL *)bitmap->line[visual.min_x]+ bitmap->width - 1 - visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define MY_FUNCTION sdl_update_16_to_16bpp_fitscale_rot270
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#define SRC_INC ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC_LINE -1
#define MODX iModuloY
#define MODY iModuloX
#define ADDX iAddY
#define ADDY iAddX
#include "blit_scale.h"
#undef ADDY
#undef ADDX
#undef MODY
#undef MODX
#undef SRC_INC_LINE
#undef SRC_INC
#undef INDIRECT
#undef MY_FUNCTION
#undef DESTMIX
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL

#define MY_FUNCTION sdl_update_rgb_direct_16bpp
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT 0
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Surface->pitch>>1)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC 1
#include "blit_rot0_fast.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot0_fast
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Surface->pitch>>1)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC 1
#include "blit_rot0_fast.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot0_1_2
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH (visual_width>>1)
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Surface->pitch>>1)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC 2
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_fitscale_rot90_1_2
#define SRC_PIXEL  unsigned short
#define DEST_PIXEL unsigned short
#define SRC ((SRC_PIXEL *)bitmap->line[visual.max_x]+ visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define DEST_WIDTH Display_width
#define DEST_HEIGHT Display_height
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DESTMIX mix_color16
#define INDIRECT current_palette->lookup
#define SRC_INC -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC_LINE 2
#define MODX iModuloY
#define MODY iModuloX
#define ADDX iAddY
#define ADDY iAddX
#include "blit_scale.h"
#undef ADDY
#undef ADDX
#undef MODY
#undef MODX
#undef SRC_INC_LINE
#undef SRC_INC
#undef INDIRECT
#undef DESTMIX
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef DEST_HEIGHT
#undef DEST_WIDTH
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION


#define MY_FUNCTION sdl_update_16_to_16bpp_rot180_1_2
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_y] + bitmap->width - 1 - visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH (visual_width>>1)
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC -2
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot0
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC 1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot90
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC ((SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_x] + visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC_LINE 1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot270
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC ((SRC_PIXEL *)bitmap->line[visual.min_x]+ bitmap->width - 1 - visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC_LINE -1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_flipx
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x + bitmap->width - 1;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC -1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_flipy
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
//#define SRC (SRC_PIXEL *)bitmap->line[visual.max_y] + visual.min_x;
#define SRC (SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC 1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_16_to_16bpp_rot180
#define SRC_PIXEL unsigned short
#define DEST_PIXEL unsigned short
#define SRC (SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_y] + bitmap->width - 1 - visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT current_palette->lookup
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE -((bitmap->line[1] - bitmap->line[0])>>1)
#define SRC_INC -1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_rgb_direct_32bpp
#define SRC_PIXEL unsigned int
#define DEST_PIXEL unsigned int
#define SRC (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
#define INDIRECT 0
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC_LINE ((bitmap->line[1] - bitmap->line[0])>>2)
#define SRC_INC 1
#include "blit_rot0_fast.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION

#define MY_FUNCTION sdl_update_rgb_direct_32bpp_rot90
#define SRC_PIXEL unsigned int
#define DEST_PIXEL unsigned int
#define SRC ((SRC_PIXEL *)bitmap->line[bitmap->height - 1 - visual.min_x] + visual.min_y)
#define DEST ((DEST_PIXEL *)Surface->pixels + Display_centering_offset)
//#undef INDIRECT
#define SRC_WIDTH visual_width
#define SRC_HEIGHT visual_height
#define DEST_INC_LINE (Display_pitch/Display_BytesPerPixel)
#define SRC_INC -((bitmap->line[1] - bitmap->line[0])>>2)
#define SRC_INC_LINE 1
#include "blit_any_90.h"
#undef SRC_INC
#undef SRC_INC_LINE
#undef DEST_INC_LINE
#undef SRC_HEIGHT
#undef SRC_WIDTH
#undef INDIRECT
#undef DEST
#undef SRC
#undef DEST_PIXEL
#undef SRC_PIXEL
#undef MY_FUNCTION


void sysdep_update_display(struct mame_bitmap *bitmap)
{
#ifdef GCW0
    // GCW writes directly to hardware surface for maximum speed
   (*update_function)(bitmap);
   if (doublebuf == 1)
      SDL_Flip(Surface);
#else
   SDL_Rect srect = { 0,0,0,0 };
   SDL_Rect drect = { 0,0,0,0 };
   srect.w = Display_width;
   srect.h = Display_height;

   /* Center the display */
   drect.x = (Display_width - visual_width*widthscale ) >> 1;
   drect.y = (Display_height - visual_height*heightscale ) >> 1;

   drect.w = Display_width;
   drect.h = Display_height;

   (*update_function)(bitmap);
   
   if(SDL_BlitSurface (Offscreen_surface, &srect, Surface, &drect)<0) 
      fprintf (stderr,"SDL: Warn: Unsuccessful blitting\n");

   if(hardware==0)
      SDL_UpdateRects(Surface,1, &drect);
#endif
}

/* shut up the display */
void sysdep_display_close(void)
{
#ifdef GCW0
#else
   SDL_FreeSurface(Offscreen_surface);
#endif

   /* Restore cursor state */
   SDL_ShowCursor(cursor_state);
}

/*
 * In 8 bpp we should alloc pallete - some ancient people  
 * are still using 8bpp displays
 */
int sysdep_display_alloc_palette(int totalcolors)
{
#ifdef GCW0
   // GCW0/Nanonote/A320/A380,etc do not have an 8-bit display mode
#else
   int ncolors;
   int i;
   ncolors = totalcolors;

   fprintf (stderr, "SDL: sysdep_display_alloc_palette(%d);\n",totalcolors);
   if (Display_depth != 8)
      return 0;

   Colors = (SDL_Color*) malloc (totalcolors * sizeof(SDL_Color));
   if( !Colors )
      return 1;
   for (i=0;i<totalcolors;i++) {
      (Colors + i)->r = 0xFF;
      (Colors + i)->g = 0x00;
      (Colors + i)->b = 0x00;
   }
   SDL_SetColors (Offscreen_surface,Colors,0,totalcolors-1);

   fprintf (stderr, "SDL: Info: Palette with %d colors allocated\n", totalcolors);
#endif
   return 0;
}

int sysdep_display_set_pen(int pen,unsigned char red, unsigned char green, unsigned char blue)
{
#ifdef GCW0
#else
   static int warned = 0;
#ifdef SDL_DEBUG
   fprintf(stderr,"sysdep_display_set_pen(%d,%d,%d,%d)\n",pen,red,green,blue);
#endif

   if( Colors ) {
      (Colors + pen)->r = red;
      (Colors + pen)->g = green;
      (Colors + pen)->b = blue;
      if ( (! SDL_SetColors(Offscreen_surface, Colors + pen, pen,1)) && (! warned)) {
         printf ("Color allocation failed, or > 8 bit display\n");
         warned = 0;
      }
   }

#ifdef SDL_DEBUG
   fprintf(stderr, "STD: Debug: Pen %d modification: r %d, g %d, b, %d\n", pen, red,green,blue);
#endif /* SDL_DEBUG */
#endif
   return 0;
}

void sysdep_mouse_poll (void)
{
   int i;
   int x,y;
   Uint8 buttons;

   buttons = SDL_GetRelativeMouseState( &x, &y);
   mouse_data[0].deltas[0] = x;
   mouse_data[0].deltas[1] = y;
   for(i=0;i<MOUSE_BUTTONS;i++) {
      mouse_data[0].buttons[i] = buttons & (0x01 << i);
   }
}

/* Keyboard procs */
/* Lighting keyboard leds */
void sysdep_set_leds(int leds) 
{
}

void sysdep_update_keyboard() 
{
   struct xmame_keyboard_event kevent;
   SDL_Event event;

   if (Surface) {
      while(SDL_PollEvent(&event)) {
         kevent.press = 0;
         
         switch (event.type)
         {
            case SDL_KEYDOWN:
               kevent.press = 1;

               /* ALT-Enter: toggle fullscreen */
               if ( event.key.keysym.sym == SDLK_RETURN )
               {
                  if(event.key.keysym.mod & KMOD_ALT)
                     SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
               }

            case SDL_KEYUP:
               kevent.scancode = klookup[event.key.keysym.sym];
               kevent.unicode = event.key.keysym.unicode;
               xmame_keyboard_register_event(&kevent);
#ifdef SDL_DEBUG
               if(!kevent.scancode)
                  fprintf (stderr, "Unknown symbol 0x%x\n",
                     event.key.keysym.sym);
               fprintf (stderr, "Key %s %ssed\n",
                  SDL_GetKeyName(event.key.keysym.sym),
                  kevent.press? "pres":"relea");
#endif
               break;
            case SDL_QUIT:
               /* Shoult leave this to application */
               exit(OSD_OK);
               break;

    	    case SDL_JOYAXISMOTION:   
               if (event.jaxis.which < JOY_AXIS)
                  joy_data[event.jaxis.which].axis[event.jaxis.axis].val = event.jaxis.value;
#ifdef SDL_DEBUG
               fprintf (stderr,"Axis=%d,value=%d\n",event.jaxis.axis ,event.jaxis.value);
#endif
		break;
	    case SDL_JOYBUTTONDOWN:

	    case SDL_JOYBUTTONUP:
               if (event.jbutton.which < JOY_BUTTONS)
                  joy_data[event.jbutton.which].buttons[event.jbutton.button] = event.jbutton.state;
#ifdef SDL_DEBUG
               fprintf (stderr, "Button=%d,value=%d\n",event.jbutton.button ,event.jbutton.state);
#endif
		break;


            default:
#ifdef SDL_DEBUG
               fprintf(stderr, "SDL: Debug: Other event\n");
#endif /* SDL_DEBUG */
               break;
         }
    joy_evaluate_moves ();
      }
   }
}

/* added funcions */
int sysdep_display_16bpp_capable(void)
{
   const SDL_VideoInfo* video_info;
   video_info = SDL_GetVideoInfo();
   return ( video_info->vfmt->BitsPerPixel >=16);
}

int list_sdl_modes(struct rc_option *option, const char *arg, int priority)
{
   SDL_Rect** vid_modes;
   int vid_modes_i;

   vid_modes = SDL_ListModes(NULL,SDL_FULLSCREEN);
   vid_modes_i = 0;

   if ( (! vid_modes) || ((long)vid_modes == -1)) {
      printf("This option only works in a full-screen mode (eg: linux's framebuffer)\n");
      return - 1;
   }

   printf("Modes available:\n");

   while( *(vid_modes+vid_modes_i) ) {
      printf("\t%d) Mode %d x %d\n",
         vid_modes_i,
         (*(vid_modes+vid_modes_i))->w,
         (*(vid_modes+vid_modes_i))->h
         );
   
      vid_modes_i++;
   }

   return -1;
}
