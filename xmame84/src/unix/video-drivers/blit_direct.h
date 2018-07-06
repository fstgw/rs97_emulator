{
    int src_width = (((SRC_PIXEL *)bitmap->line[1]) - ((SRC_PIXEL *)bitmap->line[0]));
    SRC_PIXEL *line_src = (SRC_PIXEL *)bitmap->line[visual.min_y]   + visual.min_x;
    SRC_PIXEL *line_end = (SRC_PIXEL *)bitmap->line[visual.max_y+1] + visual.min_x;
    DEST_PIXEL *line_dest = (DEST_PIXEL *)(DEST);

    for (;line_src < line_end; line_dest+=DEST_WIDTH, line_src+=src_width)
	MEMCPY(line_src, line_src+visual_width, line_dest)
}

