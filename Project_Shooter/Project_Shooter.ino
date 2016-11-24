#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#include "Player.h"
#include "Controller.h"
#include "constants.h"

Controller gameController;
const int screenHeight = 32;
const int screenWidth = 138;
const int maxRow = 3;
const int buttonNum = 4;
const int switchNum = 2;
int buttonsState[buttonNum];
const uint32_t physicalButtons[buttonNum] = {PE_0 , PD_2, PF_4, PF_0}; //corresponds with buttons up, down, left, right
const uint32_t physicalSwitches[switchNum] = {PA_6, PA_7};        //corresponds with switch left, right


void inputInit() {
  for (int i = 0; i < buttonNum; i++) {
    buttonsState[i] = 0;
    if (physicalButtons[i] == PF_4)
      pinMode(physicalButtons[i], INPUT_PULLUP);
    else
      pinMode(physicalButtons[i], INPUT);
  }

  for (int i = 0; i < switchNum; i++) {
    pinMode(physicalSwitches[i], INPUT);
  }
}

void inputTick() {
  for (int i = 0; i < buttonNum; i++) {
    bool previousState = buttonsState[i];
    buttonsState[i] = digitalRead(physicalButtons[i]);
    gameController.setButton(i, !previousState && buttonsState[i]);
  }

  for (int i = 0; i < switchNum; i++) {
    gameController.setSwitch(i, digitalRead(physicalSwitches[i]));
  }
}
int test;
void setup() {
  // put your setup code here, to run once:
  OrbitOledInit();
  inputInit();
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputTick();
  gameController.gameTick();
  test =rand() % 3;
  Serial.println(gameController.get());
}

