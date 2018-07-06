#ifndef LEVELS_H_INCLUDED
#define LEVELS_H_INCLUDED

struct levelInfo_s
{
  char file[64];
  char imgFile[32];
  char author[32];
  int time;
};
typedef struct levelInfo_s levelInfo_t;

void makeLevelList();

//char* levelFile(int num);
//char* levelImgFile(int num);
//int levelTime(int num);

levelInfo_t* levelInfo(int num);

int getNumLevels();


char* userLevelFile(int num);
int getNumUserLevels();

#endif // LEVELS_H_INCLUDED
