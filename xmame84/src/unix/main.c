/*
 * X-mame main-routine
 */

#define __MAIN_C_
#include "xmame.h"
#include <limits.h>
#include <libgen.h>

#if defined HAVE_MPROTECT || defined __QNXNTO__
#include <sys/mman.h>
#endif

char *frontend = NULL;
char frontendname[PATH_MAX];

/* From video.c. */
void osd_video_initpre();

/* put here anything you need to do when the program is started. Return 0 if */
/* initialization was successful, nonzero otherwise. */
int osd_init(void)
{
	/* now invoice system-dependent initialization */
#ifdef XMAME_NET
	if (osd_net_init()      !=OSD_OK) return OSD_NOT_OK;
#endif	
	if (osd_input_initpre() !=OSD_OK) return OSD_NOT_OK;

	return OSD_OK;
}

/*
 * Cleanup routines to be executed when the program is terminated.
 */
void osd_exit(void)
{
#ifdef XMAME_NET
	osd_net_close();
#endif
	osd_input_close();
}

void *osd_alloc_executable(size_t size)
{
	void *addr = malloc(size);
#ifdef HAVE_MPROTECT
	mprotect(addr, size, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
	return addr;
}

void osd_free_executable(void *ptr)
{
	free(ptr);
}

void set_xmameroot(void)
{
    if (getenv("XMAMEROOT")==(char*)0)
    {
	static char *current_dir;
	static char *newenv;
	current_dir=malloc(PATH_MAX);
	newenv=malloc(PATH_MAX);
	getcwd(current_dir, PATH_MAX);
	snprintf(newenv, PATH_MAX, "XMAMEROOT=%s", current_dir);
	putenv(newenv);
	/*free(current_dir);*/
	/*free(newenv);*/
    }
    printf ("Using XMAMEROOT=%s\n", getenv("XMAMEROOT"));
}

int main(int argc, char **argv)
{
	int res, res2;

	set_xmameroot();

	/* Init frontendname */
	memset(frontendname, 0, PATH_MAX);

	/* to be absolutely safe force giving up root rights here in case
	   a display method doesn't */
	if (setuid(getuid()))
	{
		perror("setuid");
		sysdep_close();
		return OSD_NOT_OK;
	}

	/* Set the title, now auto build from defines from the makefile */
	sprintf(title,"%s (%s) version %s", NAME, DISPLAY_METHOD,
			build_version);

	printf("%s\n", title);
	/* parse configuration file and environment */
	if ((res = config_init(argc, argv)) != 1234 || res2 == OSD_NOT_OK)
		goto leave;

	/* some display methods need to do some stuff with root rights */
	/*
	 * sysdep_init() has been moved to here.
	 * Originally located before config_init() but we need
	 * to run config_init() first before initializing SDL (and video)
	 * otherwise the frontend loses it's screen 
	 * when it's running xmame to query ROM lists, etc.
	 */
	res2 = sysdep_init();

	/* 
	 * Initialize whatever is needed before the display is actually 
	 * opened, e.g., artwork setup.
	 */
	osd_video_initpre();

	/* Check the colordepth we're requesting */
	if (!options.color_depth && !sysdep_display_16bpp_capable())
		options.color_depth = 8;

	/* go for it */
	res = run_game (game_index);

leave:
	sysdep_close();
	/* should be done last since this also closes stdout and stderr */
	config_exit();

	if (strlen(frontendname))
	{
	    int ret;
	    char frontend_path[PATH_MAX];

	    /* Launch frontend instead of exit() */
	    printf("Restarting frontend\n");

	    strcpy(frontend_path, frontendname);
	    chdir(dirname(frontend_path));
	    ret = execl(frontendname, frontendname);

	    printf("Failed to execl %s, code = %d\n", frontendname, ret);

	    return 1; /* fail */

	}
	else
	{
	    return res;
	}
}
