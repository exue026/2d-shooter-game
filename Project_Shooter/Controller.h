#include <vector>
#include <time.h>
#include "Player.h"
#include "View.h"
#include "constants.h"
#include "Weapon.h"


#ifndef _CONTROLLER
#define _CONTROLLER
class Controller {
  private:
    View gameView;
    Player myPlayer;
    std::vector<Target>targets;
    std::vector<Bullet>bullets;
    std::vector<Weapon>weapons;
    Weapon *selectedWeapon;

    const int scorePerTarget = 5;
    const int minScorePerBullet = -1;

    bool buttonIsPressed[4];
    bool switchIsOn[2];

    int lvlNum;
    int targetsSpawned;
    int spawnSpeed;
    int scorePerBullet(int lvlNum);
    int inventoryPage;
   

    double timeLastSpawned;
    double timeLastDrawn;
    double timeFlashDrawn;
    double timeEnterLoading;
    double currentTime;
    double timeLastFired;

    void handlePageWelcome();
    void handlePageLoading();
    void handlePageGame();
    void handlePagePause();
    void handlePageInventory();
    void handlePageGameResult();
    void detectCollision();
    void fireBullet(int rpm, double velocity);
    void updateScreen();
    void updateCursor();
    void initWeaponAmmo();
    void unlockWeapons();
    
    struct Cursor {
      int y;
      int yShift;
    };

    struct Cursor cursor;
     
  public:
    Controller();
    void gameTick();
    void setButton(int i, bool value);
    void setSwitch(int i, bool value);

    //test functions
    int get();
};

double getTime();
#endif
