#ifndef _TARGET
#define _TARGET
class Target {
  private:
    double xpos;
    double nextXpos;
    double ypos;
    double xspeed;

  public:
    Target(int playerYpos, int levelNum);
    void update();
    double getX();
    double getNextX();
    double getY();
};
#endif
