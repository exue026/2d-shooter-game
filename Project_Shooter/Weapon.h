#include <string>

#ifndef WEAPON_H
#define WEAPON_H
class Weapon {
  private:
    int rpm, magSize;
    double velocity;
    int bulletsRemaining;
    int scoreUnlocked;
    bool state;

  public:
    Weapon(int rpm, int magSize, double velocity, char *name, int scoreUnlocked);
    int getRpm();
    int getMagSize();
    double getVelocity();
    char *getName(); //not used
    char *name; //placed in public for now
    void setBulletsRemaining(int bulletsRemaining);
    void decreaseBullets();
    int getBulletsRemaining();
    int getScoreUnlocked();
    void setState(bool state);
    bool isUnlocked();
};
#endif
