// Generic function to perform no-rotation blit
// Copies 8 pixels per loop pass
// This blitter does no scaling
void MY_FUNCTION (struct mame_bitmap *bitmap)
{
    SRC_PIXEL *src = SRC;
    DEST_PIXEL *dst = DEST;
    unsigned int src_inc_line = SRC_INC_LINE;
    unsigned int dst_inc_line = DEST_INC_LINE;
    unsigned int h;

    if (INDIRECT)
	{
		for (h = SRC_HEIGHT; h; h--)
		{
			register SRC_PIXEL *srcX = src;
			register DEST_PIXEL *dstX = dst;
#if 1
			clut16to16_rot0(dstX, srcX, INDIRECT, SRC_WIDTH);
#else
			register SRC_PIXEL *srcEnd = srcX + SRC_WIDTH;
			while (srcX < srcEnd)
			{
				dstX[0] = INDIRECT[srcX[0]];
				dstX[1] = INDIRECT[srcX[1]];
				dstX[2] = INDIRECT[srcX[2]];
				dstX[3] = INDIRECT[srcX[3]];
				dstX[4] = INDIRECT[srcX[4]];
				dstX[5] = INDIRECT[srcX[5]];
				dstX[6] = INDIRECT[srcX[6]];
				dstX[7] = INDIRECT[srcX[7]];
				srcX += 8;
				dstX += 8;
			}
#endif
			src += src_inc_line;
			dst += dst_inc_line;
		}
	}
    else
	{
		for (h = SRC_HEIGHT; h; h--)
		{
			register SRC_PIXEL *srcX = src;
			register DEST_PIXEL *dstX = dst;
#if 1
			memcpy(dstX, srcX, (SRC_WIDTH*sizeof(SRC_PIXEL)));
#else
			register SRC_PIXEL *srcEnd = srcX + SRC_WIDTH;
			while (srcX < srcEnd)
			{
				dstX[0] = srcX[0];
				dstX[1] = srcX[1];
				dstX[2] = srcX[2];
				dstX[3] = srcX[3];
				dstX[4] = srcX[4];
				dstX[5] = srcX[5];
				dstX[6] = srcX[6];
				dstX[7] = srcX[7];
				srcX += 8;
				dstX += 8;
			}
#endif
			src += src_inc_line;
			dst += dst_inc_line;
		}
	}
}
