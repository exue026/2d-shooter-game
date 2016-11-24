#include "Target.h"
#include "constants.h"
#include <cstdlib>

Target::Target(int levelNum) {
  int rowNum = (rand() % 3); //random not working properly yet
  int yspeed = screenHeight / maxRow;
  int sideLength = 0.6 * yspeed;
  int startingPos = screenHeight % maxRow / 2 + (yspeed - sideLength) / 2 + 1;
  ypos = startingPos + yspeed * rowNum;
  xpos = screenWidth - 18;
  xspeed = levelNum * 0.02;
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
