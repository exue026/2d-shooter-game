#include "Controller.h"

static enum Pages {
  Welcome,
  Game,
  Inventory,
  GameResult,
} currentPage = Game;

Controller::Controller(){
  
}

void Controller::handlePageWelcome(){
    
}

void Controller::handlePageGame(){
  
}


void Controller::gameTick() {
  switch (currentPage) {
    case Welcome:
      handlePageWelcome();
      break;
    case Game:
      break;
    case Inventory:
      break;
    case GameResult:
      break;
  }
}
