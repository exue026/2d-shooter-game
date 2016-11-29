#include <vector>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Player.h"
#include "View.h"
#include "Weapon.h"
#include "constants.h"

const int ButtonCount = 4;
const int SwitchCount = 2;

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
  private:
    View gameView;
    Player myPlayer;

    std::vector<Target>targets;
    std::vector<Bullet>bullets;
    std::vector<Weapon>weapons;
    Weapon *selectedWeapon;

    struct Cursor {
      int y;
      int yShift;
    } cursor;

    const int loadScreenWaitTime = 3000;
    const int unpauseWaitTime = 1000;
    const int flashDrawTime = 2000;
    const int flashNotDrawTime = 1000;
    const int scorePerTarget = 5;
    const int minScorePerBullet = -1;
    const int minSpawnSpeed = 400;
    const int spawnSpeedDecrement = 200;
    const int killsPerSP = 20;

    bool buttonIsPressed[ButtonCount];
    bool switchIsOn[SwitchCount];
    bool trigSP;
    bool wait;

    int calibProgress;  //keep track of the current step during calibration (setup)
    //0:Switch0 UP                            1:Switch0 DOWN
    //2:Switch1 UP                            3:Switch1 DOWN
    //4,5,6,7: Press Button0, 1, 2, 3         8:Accelerometer Calibration
    //9: Finished
    int lvlNum;
    int targetsSpawned;
    int spawnSpeed;
    int inventoryPage;

    double timeLastFired;
    double timeLastSpawned;
    double timeInvalidSpawn;
    double timeLastDrawn;
    double timeFlashDrawn;
    double timeEnterLoading;
    double timeExitPause;
    double currentTime;

    void handlePageWelcome();
    void handlePageCalibration();
    void handlePageLoading();
    void handlePageGame();
    void handlePagePause();
    void handlePageInventory();
    void handlePageGameResult();
    void initVariables();
    void initWeaponAmmo();
    void unlockWeapons();
    void clearObjects();
    void detectCollision();
    void fireBullet(int rpm, double velocity);
    void updateCursor();
    void updateScreen();

    int scorePerBullet(int lvlNum);


  public:
    Controller();
    void gameTick();
    void setSPTrig(bool value);
    void setButton(int i, bool value);
    void setSwitch(int i, bool value);
};

void LightRLED();
void LightGLED();
void Calib();
double getTime();

#endif

