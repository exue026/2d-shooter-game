#include "Weapon.h"

Weapon::Weapon(int rpm, int magSize, double velocity, double reloadSpeed) {
  this->rpm = rpm;
  this->magSize = magSize;
  this->velocity = velocity;
  this->reloadSpeed = reloadSpeed;
  active = false;
}

void Weapon::setActive(bool value) {
  active = value;
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

double Weapon::getReloadSpeed() {
  return reloadSpeed;
}
