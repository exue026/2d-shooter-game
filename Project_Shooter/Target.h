#ifndef _TARGET
#define _TARGET
class Target {
  private:
    int rowNum;
    double xpos;
    double nextXpos;
    double ypos;
    double xspeed;

  public:
    Target(int levelNum);
    int getRow();
    void update();
    double getX();
    double getNextX();
    double getY();
};
#endif
