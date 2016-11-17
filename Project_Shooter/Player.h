#ifndef _PLAYER
#define _PLAYER
class Player {
  private:
    int xpos;
    int ypos;
    int yspeed;
    int sideLength;

  public:
    Player();
    int getX();
    int getY();
    int getSize();
    void moveUp();
    void moveDown();
};
#endif
