#ifndef ARROW_H
#define ARROW_H

#include <QPixmap>
#include <QRect>
#include "direction.h"

enum arrowType{
    good,
    bad
};

class Arrow
{
    QRect ItsArrowHitbox;
    QPixmap itsSpriteArrow;
    direction itsDirection;
    arrowType itsType;
    QRect itsRect;

    int itsPositionX;
    int itsPositionY;

public:

    int getItsX();
    int getItsY();

    Arrow(QPixmap spriteArrow , direction direction, arrowType type, int aX, int aY)
        : itsSpriteArrow(spriteArrow), itsDirection(direction), itsType(type), itsPositionX(aX), itsPositionY(aY) {}

    void move();
    QPixmap getItsSpriteArrow() const;

    ~Arrow();
};

#endif // ARROW_H
