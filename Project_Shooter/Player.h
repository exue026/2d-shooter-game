#ifndef _PLAYER
#define _PLAYER
class Player {
  private:
    int xpos;
    int ypos;
    int yspeed;
    int sideLength;
    int rowNum;

  public:
    Player();
    int getX();
    int getY();
    int getSize();
    int getRow();
    void moveUp();
    void moveDown();
};
#endif
