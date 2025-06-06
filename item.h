#ifndef ITEM_H
#define ITEM_H

#include <QRect>
#include <QPixmap>
#include <QRect>

enum itemType{
    sword,
    bow,
    life,
    key,
    wall,
    magma,
    theVoid,
    door,
    mimic,
    target,
    trap,
    skeleton,
    orc,
    bossHead,
    bossBody,
    bossWeakPoint,
    theExit,
    theFloor
};


QPixmap getSpriteForItemType(itemType type);


class Item {
protected:
    QRect itsItemHitbox;
    int itsPositionX;
    int itsPositionY;
    QPixmap itsSpriteItem;
    int itsDamage;
    itemType itsItemType;


public:
    Item(int x, int y, QPixmap spriteItem, int dmg, itemType type)
        : itsPositionX(x),
        itsPositionY(y),
        itsSpriteItem(spriteItem.isNull() ? getSpriteForItemType(type) : spriteItem),
        itsDamage(dmg),
        itsItemType(type)
    {
        // Redimensionner le sprite et mettre à jour la hitbox
        itsSpriteItem = itsSpriteItem.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        // Ajuster la hitbox pour correspondre à la position et la taille du sprite
        itsItemHitbox = QRect(x, y+100, 50, 50);
    }


    int getItsPositionX();
    int getItsPositionY();
    QPixmap getItsSpriteItem();
    int getItsDamage();
    itemType getItsItemType();


    virtual void takeDamage(int damage) {

        itsDamage -= damage;
    }

    virtual ~Item(){}
    QRect getItsItemHitbox() const;
};




#endif // ITEM_H
