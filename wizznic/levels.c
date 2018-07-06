#include "levels.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static listItem* levelFiles;
static listItem* userLevelFiles;
static int numUserLevels=0;
static int numLevels=0;

void makeLevelList()
{
  int i=0;
  char buf[64];

  FILE *f;
  //Init the list to hold the filenames
  levelFiles = initList();
  levelInfo_t* tl;

  //List all official levels
  while(1)
  {
    sprintf(buf, "data/levels/level%i.wzp", i);
    f = fopen(buf, "r");
    if(f)
    {

      //Add data to list
      tl=malloc(sizeof(levelInfo_t));

      //Level file name
      strcpy(tl->file, buf);

      //preview file name
      sprintf( buf, "%s.png", buf);
      strcpy(tl->imgFile, buf);

      //Level author
      fgets( buf, 32, f);
      strcpy(tl->author, buf);

      //Time
      fgets( buf, 32, f);
      tl->time=atoi(buf);

      listAddData(levelFiles, (void*)tl);

      fclose(f);
    } else {
      break;
    }
    i++;
  }
  numLevels=listSize(levelFiles);

  // Add a "Completed" level at the very end of the list
  tl=malloc(sizeof(levelInfo_t));
  sprintf( buf, "data/complete.png" );
  strcpy(tl->imgFile, buf);
  strcpy(tl->file, buf);
  tl->time=0;
  listAddData(levelFiles, (void*)tl);

  //List userlevels
  userLevelFiles = initList();
  i=0;
  while(1)
  {
    sprintf(buf, "data/userlevels/userlevel%i.wzp", i);
    f = fopen(buf, "r");
    if(f)
    {

      //Add data to list
      tl=malloc(sizeof(levelInfo_t));

      //Level file name
      strcpy(tl->file, buf);


      //preview file name
      sprintf( buf, "%s.png", buf);
      strcpy(tl->imgFile, buf);

      //Time
      fgets( buf, 32, f);
      tl->time=atoi(buf);

      //Level author
      sprintf(tl->author, "Unknown");

      listAddData(userLevelFiles, (void*)tl);

      fclose(f);
    } else {
      break;
    }
    i++;
  }
  numUserLevels=listSize(userLevelFiles);


}

levelInfo_t* levelInfo(int num)
{
  return( (levelInfo_t*)listGetItemData(levelFiles,num) );
}

/*char* levelFile(int num)
{
  if(num < numLevels)
  {
    return( ((levelInfo_t*)listGetItemData(levelFiles,num))->file );
  } else {
    return(NULL);
  }
}



char* levelImgFile(int num)
{
  return( ((levelInfo_t*)listGetItemData(levelFiles,num))->imgFile );
}

int levelTime(int num)
{
  if(num < numLevels)
  {
    return( ((levelInfo_t*)listGetItemData(levelFiles,num))->time );
  } else {
    return(0);
  }
}*/

int getNumLevels()
{
  return(numLevels);
}

// Userlevels
int getNumUserLevels()
{
  return(numUserLevels);
}

void addUserLevel(const char* fn)
{
  levelInfo_t* tl;
  listItem* l=userLevelFiles;
  //Check if it's there
  while(l=l->next)
  {
    if(strcmp( ((levelInfo_t*)l->data)->file, fn )==0)
    {
      printf("exists\n");
      return;
    }
  }


  tl=malloc(sizeof(levelInfo_t));
  strcpy(tl->file, fn);
  tl->time=360;
  listAddData(userLevelFiles, (void*)tl);
  numUserLevels=listSize(userLevelFiles);
}

char* userLevelFile(int num)
{
  if(num < numUserLevels)
  {
    return( ((levelInfo_t*)listGetItemData(userLevelFiles,num))->file );
  } else {
    return(NULL);
  }
}
