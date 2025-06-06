#ifndef GAME_H
#define GAME_H


#include <vector>
#include <list>
#include <QElapsedTimer>
#include "donjon.h"
#include "player.h"
#include "scores.h"

class Game
{
    std::vector<Donjon> itsDonjon;
    std::list<Scores> itsScores;
    Player* itsPlayer;
    int itsTime;
    QElapsedTimer itschrono;
    int lastIFrame;
    float lastUseSword;

public:

    Game(int time = 0);
    ~Game();

    int getItsTime() const;
    std::vector<Donjon> getItsDonjon() const;
    Donjon& getCurrentDonjon();
    Player *getItsPlayer() const;

    void startGame();
    void showLogo();
    void showPitch();
    void displayLeadBoard();
    void victoryScreen();
    void gameOverScreen();
    void saveScore();
    void addTime(string name, int Time);
    QElapsedTimer getChrono();
    Room& getCurrentRoom();
    void pickUpNearbyItem(Room& room);
    void update();
    void specialColision();






};

#endif // GAME_H
