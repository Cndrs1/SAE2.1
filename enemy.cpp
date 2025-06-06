#include "enemy.h"
#include <random>
#include "player.h"

// Déplace l'ennemi dans une direction aléatoire
void Enemy::move() {
    itsDirection = getRandomDirection();

    switch (itsDirection) {
    case direction::north:
        if (itsPositionY - 50 >= 0) {
            itsPositionY -= 50;
        }
        break;
    case direction::south:
        if (itsPositionY + 50 <= 600) {
            itsPositionY += 50;
        }
        break;
    case direction::east:
        if (itsPositionX + 50 <= 800) {
            itsPositionX += 50;
        }
        break;
    case direction::west:
        if (itsPositionX - 50 >= 0) {
            itsPositionX -= 50;
        }
        break;
    }

    // Met à jour la hitbox de l'ennemi
    itsItemHitbox.moveTo(itsPositionX, itsPositionY + 100);  // Offset de 100 pour le placement vertical
}

direction Enemy::getRandomDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);  // Corrigé pour 4 directions

    int randDirection = dis(gen);

    switch (randDirection) {
    case 0: return direction::north;
    case 1: return direction::south;
    case 2: return direction::east;
    case 3: return direction::west;
    default: return direction::south;
    }
}

void Enemy::attack(Player& player) {
    QRect enemyHitbox = this->getItsEnemyHitbox();
    QRect playerHitbox = player.getItsPlayerHitbox();

    // On peut aussi ajouter ici la logique d'attaque, mais on garde cette partie simple pour l'exemple
}

void Enemy::takeDamage(int damage) {
    if (isInvincible) {
        qDebug() << "Enemy is invincible, no damage taken!";
        return;  // L'ennemi ne prend pas de dégâts s'il est invincible
    }
    itsPv -= damage;
    if (itsPv <= 0) {
        die();
    }
    // L'ennemi devient invincible pendant un certain temps après avoir pris des dégâts
    setInvincible(true);        // L'ennemi devient invincible
    setIFrame(2.0);             // Exemple : 2 secondes d'invincibilité
}

void Enemy::updateIFrame(double deltaTime) {
    if (itsIFrame > 0) {
        itsIFrame -= deltaTime;
        if (itsIFrame <= 0) {
            isInvincible = false;  // L'ennemi n'est plus invincible
        }
    }
}

void Enemy::die() {

    isInvincible = true;
    // Tu pourrais aussi mettre une animation ou effet sonore ici, si nécessaire
}

void Enemy::setDirection(direction dir) {
    itsDirection = dir;
}

direction Enemy::getDirection() const {
    return itsDirection;
}

void Enemy::setPv(int pv) {
    itsPv = pv;
}

int Enemy::getPv() const {
    return itsPv;
}

int Enemy::getItsPositionX() const {
    return itsPositionX;
}

int Enemy::getItsPositionY() const {
    return itsPositionY;
}

QPixmap Enemy::getItsSpriteItem() const {
    return itsSpriteItem;
}

itemType Enemy::getItsItemType() const {
    return itsItemType;
}
