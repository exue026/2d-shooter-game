#include "Player.h"
#include "View.h"

#ifndef _CONTROLLER
#define _CONTROLLER
class Controller {
  private:
    Player player;
    View gameView;

  public:
    Controller();
    void gameTick();
    void handlePageWelcome();
    void handlePageGame();
};
#endif
