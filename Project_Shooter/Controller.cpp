#include "Controller.h"
#include "constants.h"

using namespace std;

static enum Pages {
  Welcome,
  Loading,
  Game,
  Pause,
  Inventory,
  GameResult,
} currentPage = Welcome;



Controller::Controller() {
  lvlNum = 1;
  counter = 0;   //testing var
  for (int i = 0; i < buttonNum; i++) {
    buttonIsPressed[i] = 0;
  }
  for (int i = 0; i < switchNum; i++) {
    switchIsOn[i] = 0;
  }
}

void Controller::handlePageWelcome() {
  gameView.clearScreen();
  gameView.drawWelcome();
  gameView.update();
  if (switchIsOn[1])
    currentPage = Loading;
}

void Controller::handlePageLoading() {
   gameView.clearScreen();
   gameView.drawLoading();
   gameView.update();
   currentPage = Game;
}

void Controller::handlePageGame() {
  //check input
  if (buttonIsPressed[0])
    myPlayer.moveUp();
  if (buttonIsPressed[1])
    myPlayer.moveDown();
  if (buttonIsPressed[2])
    bullets.push_back(Bullet(myPlayer.getRow(), myPlayer.getX(), myPlayer.getY(), myPlayer.getSize(), 0.4));
  if (!switchIsOn[1])
    currentPage = Pause;

  //check if needs to spawn target
  if (counter % 200 == 0) {
    targets.push_back(Target(1));
    counter = 0;
  }
  counter++;

  //draw and update target and bullet positions
  gameView.clearScreen();
  for (int i = 0; i < targets.size(); i++) {
    targets[i].update();
    gameView.drawTarget(targets[i]);
  }
  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].update();
    gameView.drawBullet(bullets[i]);
  }
  //draw player, target, and bullets
  gameView.drawPlayer(myPlayer);
  gameView.update();

  //collision detection
  detectCollision();
}

void Controller::handlePagePause() {
if (counter > 500)
    counter = 0;
  counter++;
  gameView.clearScreen();
  gameView.drawPause(counter < 350);
  gameView.update();
  if (switchIsOn[0] && switchIsOn[1])
    currentPage = Game;
}

void Controller::handlePageInventory() {

}

void Controller::handlePageGameResult() {
  gameView.clearScreen();
  gameView.drawGameEnd();
  gameView.update();
  if(!switchIsOn[1]) {
    currentPage = Welcome;
  }
}

void Controller::detectCollision() {
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].getNextX() >= screenWidth - 2) {
      bullets.erase(bullets.begin() + i);
    }
  }

  for (int i = 0; i < targets.size(); i++) {
    if (targets[i].getNextX() < 0) {
      targets.erase(targets.begin() + i);
      currentPage = GameResult;
      return;
    }
  }
  //target get row is the root of all evil
  for (int i = 0; i < bullets.size(); i++) {
    for (int k = 0; k < targets.size(); k++) {
      if ((bullets[i].getRow() == targets[k].getRow()) && (bullets[i].getNextX() >= targets[k].getNextX())) {
        bullets.erase(bullets.begin() + i);
        targets.erase(targets.begin() + k);
      }
    }
  }
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