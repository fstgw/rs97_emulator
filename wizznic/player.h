#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

struct player_s {
  int bestScore; //Best score of all time
  int bestLevel; //Highest level achieved of all time

  int gameOver; //If 1, menu will reset to "New Game", else, it will go to stats screen.
  int finishedLevel;
  int level;
  int boardScore;
  int gameScore;
  int lives;
  int retries;
  char* levelFile;
  int paused;
};
typedef struct player_s player_t;

void initPlayer();
player_t* player();
void savePlayer(); //Saves level and/or score if they are better

#endif // PLAYER_H_INCLUDED
