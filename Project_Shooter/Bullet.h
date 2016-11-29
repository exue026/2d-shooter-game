#ifndef BULLET_H
#define BULLET_H

class Bullet {
  private:
    int rowNum;
    double xpos;
    double nextXpos;
    double ypos;
    double xspeed;

  public:
    Bullet(int rowNum, int playerXpos, int playerYpos, int playerSize, double bulletSpeed);
    void update();
    int getRow();
    double getX();
    double getY();
    double getNextX();
};
#endif

