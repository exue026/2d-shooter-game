#include <vector>
#include "Player.h"
#include "View.h"
#include "constants.h"

#ifndef _CONTROLLER
#define _CONTROLLER
class Controller {
  private:
    View gameView;
    Player myPlayer;
    vector<Target>targets;
    vector<Bullet>bullets;

    bool buttonIsPressed[4];
    bool switchIsOn[2];
    int lvlNum;
    int counter;//var used to test program, pls delete after use (current status: still in use)

    void handlePageWelcome();
    void handlePageLoading();
    void handlePageGame();
    void handlePagePause();
    void handlePageInventory();
    void handlePageGameResult();
    void detectCollision();


  public:
    Controller();
    void gameTick();
    void setButton(int i, bool value);
    void setSwitch(int i, bool value);

    //test functions
    int get();
};
#endif