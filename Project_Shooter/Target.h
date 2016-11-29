#include <cstdlib>
#include "constants.h"

#ifndef TARGET_H
#define TARGET_H

class Target {
  private:
    int rowNum;
    double xpos;
    double nextXpos;
    double ypos;
    double xspeed;

  public:
    Target(int levelNum);
    void update();
    int getRow();
    double getX();
    double getY();
    double getNextX();
};
#endif
