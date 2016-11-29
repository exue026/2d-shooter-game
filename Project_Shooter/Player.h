#include "constants.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
  private:
    int xpos;
    int ypos;
    int yspeed;
    int sideLength;
    int rowNum;
    int score;
    int specialPower;
    int killCount;

  public:
    Player();
    int getX();
    int getY();
    int getSize();
    int getRow();
    int getScore();
    int getSpecialPower();
    int getKillCount();
    int addScore(int increment);
    int addSpecialPower(int increment);
    void moveUp();
    void moveDown();
    void resetVariables();
};
#endif
