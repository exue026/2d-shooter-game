#ifndef _PLAYER
#define _PLAYER
class Player {
  private:
    int xpos;
    int ypos;
    int yspeed;
    int sideLength;
    int rowNum;
    int score;

  public:
    Player();
    int getX();
    int getY();
    int getSize();
    int getRow();
    int getScore();
    int addScore(int increment);
    void moveUp();
    void moveDown();
};
#endif
