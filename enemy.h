#ifndef ENEMY_H
#define ENEMY_H

#include "item.h"
#include "direction.h"
#include <QPixmap>
#include <QDebug>
#include "player.h"

class Enemy : public Item {
protected:
    int itsPv;                // Points de vie de l'ennemi
    bool isInvincible;        // Indicateur d'invincibilité de l'ennemi
    double itsIFrame;         // Frames d'invincibilité (si l'ennemi peut être touché ou non)
    direction itsDirection;   // Direction actuelle de l'ennemi

public:
    // Constructeur de l'ennemi
    Enemy(int x, int y, QPixmap spriteItem, int dmg, itemType type, int pv, bool inv = false, double iframe = 0.0)
        : Item(x, y, spriteItem, dmg, type), itsPv(pv), isInvincible(inv), itsIFrame(iframe) {}

    QRect getItsEnemyHitbox() const {
        return QRect(itsPositionX, itsPositionY + 100, 50, 50); // 50x50 de taille pour l'ennemi
    }

    void move();
    void attack(Player& player);
    void takeDamage(int damage) override;
    void updateIFrame(double deltaTime);
    void die();

    // Setters et Getters
    void setDirection(direction dir);
    direction getDirection() const;

    void setPv(int pv);
    int getPv() const;

    int getItsPositionX() const;
    int getItsPositionY() const;
    QPixmap getItsSpriteItem() const;
    itemType getItsItemType() const;

    direction getRandomDirection();

    // Setters pour l'invincibilité et I-Frame
    void setInvincible(bool inv) { isInvincible = inv; }
    void setIFrame(double iframe) { itsIFrame = iframe; }
    bool getIsInvincible() const { return isInvincible; }
    double getIFrame() const { return itsIFrame; }
};

#endif // ENEMY_H
