#include "door.h"


bool Door::getIsOpen() const
{
    return isOpen;
}

int Door::getItsIdDoor() const
{
    return itsIdDoor;
}


int Door::getNbRoom(){ return itsNbRoom;}

void Door::setNextRoom(Room* theNextRoom){
    itsNextRoom = theNextRoom;
}

Room* Door::getNextRoom()
{
    return itsNextRoom;
}
void Door::setSprite(QPixmap aSprite){
    itsSpriteItem = aSprite;
}
