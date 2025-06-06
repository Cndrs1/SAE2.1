#ifndef KEY_H
#define KEY_H

#include "item.h"
#include "door.h"

class Key : public Item
{
    int nbDoor;
    Door* itsDoor;
public:
    Key(int x, int y, QPixmap spriteItem, int dmg,itemType type, int aNbDoor, Door* aDoor = nullptr )
        : Item(x, y,spriteItem, dmg, type),nbDoor(aNbDoor), itsDoor(aDoor) {}
    Door *getItsDoor() const;
    void setItsDoor(Door* aDoor);
    int getNbDoor();
};
#endif // KEY_H


