#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#include "Player.h"
#include "constants.h"

const int screenHeight=32;
const int screenWidth=138;
const int maxRow=3;

void setup() {
  // put your setup code here, to run once:
  OrbitOledInit();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  OrbitOledMoveTo(0, 0);
  OrbitOledClear();
  //OrbitOledClearBuffer();
  OrbitOledDrawString("Hello World.");

  OrbitOledUpdate();
}

