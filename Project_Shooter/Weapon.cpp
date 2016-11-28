#include "Weapon.h"


Weapon::Weapon(int rpm, int magSize, double velocity, char *name, int scoreUnlocked) {
  this->rpm = rpm;
  this->magSize = magSize;
  this->velocity = velocity;
  this->name = name;
  this->scoreUnlocked = scoreUnlocked;
  this->state = false;
}

int Weapon::getRpm() {
  return rpm;
}

int Weapon::getMagSize() {
  return magSize;
}

double Weapon::getVelocity() {
  return velocity;
}

void Weapon::setBulletsRemaining(int bulletsRemaining) {
  this->bulletsRemaining = bulletsRemaining;
}

void Weapon::decreaseBullets() {
  if (bulletsRemaining > 0) {
    bulletsRemaining--;
  }
}

int Weapon::getBulletsRemaining() {
  return bulletsRemaining;
}

int Weapon::getScoreUnlocked() {
  return scoreUnlocked;
}

void Weapon::setState(bool state) {
  this->state = state;
}
bool Weapon::isUnlocked() {
  return state;
}
/* isn't working
char* Weapon::getName() {
  return name;
}
*/

