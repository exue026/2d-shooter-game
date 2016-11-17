#include "View.h"
#include "constants.h"

View::View() {
  OrbitOledInit();
}

void View::drawPlayer(Player player) {
  OrbitOledClearBuffer();
  OrbitOledMoveTo(player.getX(), player.getY());
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledFillRect(player.getX()+player.getSize(), player.getY()+player.getSize());
  OrbitOledUpdate();
}
