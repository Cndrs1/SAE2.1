#ifndef DONJON_H
#define DONJON_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

using namespace std;

#include <vector>
#include <QFile>

#include "room.h"
#include "key.h"

class Donjon
{
    string itsName;
    vector<Room> itsRooms;
    Room* itsCurrentRoom;

public:

    Donjon(string name, Room* currentRoom=nullptr) : itsName(name), itsCurrentRoom(currentRoom) {}

    void openDoor(Key* aKey);
    void setCurrentRoom(Room* newCurrentRoom);
    void createRoom(QString donjonPath);

    string getItsName() const;
    Room& getItsCurrentRoom();
    vector<Room> getItsRooms() const;
    void moveEnemies() ;


        // Méthode pour obtenir les ennemis dans la salle courante
        std::vector<Enemy*> getEnemiesInCurrentRoom() {
            return itsCurrentRoom ? itsCurrentRoom->getEnemies() : std::vector<Enemy*>();
        }


};

#endif // DONJON_H
