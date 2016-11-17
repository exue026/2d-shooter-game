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
#include "constants.h"

using namespace std;

#ifndef _VIEW
#define _VIEW
class View {
  public:
    View();
    void drawPlayer(Player player);
    void drawBullets(vector<Bullet> bullet);
    void drawTargets(vector<Target> target);
};
#endif
