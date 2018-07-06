// Generic function to perform blits in any 90 degree rotation
// This blitter does no scaling
// For ROT0, use the optimized ROT0 blitter.
void MY_FUNCTION (struct mame_bitmap *bitmap)
{
    SRC_PIXEL *src = SRC;
    DEST_PIXEL *dst = DEST;
    unsigned int src_inc_line = SRC_INC_LINE;
    unsigned int dst_inc_line = DEST_INC_LINE;

    unsigned int h;
    register unsigned int w;

    for (h = 0; h < SRC_HEIGHT; h++)
    {
	    register SRC_PIXEL *srcX = src;
	    register DEST_PIXEL *dstX = dst;
	    for (w = 0; w < SRC_WIDTH; w++)
	    {
#ifdef INDIRECT
		    *dstX++ = INDIRECT[*srcX];
#else
		    *dstX++ = *srcX;
#endif
		    srcX += SRC_INC;
	    }
	    src += src_inc_line;
	    dst += dst_inc_line;
    }
}
