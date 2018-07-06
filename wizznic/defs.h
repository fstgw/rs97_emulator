#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define FIELDSIZE 11

//Icon bricks
#define BRICKSBEGIN 1
#define BRICKSEND 5

//Tiles
#define STD 6
//Moving platforms (from levelfile)
#define MOVERVERT 7
#define MOVERHORIZ 8
#define MOVERCOUNTDOWN 1000

#define NUMTILES 9

//Blocker, reserve space for moving bricks
#define RESERVED 9

#define DIRLEFT -1
#define DIRRIGHT 1

#define DIRUP -1
#define DIRDOWN 1

//Board
#define brickSize 20
#define boardOffsetX 90
#define boardOffsetY 10
#define NOBLOCK 0
#define DOBLOCK 1
#define CURLOCK 2

//Speeds
#define CURSORMOVESPEED 5
#define VERTMOVERSPEED 1
#define HORIZMOVERSPEED 1
#define FALLINGSPEED 2
//Delays
#define REPEATDELAY 350

#endif // DEFS_H_INCLUDED
