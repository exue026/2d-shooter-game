#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Target.h"
#include "Weapon.h"
#include "constants.h"

using namespace std;

#ifndef _VIEW
#define _VIEW
class View {
  public:
    View();
    void drawWelcome();
    void drawLoading(int lvlNum);
    void drawPause(int i, int score);
    void drawInventory(int cursorY, int inventoryPage, vector<Weapon>&weapons);
    void drawGameEnd(int score);
    void drawPlayer(Player player);
    void drawBullet(Bullet bullet);
    void drawTarget(Target target);
    void drawBulletCount(int bulletsRemaining);
    void clearBuffer();
    void update();
};
#endif
