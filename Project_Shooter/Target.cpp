#include "Target.h"
#include "constants.h"

Target::Target(int playerYpos, int levelNum) {
  this->ypos = playerYpos;
  this->xpos = screenWidth;
  this->xspeed = levelNum * 2;
}

void Target::update() {
  this->xpos -= this->xspeed;
  this->nextXpos = this->xpos - this->xspeed;
}

double Target::getX() {
  return this->xpos;
}

double Target::getY() {
  return this->ypos;
}

double Target::getNextX() {
  return this->nextXpos;
}
