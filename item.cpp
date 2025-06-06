#include "item.h"


QRect Item::getItsItemHitbox() const
{
    return itsItemHitbox;
}

int Item::getItsPositionX()
{
    return itsPositionX;
}

int Item::getItsPositionY()
{
    return itsPositionY;
}

QPixmap Item::getItsSpriteItem()
{
    return itsSpriteItem;
}

int Item::getItsDamage()
{
    return itsDamage;
}

itemType Item::getItsItemType()
{
    return itsItemType;
}


QPixmap getSpriteForItemType(itemType type)
{
    switch (type) {
    case sword: return QPixmap(":/Item/Sword.png");
    case bow: return QPixmap(":/Item/Bow.png");
    case life: return QPixmap(":/Item/Hearth.png");
    case key: return QPixmap(":/Item/Key1.png");
    case door: return QPixmap(":/Tiles/Door1.png");
    case wall: return QPixmap(":/Tiles/Wall.png");
    case magma: return QPixmap(":/Tiles/Magma.png");
    case theVoid: return QPixmap(":/Tiles/Void.png");
    case orc: return QPixmap(":/Enemy/Orc.png");
    case bossHead: return QPixmap(":/Enemy/BossHead.png");
    case bossBody: return QPixmap(":/Enemy/BossBody.png");
    case bossWeakPoint: return QPixmap(":/Enemy/BossTail.png");
    default: return QPixmap();

}
}
