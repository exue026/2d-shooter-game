#include <stdio.h>
#include <cstring>
#include "View.h"
#include "constants.h"



View::View() {
  OrbitOledInit();
}

void View::drawWelcome() {
  OrbitOledMoveTo(screenWidth / 4, screenHeight / 2);
  OrbitOledDrawString("Welcome!!");
}

void View::drawLoading(int lvlNum) {
  char msg[9 + lvlNum / 10];
  char lvl[2 + lvlNum / 10];
  sprintf(lvl, "%d", lvlNum);
  strcpy(msg, "Level: ");
  strcat(msg, lvl);
  OrbitOledMoveTo(screenWidth / 4, screenHeight / 3);
  OrbitOledDrawString(msg);
}


void View::drawPause(int i, int score) {
  OrbitOledMoveTo(screenWidth / 6, 0);
  if (i)
    OrbitOledDrawString("Game Paused");
  OrbitOledMoveTo(screenWidth / 5, screenHeight - 22);
  char scoreMsg[9 + score / 10];
  char scoreStr[2 + score / 10];
  sprintf(scoreStr, "%d", score);
  strcpy(scoreMsg, "Score: ");
  strcat(scoreMsg, scoreStr);
  OrbitOledDrawString(scoreMsg);
  OrbitOledMoveTo(0, screenHeight - 10);
  OrbitOledDrawString("S1 for Inventory");
}

void View::drawInventory(int cursorY, int inventoryPage, vector<Weapon>&weapons) {
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Inventory");

  OrbitOledMoveTo(screenWidth / 4, 10);
  if (inventoryPage == 1 && weapons[0].isUnlocked()) {
    OrbitOledDrawString(weapons[0].name);
  }
  else if (inventoryPage == 2 && weapons[2].isUnlocked()) {
    OrbitOledDrawString(weapons[2].name);
  }
  else {
    if (weapons[4].isUnlocked()) {
      OrbitOledDrawString(weapons[4].name);
    }
  }
  OrbitOledMoveTo(screenWidth / 4, 10 + screenHeight / 3);
  if (inventoryPage == 1 && weapons[1].isUnlocked()) {
    OrbitOledDrawString(weapons[1].name);
  }
  else if (inventoryPage == 2 && weapons[3].isUnlocked()) {
    OrbitOledDrawString(weapons[3].name);
  }
  else {
    if (weapons[5].isUnlocked()) {
      OrbitOledDrawString(weapons[5].name);
    }
  }

  OrbitOledMoveTo(0, cursorY);
  OrbitOledDrawString("->");
}

void View::drawGameEnd(int score) {

  int temp = score;
  int digits = 0;
  while (temp > 0) {
    temp /= 10;
    digits++;
  }
  char finalScore[digits + 1]; //+1 for the null char
  sprintf(finalScore, "%d", score);
  OrbitOledMoveTo(screenWidth / 5, 0);
  OrbitOledDrawString("Game Over!!");
  OrbitOledMoveTo(0, 15);
  OrbitOledDrawString("Final score: ");
  OrbitOledMoveTo(screenWidth - 35, 15);
  OrbitOledDrawString(finalScore);

}

void View::drawPlayer(Player player) {
  OrbitOledMoveTo(player.getX(), player.getY());
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledFillRect(player.getX() + player.getSize(), player.getY() + player.getSize());
}

void View::drawTarget(Target target) {
  OrbitOledMoveTo(target.getX(), target.getY());
  OrbitOledDrawString("*");
}

void View::drawBullet(Bullet bullet) {
  OrbitOledMoveTo(bullet.getX(), bullet.getY());
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledFillRect(bullet.getX() + 2, bullet.getY() + 2);
}

void View::drawBulletCount(int bulletsRemaining) {
  int temp = bulletsRemaining;
  int digits = 0;
  while (temp > 0) {
    temp /= 10;
    digits++;
  }
  char count[digits + 1]; //+1 for the null char
  sprintf(count, "%d", bulletsRemaining);
  OrbitOledMoveTo(screenWidth - 30, screenHeight - 8);
  OrbitOledDrawString(count);
}

void View::clearBuffer() {
  OrbitOledClearBuffer();
}

void View::update() {
  OrbitOledUpdate();
}
