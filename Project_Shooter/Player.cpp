#include "Player.h"

Player::Player() {
  xpos = 2;
  yspeed = ScreenHeight / MaxRow;
  sideLength = 0.6 * yspeed;
  ypos = ScreenHeight % MaxRow / 2 + (yspeed - sideLength) / 2 + 1;
  rowNum = 0;
  score = 0;
  specialPower = 0;
  killCount = 0;
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

int Player::getRow() {
  return rowNum;
}

int Player::getScore() {
  return score;
}

int Player::getSpecialPower() {
  return specialPower;
}

int Player::getKillCount() {
  return killCount;
}

int Player::addScore(int increment) {
  score += increment;

  //if increment is positive, a target was killed.  Thus, increase kills count.
  if (increment > 0)
    killCount++;
}

int Player::addSpecialPower(int increment) {
  specialPower += increment;
}

void Player::moveUp() {
  if (ypos - yspeed >= 0) {
    ypos -= yspeed;
    rowNum--;
  }
}

void Player::moveDown() {
  if (ypos + yspeed <= ScreenHeight) {
    ypos += yspeed;
    rowNum++;
  }
}

void Player::resetVariables() {
  xpos = 2;
  yspeed = ScreenHeight / MaxRow;
  sideLength = 0.6 * yspeed;
  ypos = ScreenHeight % MaxRow / 2 + (yspeed - sideLength) / 2 + 1;
  rowNum = 0;
  score = 0;
  specialPower = 0;
  killCount = 0;
}

