#define RLED RED_LED
#define GLED GREEN_LED

#include "Controller.h"
#include "constants.h"

const int ScreenHeight = 32;
const int ScreenWidth = 138;
const int MaxRow = 3;
const int ButtonNum = 4;
const int SwitchNum = 2;

void WireInit();
void OrienInit();
void InputInit();
void OrienTick();
void InputTick();

Controller gameController;

void setup() {
  
  WireInit();
  OrbitOledInit();
  OrienInit();
  InputInit();
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
}

void loop() {
  
  OrienTick();
  InputTick();
  gameController.gameTick();
  
}

