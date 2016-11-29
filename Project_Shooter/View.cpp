#include "View.h"

View::View() {
  OrbitOledInit();
}

void View::drawWelcome() {
  
  for (int i = 5; i < ScreenWidth - 10; i += 10) {
    OrbitOledMoveTo(i, 5);
    OrbitOledDrawString("~");
    OrbitOledMoveTo(i, ScreenHeight - 7);
    OrbitOledDrawString("~");
  }
  OrbitOledMoveTo(ScreenWidth / 4, ScreenHeight / 2);
  OrbitOledDrawString("Welcome!");
}

void View::drawCalib(int calibProgress) {
  
  int deviceNum;  //the number code of the devic(switch/button) currently calibrating
  OrbitOledMoveTo(0, 2);
  
  if (calibProgress <= 3) {
    deviceNum = calibProgress / 2;
    char msg[13 + 1]; //13 is max length of first row of the messsage, plus 1 for null terminator
    char deviceNumChar[2];
    strcpy(msg, "Flip Switch ");
    sprintf(deviceNumChar, "%d", deviceNum);
    strcat(msg, deviceNumChar);
    OrbitOledDrawString(msg);
    
    //switch is not used here because of the range of each if statement
    if (calibProgress % 2 == 0 ) {
      OrbitOledMoveTo(ScreenWidth / 2 - 10 * 1, 17);
      OrbitOledDrawString("Up");
    } else {
      OrbitOledMoveTo(ScreenWidth / 2 - 10 * 2, 17);
      OrbitOledDrawString("Down");
    }
  } else if (calibProgress <= 7) {
    deviceNum = calibProgress - 4;
    char msg[14 + 1]; //14 is the length of the messsage, plus 1 for null terminator
    char deviceNumChar[2];
    OrbitOledMoveTo ((ScreenWidth - 10 * 14) / 2, (ScreenHeight - 10) / 2 ); //14 is length of message drawn
    sprintf(deviceNumChar, "%d", deviceNum);
    strcpy(msg, "Press Button ");
    strcat(msg, deviceNumChar);
    OrbitOledDrawString(msg);
  } else if (calibProgress == 8) {
    OrbitOledMoveTo ((ScreenWidth - 10 * 11) / 2, 3);
    OrbitOledDrawString("Press B0 To");
    OrbitOledMoveTo ((ScreenWidth - 10 * 9) / 2, 17);
    OrbitOledDrawString("Calibrate");
  }
  else if (calibProgress == 9) {
    OrbitOledMoveTo ((ScreenWidth - 10 * 9) / 2, 3);
    OrbitOledDrawString("Finished!");
    OrbitOledMoveTo (ScreenWidth/5, 17);
    OrbitOledDrawString("S1 To Play");
  }

}

void View::drawLoading(int lvlNum) {
  
  int digits = lvlNum > 0 ? (int) log10 ((double) lvlNum) + 1 : 1;
  char msg[ 7 + digits + 1];  //7 is the length of "Level: "
  char lvlNumChar[digits + 1];
  sprintf(lvlNumChar, "%d", lvlNum);
  strcpy(msg, "Level: ");
  strcat(msg, lvlNumChar);
  OrbitOledMoveTo(ScreenWidth / 4, ScreenHeight / 3);
  OrbitOledDrawString(msg);
}

void View::drawPause(int i, int score) {
  
  OrbitOledMoveTo(ScreenWidth / 6, 0);
  if (i)
    OrbitOledDrawString("Game Paused");
  OrbitOledMoveTo(ScreenWidth / 5, ScreenHeight - 22);
  int digits = score > 0 ? (int) log10 ((double) score) + 1 : 1;
  char scoreMsg[7 + digits + 1];
  char scoreChar[digits + 1];
  sprintf(scoreChar, "%d", score);
  strcpy(scoreMsg, "Score: ");
  strcat(scoreMsg, scoreChar);
  OrbitOledDrawString(scoreMsg);
  OrbitOledMoveTo(0, ScreenHeight - 10);
  OrbitOledDrawString("S1 for Inventory");
}

void View::drawInventory(int cursorY, int inventoryPage, int spCount, std::vector<Weapon>&weapons) {
  
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Inventory");
  OrbitOledMoveTo(ScreenWidth - 50, 0);
  OrbitOledDrawString("SP:");
  int digits = spCount > 0 ? (int) log10 ((double) spCount) + 1 : 1;
  char numNukes[digits];
  sprintf(numNukes, "%d", spCount);
  OrbitOledDrawString(numNukes);

  for (int k = 2; k > 0; k--) {
    if (k == 2)
      OrbitOledMoveTo(ScreenWidth / 6, 10);
    else
      OrbitOledMoveTo(ScreenWidth / 6, 10 + ScreenHeight / 3);
      
    if (weapons[(inventoryPage * 2) - k].isUnlocked()) {
      OrbitOledDrawString(weapons[(inventoryPage * 2) - k].name);
      OrbitOledMoveTo(ScreenWidth - 65, k == 2 ? 10 : 10 + ScreenHeight / 3);
      OrbitOledDrawString("#");
      int digits = weapons[(inventoryPage * 2) - k].getBulletsRemaining() > 0 ? (int) log10 ((double) weapons[(inventoryPage * 2) - k].getBulletsRemaining()) + 1 : 1;
      char ammunition[digits];
      sprintf(ammunition, "%d", weapons[(inventoryPage * 2) - k].getBulletsRemaining());
      OrbitOledDrawString(ammunition);
    }
  }

  OrbitOledMoveTo(0, cursorY);
  OrbitOledDrawString("->");

}

void View::drawGameEnd(int score) {

  OrbitOledMoveTo(ScreenWidth / 5, 0);
  OrbitOledDrawString("Game Over!!");
  OrbitOledMoveTo(0, 15);
  OrbitOledDrawString("Final score: ");
  int digits = score > 0 ? (int) log10 ((double) score) + 1 : score < 0 ? (int) log10 ((double) - score) + 1 : 1;
  char finalScore[digits];
  sprintf(finalScore, "%d", score);
  OrbitOledMoveTo(ScreenWidth - 35, 15);
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
  int digits = bulletsRemaining > 0 ? (int) log10 ((double) bulletsRemaining) + 1 : 1;
  char count[digits];
  sprintf(count, "%d", bulletsRemaining);
  OrbitOledMoveTo(ScreenWidth - 32, ScreenHeight - 8);
  OrbitOledDrawString(count);
}

void View::clearBuffer() {
  OrbitOledClearBuffer();
}

void View::update() {
  OrbitOledUpdate();
}
