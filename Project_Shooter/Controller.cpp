#include <math.h>
#include "Controller.h"
#include "constants.h"
#include <string.h>

static enum Pages {
  Welcome,
  Loading,
  Game,
  Pause,
  Inventory,
  GameResult,
} currentPage = Welcome;


Controller::Controller() {
  lvlNum = 0;
  spawnSpeed = 1800;
  timeEnterLoading = 0;
  timeLastSpawned = 0;
  timeLastFired = 0;
  timeLastDrawn = 0;
  currentTime = 0;
  inventoryPage = 1;

  for (int i = 0; i < buttonNum; i++) {
    buttonIsPressed[i] = 0;
  }
  for (int i = 0; i < switchNum; i++) {
    switchIsOn[i] = 0;
  }

  weapons.push_back(Weapon(83, 20, 0.2, "m1911", -100));  //m1911 - default gun
  weapons.push_back(Weapon(100, 29, 0.1, "ump", 20)); //ump - unlocked when score is 30
  weapons.push_back(Weapon(30, 12, 1.2, "AWP", 30)); //AWP
  weapons.push_back(Weapon(200, 40, 0.4, "AK47", 70)); //ak47
  weapons.push_back(Weapon(250, 50, 0.3, "famas", 80)); //famas
  weapons.push_back(Weapon(120, 100, 0.08,"RPK", 100)); //rpk

  selectedWeapon = &(weapons[0]);

  cursor.y = 10;
  cursor.yShift = screenHeight / 3;
}

void Controller::handlePageWelcome() {
  gameView.clearBuffer();
  gameView.drawWelcome();
  updateScreen();
  if (switchIsOn[1])
    currentPage = Loading;
}

void Controller::handlePageLoading() {
  timeEnterLoading = getTime();
  lvlNum++;
  initWeaponAmmo();
  if (spawnSpeed <= 200)
    spawnSpeed = 200;
  else
    spawnSpeed -= 200;

  targetsSpawned = 0;
  while (getTime() - timeEnterLoading <= 2000) {
    gameView.clearBuffer();
    gameView.drawLoading(lvlNum);
    updateScreen();
  }
  currentPage = Game;
}

void Controller::initWeaponAmmo() {
  for (int k = 0; k < weapons.size(); k++) {
     weapons[k].setBulletsRemaining(weapons[k].getMagSize() * lvlNum * 0.5); 
  }
}

void Controller::handlePageGame() {

  unlockWeapons();
  
  //check input
  if (buttonIsPressed[0])
    myPlayer.moveUp();
  if (buttonIsPressed[1])
    myPlayer.moveDown();
  if (buttonIsPressed[2])
    fireBullet((*selectedWeapon).getRpm(), (*selectedWeapon).getVelocity());
  if (!switchIsOn[1]) {
    timeFlashDrawn = getTime();
    currentPage = Pause;
  }

  //check if needs to spawn target
  if (targetsSpawned < lvlNum * 10 && (timeLastSpawned == 0 || currentTime - timeLastSpawned >= spawnSpeed)) {
    targets.push_back(Target(lvlNum));
    targetsSpawned++;
    timeLastSpawned = getTime();
  }

  //draw and update target and bullet positions
  
  gameView.clearBuffer();
  for (int i = 0; i < targets.size(); i++) {
    targets[i].update();
    gameView.drawTarget(targets[i]);
  }
  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].update();
    gameView.drawBullet(bullets[i]);
  }

  gameView.drawBulletCount((*selectedWeapon).getBulletsRemaining());

  //draw player, target, and bullets, and bullet counter
  gameView.drawPlayer(myPlayer);
  updateScreen();

  detectCollision();

  if (targets.size() == 0 && targetsSpawned >= lvlNum * 10) {
    currentPage = Loading;
  }
}

void Controller::handlePagePause() {
  currentTime = getTime();
  if (currentTime - timeFlashDrawn >= 3000)
    timeFlashDrawn = currentTime;
  gameView.clearBuffer();
  gameView.drawPause(currentTime - timeFlashDrawn <= 2000, myPlayer.getScore());
  updateScreen();
  if (switchIsOn[0] && !switchIsOn[1]) {
    currentPage = Inventory;
  }
  if (!switchIsOn[0] && switchIsOn[1])
    currentPage = Game;
}

void Controller::handlePageInventory() {
 
  updateCursor();
  gameView.clearBuffer();
  gameView.drawInventory(cursor.y, inventoryPage, weapons);
  updateScreen();
  if (!switchIsOn[0] && !switchIsOn[1]) {
    currentPage = Pause;
  }
}

void Controller::unlockWeapons() {
  for(int k = 0; k < weapons.size(); k++) {
    if (myPlayer.getScore() >= weapons[k].getScoreUnlocked() && !weapons[k].isUnlocked()) {
      weapons[k].setState(true);
    }
  }
}

void Controller::updateCursor() {

  if (buttonIsPressed[0]) {
    if (cursor.y - cursor.yShift >= 10) {
      cursor.y -= cursor.yShift;
      selectedWeapon--;
    }
    else if (inventoryPage != 1) {
        inventoryPage--;
        cursor.y = 10 + cursor.yShift;
        selectedWeapon--;
    }
  }
  if (buttonIsPressed[1] && ((strcmp((*selectedWeapon).name, weapons[weapons.size()-1].name) == 0) || ((*(selectedWeapon + 1)).isUnlocked()))) {
    if (cursor.y + cursor.yShift <= 10 + cursor.yShift) {
      cursor.y += cursor.yShift;
      selectedWeapon++;
    }
    else if (inventoryPage != 3) {
        inventoryPage++;
        cursor.y = 10;
        selectedWeapon++;
    }
  }
}

void Controller::handlePageGameResult() {
  gameView.clearBuffer();
  gameView.drawGameEnd(myPlayer.getScore());
  gameView.update();
  if (!switchIsOn[1]) {
    currentPage = Welcome;
  }
}

void Controller::detectCollision() {
  //detect if bullet exits right side of screen
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].getNextX() >= screenWidth) {
      bullets.erase(bullets.begin() + i);
    }
  }
  //detects if target exits left side of screen
  for (int i = 0; i < targets.size(); i++) {
    if (targets[i].getNextX() < 0) {
      targets.erase(targets.begin() + i);
      currentPage = GameResult;
      return;
    }
  }
  //detect if bullet collides with a target
  for (int i = 0; i < bullets.size(); i++) {
    for (int k = 0; k < targets.size(); k++) {
      if ((bullets[i].getRow() == targets[k].getRow()) && (bullets[i].getNextX() >= targets[k].getNextX())) {
        bullets.erase(bullets.begin() + i);
        targets.erase(targets.begin() + k);
        myPlayer.addScore(scorePerTarget);
      }
    }
  }
}

void Controller::fireBullet(int rpm, double velocity) {

  currentTime = getTime();
  if ((currentTime - timeLastFired >= ((60 * 1000) / rpm)) && (*selectedWeapon).getBulletsRemaining() > 0) {
    (*selectedWeapon).decreaseBullets();
    bullets.push_back(Bullet(myPlayer.getRow(), myPlayer.getX(), myPlayer.getY(), myPlayer.getSize(), velocity));
    timeLastFired = getTime();

    if (scorePerBullet(lvlNum) <= -1)
      myPlayer.addScore(scorePerBullet(lvlNum));
    else
      myPlayer.addScore(minScorePerBullet);
  }
}

void Controller::updateScreen() {
  currentTime = getTime();
  if (timeLastDrawn == 0 || currentTime - timeLastDrawn > 33) {
    gameView.update();
  }
}

int Controller::scorePerBullet(int lvlNum) {
  return (int)sqrt(0.75 * lvlNum) - 4.0;
}



void Controller::gameTick() {
  switch (currentPage) {
    case Welcome:
      handlePageWelcome();
      break;
    case Loading:
      handlePageLoading();
      break;
    case Game:
      handlePageGame();
      break;
    case Pause:
      handlePagePause();
      break;
    case Inventory:
      handlePageInventory();
      break;
    case GameResult:
      handlePageGameResult();
      break;
  }
}

void Controller::setButton(int i, bool value) {
  buttonIsPressed[i] = value;
}

void Controller::setSwitch(int i, bool value) {
  switchIsOn[i] = value;
}

