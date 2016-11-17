#ifndef _BULLET
#define _BULLET
class Bullet {
private:
  double xpos;
  double nextXpos;
  double ypos;
  double xspeed;

public:
  Bullet(int playerXpos, int playerYpos, int bulletSpeed);   
  void update();
  double getX();
  double getY();
  double getNextX();
};
#endif
