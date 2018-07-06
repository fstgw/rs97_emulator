void MY_FUNCTION (struct mame_bitmap *bitmap)
{
    DEST_PIXEL *dest = DEST;
    SRC_PIXEL *src = (SRC_PIXEL *)bitmap->line[visual.min_y] + visual.min_x;
    int src_offset = ((bitmap->line[1] - bitmap->line[0])>>1)-SRC_WIDTH;
    int src_width = (bitmap->line[1] - bitmap->line[0]);
    int src_inc = SRC_INC;
    int xstep,ystep,i,j;
    int x,y=SRC_HEIGHT;


    if (Machine->drv->video_attributes & VIDEO_PIXEL_ASPECT_RATIO_1_2)
    {
	xstep=DEST_WIDTH/((SRC_WIDTH/2)-DEST_WIDTH);
    }
    else
    {
	xstep=DEST_WIDTH/(SRC_WIDTH-DEST_WIDTH);
    }

    if (SRC_HEIGHT>DEST_HEIGHT)
	ystep=DEST_HEIGHT/(SRC_HEIGHT-DEST_HEIGHT)+1;
    else
	ystep=SRC_HEIGHT;

    j=ystep;

    if(INDIRECT)
    {
	do {
	    x=DEST_WIDTH; i=xstep;
	    do {
		*dest++=INDIRECT[*src];
		src+=src_inc;
		x--; i--;
		if (!i) { if (x) { *dest++=DESTMIX(INDIRECT[*src],INDIRECT[*(src+src_inc)]); src+=(src_inc<<1); x--; i=xstep-1; } else { src+=src_inc; i=xstep; } }
	    } while (x);
	    src+=src_offset;
	    y--;
	    j--;
	    if (!j && y)
	    {
		/* Skip a source line */
		j=ystep;
		y--;
		src+=src_width;
	    }
	} while (y);
    }
    else
    {
	do {
	    x=DEST_WIDTH; i=xstep;
	    do {
		*dest++=*src;
		src+=src_inc;
		x--; i--;
		if (!i) { if (x) { *dest++=DESTMIX(*src,*(src+src_inc)); src+=(src_inc<<1); x--; i=xstep-1; } else { src+=src_inc; i=xstep; } }
	    } while (x);
	    src+=src_offset;
	    y--;
	    j--;
	    if (!j && y)
	    {
		/* Skip a source line */
		j=ystep;
		y--;
		src+=src_width;
	    }
	} while (y);
    }
}
