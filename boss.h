#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

enum bossType{
    head,
    body,
    tail
};


class Boss : Enemy
{
private:

    int itsId;
    bossType itsBossType;

public:

    Boss(int x, int y, QPixmap spriteItem, int dmg,itemType type,
         int pv, bool inv, double frame, int id, bossType bossType)
        : Enemy(x, y, spriteItem, dmg, type, pv,inv, frame),  itsId(id),itsBossType(bossType){}

    void chasse();
    void takeDamage();

};

#endif // BOSS_H
