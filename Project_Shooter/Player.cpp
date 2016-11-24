#include "Player.h"
#include "constants.h"

Player::Player() {
  xpos = 2;
  yspeed = screenHeight / maxRow;
  sideLength = 0.6 * yspeed;
  ypos = screenHeight % maxRow / 2 + (yspeed - sideLength) / 2 + 1;
  rowNum = 0;
}

void Player::moveUp() {
  if (ypos - yspeed >= 0) {
    ypos -= yspeed;
    rowNum--;
  }
}

void Player::moveDown() {
  if (ypos + yspeed <= screenHeight) {
    ypos += yspeed;
    rowNum++;
  }
}

int Player::getX() {
  return xpos;
}

int Player::getY() {
  return ypos;
}

int Player::getSize() {
  return sideLength;
}

int Player::getRow(){
  return rowNum;
}
