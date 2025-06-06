#ifndef DOOR_H
#define DOOR_H

#include"item.h"
#include "room.h"

class Door:public Item
{
private:
    int itsIdDoor;
    bool isOpen;
    int itsNbTargets;
    Room* itsNextRoom;
    int itsNbRoom;
public:

    Door(int x, int y, QPixmap spriteItem, int dmg,itemType type,
         int id, bool open, int nbTargets, Room* nextRoom, int aRoomNb)
        : Item(x, y,spriteItem, dmg, type), itsIdDoor(id),
        isOpen(open),itsNbTargets(nbTargets), itsNextRoom(nextRoom), itsNbRoom(aRoomNb) {}

    int getItsIdDoor() const;
    bool getIsOpen() const;
    int getNbRoom();
    Room* getNextRoom();
    void setNextRoom(Room* aNextRoom);
    void setSprite (QPixmap aSprite);

    //Function to open a door
    void open()
    {
        isOpen = true;
    }




};



#endif // DOOR_H
