#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#include <math.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Target.h"
#include "Weapon.h"
#include "constants.h"

#ifndef VIEW_H
#define VIEW_H

class View {
  public:
    View();
    void drawWelcome();
    void drawCalib(int calibProgress);
    void drawLoading(int lvlNum);
    void drawPause(int i, int score);
    void drawInventory(int cursorY, int inventoryPage, int spCount, std::vector<Weapon>&weapons);
    void drawGameEnd(int score);
    void drawPlayer(Player player);
    void drawTarget(Target target);
    void drawBullet(Bullet bullet);
    void drawBulletCount(int bulletsRemaining);
    void clearBuffer();
    void update();
};
#endif
