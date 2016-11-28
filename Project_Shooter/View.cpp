#include <stdio.h>
#include <cstring>
#include "View.h"
#include "constants.h"
#include <math.h>


View::View() {
  OrbitOledInit();
}

void View::drawWelcome() {
  
    for (int i = 5; i < screenWidth - 10; i+=10) {
      OrbitOledMoveTo(i, 5);
      OrbitOledDrawString("~");
      OrbitOledMoveTo(i, screenHeight - 7);
      OrbitOledDrawString("~");
    }
  
  OrbitOledMoveTo(screenWidth / 4 + 2, screenHeight / 2);
  OrbitOledDrawString("Welcome");
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

  for (int k = 2; k > 0; k--) {
    if (k == 2) 
      OrbitOledMoveTo(screenWidth / 6, 10);
    else 
      OrbitOledMoveTo(screenWidth / 6, 10 + screenHeight / 3);
      
    if (weapons[(inventoryPage * 2) - k].isUnlocked()) {
    OrbitOledDrawString(weapons[(inventoryPage * 2) - k].name);
    OrbitOledMoveTo(screenWidth - 65, k == 2? 10 : 10 + screenHeight / 3);
    OrbitOledDrawString("#");
    int digits = weapons[(inventoryPage * 2) - k].getBulletsRemaining() > 0? (int) log10 ((double) weapons[(inventoryPage * 2) - k].getBulletsRemaining()) + 1 : 1;
    char ammunition[digits]; 
    sprintf(ammunition, "%d", weapons[(inventoryPage * 2) - k].getBulletsRemaining());
    OrbitOledDrawString(ammunition);
    }
  }
 /* 
  OrbitOledMoveTo(screenWidth / 6, 10);
  if (weapons[(inventoryPage * 2) - 2].isUnlocked()) {
    OrbitOledDrawString(weapons[(inventoryPage * 2) - 2].name);
    OrbitOledMoveTo(screenWidth - 65, 10);
    OrbitOledDrawString("#");
    int digits = weapons[(inventoryPage * 2) - 2].getBulletsRemaining() > 0? (int) log10 ((double) weapons[(inventoryPage * 2) - 2].getBulletsRemaining()) + 1 : 1;
    char ammunition[digits]; 
    sprintf(ammunition, "%d", weapons[(inventoryPage * 2) - 2].getBulletsRemaining());
    OrbitOledDrawString(ammunition);
  }
  OrbitOledMoveTo(screenWidth / 6, 10 + screenHeight / 3);
  if (weapons[(inventoryPage * 2) - 1].isUnlocked()) {
    OrbitOledDrawString(weapons[(inventoryPage * 2) - 1].name);
    OrbitOledMoveTo(screenWidth - 65, 10 + screenHeight / 3);
    OrbitOledDrawString("#");
    int digits = weapons[(inventoryPage * 2) - 1].getBulletsRemaining() > 0? (int) log10 ((double) weapons[(inventoryPage * 2) - 1].getBulletsRemaining()) + 1 : 1;
    char ammunition[digits]; 
    sprintf(ammunition, "%d", weapons[(inventoryPage * 2) - 1].getBulletsRemaining());
    OrbitOledDrawString(ammunition);
  }
  */
  OrbitOledMoveTo(0, cursorY);
  OrbitOledDrawString("->");
  
}

void View::drawGameEnd(int score) {

  OrbitOledMoveTo(screenWidth / 5, 0);
  OrbitOledDrawString("Game Over!!");
  OrbitOledMoveTo(0, 15);
  OrbitOledDrawString("Final score: ");
  int digits = score > 0 ? (int) log10 ((double) score) + 1 : score < 0? (int) log10 ((double) -score) + 1 : 1;
  char finalScore[digits];
  sprintf(finalScore, "%d", score);
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
  int digits = bulletsRemaining > 0? (int) log10 ((double) bulletsRemaining) + 1 : 1;
  char count[digits]; 
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
