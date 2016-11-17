#include "Bullet.h"

Bullet::Bullet(int playerXpos, int playerYpos, int bulletSpeed) {
  this->xpos = playerXpos;
  this->ypos = playerYpos;
  this->xspeed = bulletSpeed;
}

void Bullet::update() {
  this->xpos += this->xspeed;
  this->nextXpos = this->xpos + this->xspeed;
}

double Bullet::getX() {
  return this->xpos;
}

double Bullet::getY() {
  return this->ypos;
}

double Bullet::getNextX() {
  return this->nextXpos;
}
