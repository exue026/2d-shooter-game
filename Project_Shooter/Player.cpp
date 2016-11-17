#include "Player.h"
#include "constants.h"

Player::Player() {
  this->xpos = 2;
  this->yspeed = screenHeight / maxRow;
  this->sideLength = 0.6*yspeed;
  this->ypos = screenHeight % maxRow / 2+(yspeed-sideLength)/2+1;
}

void Player::moveUp() {
  if (ypos - yspeed >= 0) ypos -= yspeed;
}

void Player::moveDown() {
  if (ypos + yspeed <= screenHeight) ypos += yspeed;
}

int Player::getX(){
  return xpos;  
}

int Player::getY(){
  return ypos;
}

int Player::getSize(){
  return sideLength;
}
