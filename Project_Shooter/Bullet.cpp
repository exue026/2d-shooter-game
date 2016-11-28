#include "Bullet.h"

Bullet::Bullet(int rowNum, int playerXpos, int playerYpos, int playerSize, double bulletSpeed) {
  
  this->rowNum = rowNum;
  xpos = playerXpos + playerSize;
  ypos = playerYpos + playerSize / 2;
  xspeed = bulletSpeed;
}

void Bullet::update() {
  xpos += xspeed;
  nextXpos = xpos + xspeed;
}

int Bullet::getRow() {
  return rowNum;
}

double Bullet::getX() {
  return xpos;
}

double Bullet::getY() {
  return ypos;
}

double Bullet::getNextX() {
  return nextXpos;
}
