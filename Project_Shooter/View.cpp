#include "View.h"
#include "constants.h"

View::View() {
  OrbitOledInit();
}

void View::drawWelcome(){
  OrbitOledMoveTo(screenWidth/3,screenHeight/2);
  OrbitOledDrawString("Welcome");
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

void View::clearScreen() {
  OrbitOledClearBuffer();
  OrbitOledClear();
}

void View::update() {
  OrbitOledUpdate();
}