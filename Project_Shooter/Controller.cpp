#include "Controller.h"

static enum Pages {
  Welcome,
  Calibration,
  Loading,
  Game,
  Pause,
  Inventory,
  GameResult,
} currentPage = Welcome;

Controller::Controller() {
  
  for (int i = 0; i < ButtonNum; i++) {
    buttonIsPressed[i] = 0;
  }
  for (int i = 0; i < SwitchNum; i++) {
    switchIsOn[i] = 0;
  }

  weapons.push_back(Weapon(83, 22, 0.1, "m1911", -100));
  weapons.push_back(Weapon(90, 35, 0.2, "ump", 40));
  weapons.push_back(Weapon(30, 12, 1.2, "AWP", 160));
  weapons.push_back(Weapon(200, 40, 0.4, "AK47", 250));
  weapons.push_back(Weapon(250, 50, 0.3, "famas", 500));
  weapons.push_back(Weapon(300, 2, 1.4, "OPgun", 800));

  initVariables();
}

void Controller::handlePageWelcome() {
  
  gameView.clearBuffer();
  gameView.drawWelcome();
  updateScreen();
  if (buttonIsPressed[1])
    currentPage = Calibration;
}

void Controller::handlePageCalibration() {
  
  if ((calibProgress <= 3 && !(calibProgress % 2) == switchIsOn[calibProgress / 2]) ||
      (calibProgress > 3 && calibProgress <= 7 && buttonIsPressed[calibProgress - 4]) ||
      (calibProgress > 7 && buttonIsPressed[0]))
    calibProgress++;
  if (calibProgress == 8 && buttonIsPressed[0])
    Calib();
  gameView.clearBuffer();
  gameView.drawCalib(calibProgress);
  updateScreen();
  if (calibProgress == 9 && switchIsOn[1])
    currentPage = Game;
}

void Controller::handlePageLoading() {
  
  timeEnterLoading = getTime();
  lvlNum++;
  bullets.clear();
  initWeaponAmmo();
  if (spawnSpeed <= minSpawnSpeed)
    spawnSpeed = minSpawnSpeed;
  else
    spawnSpeed -= spawnSpeedDecrement;

  targetsSpawned = 0;
  while (getTime() - timeEnterLoading <= loadScreenWaitTime) {
    gameView.clearBuffer();
    gameView.drawLoading(lvlNum);
    updateScreen();
  }
  currentPage = Game;
}

void Controller::handlePageGame() {
  
  if (wait && getTime() - timeExitPause + timeInvalidSpawn > spawnSpeed)
    wait = 0;
  //diplay special power availability through LED
  if (myPlayer.getSpecialPower())
    LightGLED();
  else
    LightRLED();
    
  //check if SP is triggerd;
  if (trigSP && myPlayer.getSpecialPower()) {
    myPlayer.addSpecialPower(-1);
    myPlayer.addScore(scorePerTarget * (targets.size() - 1));
    targets.clear();
    if (myPlayer.getKillCount() != 0 && myPlayer.getKillCount() % killsPerSP == 0)
      myPlayer.addSpecialPower(1);
  }
  
  unlockWeapons();
  
  if (buttonIsPressed[0])
    myPlayer.moveUp();
  if (buttonIsPressed[1])
    myPlayer.moveDown();
  if (buttonIsPressed[2])
    fireBullet((*selectedWeapon).getRpm(), (*selectedWeapon).getVelocity());
  if (!switchIsOn[1]) {
    timeInvalidSpawn = getTime() - timeLastSpawned;
    timeFlashDrawn = getTime();
    currentPage = Pause;
  }

  //check if a target needs to be spawned
  if (!wait && targetsSpawned < lvlNum * 10 && (timeLastSpawned == 0 || currentTime - timeLastSpawned >= spawnSpeed)) {
    targets.push_back(Target(lvlNum));
    targetsSpawned++;
    timeLastSpawned = getTime();
    timeInvalidSpawn=0;
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
  //draw bullets remaining on screen
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
  if (currentTime - timeFlashDrawn >= flashDrawTime + flashNotDrawTime)
    timeFlashDrawn = currentTime;
    
  gameView.clearBuffer();
  gameView.drawPause(currentTime - timeFlashDrawn <= flashDrawTime, myPlayer.getScore());
  updateScreen();
  
  if (switchIsOn[0] && !switchIsOn[1]) {
    currentPage = Inventory;
  }
  if (!switchIsOn[0] && switchIsOn[1]) {
    wait = 1;
    timeExitPause = getTime();
    currentPage = Game;
  }
  if(buttonIsPressed[3]) {
    Calib();
  }
}

void Controller::handlePageInventory() {

  updateCursor();
  gameView.clearBuffer();
  gameView.drawInventory(cursor.y, inventoryPage, myPlayer.getSpecialPower(), weapons);
  updateScreen();
  if (!switchIsOn[0] && !switchIsOn[1]) {
    currentPage = Pause;
  }
}

void Controller::handlePageGameResult() {
  
  gameView.clearBuffer();
  gameView.drawGameEnd(myPlayer.getScore());
  updateScreen();
  
  LightRLED();
  //Reset the entire game
  if (buttonIsPressed[3]) {
    initVariables();
    clearObjects();
    currentPage = Loading;
  }
}

void Controller::initVariables() {
  
  calibProgress = 0;
  lvlNum = 0;
  wait = 0;
  spawnSpeed = 1800;
  timeExitPause = 0;
  timeInvalidSpawn=0;
  timeEnterLoading = 0;
  timeLastSpawned = 0;
  timeLastFired = 0;
  timeLastDrawn = 0;
  currentTime = 0;
  trigSP = false;
  inventoryPage = 1;
  selectedWeapon = &(weapons[0]);
  cursor.y = 10;
  cursor.yShift = ScreenHeight / 3;
}

void Controller::initWeaponAmmo() {
  
  for (int k = 0; k < weapons.size(); k++) {
    weapons[k].setBulletsRemaining(weapons[k].getMagSize() * lvlNum * 0.5);
  }
}

void Controller::unlockWeapons() {
  
  for (int k = 0; k < weapons.size(); k++) {
    if (myPlayer.getScore() >= weapons[k].getScoreUnlocked() && !weapons[k].isUnlocked()) {
      weapons[k].setState(true);
    }
  }
}

void Controller::clearObjects() {
  
  myPlayer.resetVariables();
  targets.clear();
  bullets.clear();
  for (int k = 0; k < weapons.size(); k++) {
    weapons[k].setState(false);
  }
}
void Controller::detectCollision() {
  
  //detect if bullet exits right side of screen
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].getNextX() >= ScreenWidth) {
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
        if (myPlayer.getKillCount() != 0 && myPlayer.getKillCount() % killsPerSP == 0)
          myPlayer.addSpecialPower(1);
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
  if (buttonIsPressed[1] && ((strcmp((*selectedWeapon).name, weapons[weapons.size() - 1].name) == 0) || ((*(selectedWeapon + 1)).isUnlocked()))) {
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
    case Calibration:
      handlePageCalibration();
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

void Controller::setSPTrig(bool value) {
  trigSP = value;
}

void Controller::setButton(int i, bool value) {
  buttonIsPressed[i] = value;
}

void Controller::setSwitch(int i, bool value) {
  switchIsOn[i] = value;
}


