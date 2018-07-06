void MY_FUNCTION (struct mame_bitmap *bitmap)
{
  unsigned int accAddX = ADDX;
  unsigned int accAddY = ADDY;
  unsigned int accModX = MODX;
  unsigned int accModY = MODY;
  unsigned int src_inc_line = SRC_INC_LINE;
  unsigned int src_inc = SRC_INC;
  SRC_PIXEL *src = SRC;
  DEST_PIXEL *dst = DEST;

  int accumulatorY = 0;
  unsigned int h;
  
  for (h = 0; h < SRC_HEIGHT; h++)
  {
    DEST_PIXEL pixel = 0;
    DEST_PIXEL *dstX=dst;
    SRC_PIXEL *srcX=src;
    int accumulatorX = 0;

    accumulatorY += accAddY;
    if (accumulatorY >= accModY || h == SRC_HEIGHT - 1)
    {
      accumulatorY -= accModY;
      int w;
      
      for (w = SRC_WIDTH - 1; w >= 0; w--)
      {
        DEST_PIXEL mixPixel = INDIRECT[*srcX];
	srcX+=src_inc;
        if (accumulatorX >= accAddX)
        {
          mixPixel = DESTMIX(pixel, mixPixel);
        }
        pixel = mixPixel;
    
        accumulatorX += accAddX;
        if (accumulatorX >= accModX || w == 0)
        {
          *dstX++ = pixel;
          accumulatorX -= accModX;
        }
      }
      dst += DEST_WIDTH;
    }

    src += src_inc_line;
  }
}
