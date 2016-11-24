#ifndef _WEAPON
#define _WEAPON
class Weapon {
  private:
    int rpm, magSize;
    double velocity, reloadSpeed;
    bool active;

  public:
    Weapon(int rpm, int magSize, double velocity, double reloadSpeed);
    void setActive(bool value);
    int getRpm();
    int getMagSize();
    double getVelocity();
    double getReloadSpeed();
};
#endif
