#include "Target.h"

Target::Target(int levelNum) {
  
  rowNum = (rand() % 3);
  int yspeed = ScreenHeight / MaxRow;
  int sideLength = 0.6 * yspeed;
  int startingPos = ScreenHeight % MaxRow / 2 + (yspeed - sideLength) / 2 + 1;
  ypos = startingPos + yspeed * rowNum;
  xpos = ScreenWidth - 18;
  xspeed = 0.02 + levelNum * 0.02;
  nextXpos = xpos - xspeed;
}

void Target::update() {
  xpos -= xspeed;
  nextXpos = xpos - xspeed;
}

int Target::getRow() {
  return rowNum;
}

double Target::getX() {
  return xpos;
}

double Target::getY() {
  return ypos;
}

double Target::getNextX() {
  return nextXpos;
}
