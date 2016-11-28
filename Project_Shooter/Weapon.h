#include <string>

#ifndef _WEAPON
#define _WEAPON

class Weapon {
  private:
    int rpm, magSize;
    double velocity;
    int bulletsRemaining;
    int scoreUnlock;

  public:
    Weapon(int rpm, int magSize, double velocity, char *name, int scoreUnlock);
    int getRpm();
    int getMagSize();
    double getVelocity();
    char *getName(); //not used
    char *name; //placed in public for now
    int scoreUnlocked();
    void setBulletsRemaining(int bulletsRemaining);
    void decreaseBullets();
    int getBulletsRemaining();
};
#endif
