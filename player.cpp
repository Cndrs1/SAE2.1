#include "player.h"
#include <QDebug>
#include "item.h"
#include "door.h"
#include "Game.h"  // Include Game.h here in the .cpp file, not the header
#include "enemy.h"

/**
 * @brief Constructs a Player object with the given parameters.
 *
 * @param pv The player's health points.
 * @param PositionX The player's initial X position.
 * @param PositionY The player's initial Y position.
 * @param useSword Whether the player uses a sword.
 * @param useBow Whether the player uses a bow.
 * @param spritePlayer The player's sprite image.
 * @param direction The direction the player is facing.
 */
void Player::setItsSpritePlayer(const QPixmap &newItsSpritePlayer)
{
    itsSpritePlayer = newItsSpritePlayer;
}

Player::Player(int pv, int PositionX, int PositionY, bool useSword, bool useBow, QPixmap spritePlayer, direction direction)
    : itsPv(pv), itsPositionX(PositionX), itsPositionY(PositionY),
    isUseSword(useSword), itsUseBow(useBow),
    itsArrow(nullptr), itsSpritePlayer(spritePlayer), itsDirection(direction), itsInv(0), itsIFrame(4), hasSword(false) {

    // Initialize the player's hitbox
    itsPlayerHitbox = QRect(itsPositionX, itsPositionY, itsSpritePlayer.width(), itsSpritePlayer.height());
    itsInv = false;
}


/**
 * @brief Gets the player's current hitbox.
 *
 * @return QRect The player's hitbox.
 */
QRect Player::getItsPlayerHitbox() const {
    return QRect(itsPositionX, itsPositionY + 100, 40, 40);  // Adjust based on the player's size
}

/**
 * @brief Checks if the player will collide with any walls or doors.
 *
 * @param items List of items in the game.
 * @param dx The change in the X position.
 * @param dy The change in the Y position.
 *
 * @return true if a collision is detected, false otherwise.
 */
bool Player::checkCollisionWithWalls(const std::vector<Item*>& items, int dx, int dy) {
    QRect futureHitbox = getItsPlayerHitbox().translated(dx, dy);

    for (Item* item : items) {
        if (!item) continue;

        if (item->getItsItemType() == wall || item->getItsItemType() == theVoid) {
            if (futureHitbox.intersects(item->getItsItemHitbox())) {
                return true;  // Collision with a wall
            }
        } else if (item->getItsItemType() == door) {
            Door* aDoor = dynamic_cast<Door*>(item);
            if (aDoor->getIsOpen() == 0 && futureHitbox.intersects(item->getItsItemHitbox())) {
                return true;  // Collision with a closed door
            }
        }
    }

    return false;
}

/**
 * @brief Returns whether the player is using a sword.
 *
 * @return true if the player is using a sword, false otherwise.
 */
bool Player::getItsUseSword() const {
    return isUseSword;
}

/**
 * @brief Returns whether the player has a sword.
 *
 * @return true if the player has a sword, false otherwise.
 */
bool Player::getHasSword() const {
    return hasSword;
}

/**
 * @brief Moves the player up.
 */
void Player::moveUp() {
    itsDirection = north;
    itsPositionY -= 10;
}

/**
 * @brief Moves the player left.
 */
void Player::moveLeft() {
    itsDirection = west;
    itsPositionX -= 10;
}

/**
 * @brief Moves the player right.
 */
void Player::moveRight() {
    itsDirection = east;
    itsPositionX += 10;
}

/**
 * @brief Moves the player down.
 */
void Player::moveDown() {
    itsDirection = south;
    itsPositionY += 10;
}

/**
 * @brief Performs a sword attack if the player has a sword.
 *
 * @param game Pointer to the Game object.
 */
void Player::attackSword(Game* game) {
    if (hasSword) {
        // Trigger the attack
        isUseSword = true;

        // Get the attack hitbox
        QRect attackHitbox = getAttackHitbox();

        // Get the list of enemies in the current room via the Donjon (Dungeon)
        std::vector<Enemy*> enemies = game->getCurrentDonjon().getEnemiesInCurrentRoom();

        // Check for collisions with enemies
        for (Enemy* enemy : enemies) {
            if (!enemy) continue;

            // Check if the attack hitbox intersects with the enemy's hitbox
            if (attackHitbox.intersects(enemy->getItsEnemyHitbox())) {
                // Inflict damage to the enemy
                enemy->takeDamage(1);  // Example: Inflict 1 damage
            }
        }
    }
}

/**
 * @brief Reduces the player's health by the specified damage amount.
 *
 * @param damage The amount of damage to inflict.
 */
void Player::takeDamage(int damage) {
    // Decrease the player's health points
    itsPv -= damage;
    if (itsPv <= 0) {
        itsPv = 0;  // Prevent negative health points
        // die(); // Call a function to handle the player's death (optional)
    }
    // Optional: Add visual or sound effects here (e.g., flash or color change)
}

/**
 * @brief Handles the player's death.
 */
void Player::die() {
    qDebug() << "Player has died!";
}

/**
 * @brief Returns the attack hitbox based on the player's direction.
 *
 * @return QRect The attack hitbox.
 */
QRect Player::getAttackHitbox() const {
    int attackWidth = 40;  // Width of the sword's hitbox
    int attackHeight = 40; // Height of the sword's hitbox

    switch (itsDirection) {
    case north:
        return QRect(itsPositionX + 10, itsPositionY + 100 - attackHeight, attackWidth, attackHeight);  // Attack upwards
    case south:
        return QRect(itsPositionX + 10, itsPositionY + 100 + itsSpritePlayer.height(), attackWidth, attackHeight);  // Attack downwards
    case west:
        return QRect(itsPositionX - attackWidth, itsPositionY + 100 + 10, attackWidth, attackHeight);  // Attack to the left
    case east:
        return QRect(itsPositionX + itsSpritePlayer.width(), itsPositionY + 100 + 10, attackWidth, attackHeight);  // Attack to the right
    default:
        return QRect();  // Default case, shouldn't be reached
    }
}

/**
 * @brief Gets the player's current health points.
 *
 * @return int The player's health points.
 */
int Player::getItsPv() const {
    return itsPv;
}

/**
 * @brief Gets the player's current X position.
 *
 * @return int The player's X position.
 */
int Player::getItsPositionX() const {
    return itsPositionX;
}

/**
 * @brief Gets the player's current Y position.
 *
 * @return int The player's Y position.
 */
int Player::getItsPositionY() const {
    return itsPositionY;
}

/**
 * @brief Gets the player's sprite based on the direction and weapon usage.
 *
 * @return QPixmap The current sprite image for the player.
 */
QPixmap Player::getItsSpritePlayer() const {
    if (isUseSword) {
        // Return the appropriate sprite when the player is using a sword
        switch (itsDirection) {
        case north: return QPixmap(":/Player/PlayerSwordUpV2.png");
        case south: return QPixmap(":/Player/PlayerSwordDownV2.png");
        case west: return QPixmap(":/Player/PlayerSwordLeftV2.png");
        case east: return QPixmap(":/Player/PlayerSwordRightV2.png");
        default: return QPixmap(":/Player/PlayerSwordDownV2.png");
        }
    } else {
        // Return the appropriate sprite when the player is not using a sword
        switch (itsDirection) {
        case north: return QPixmap(":/Player/PlayerUp.png");
        case south: return QPixmap(":/Player/PlayerDown.png");
        case west: return QPixmap(":/Player/PlayerLeft.png");
        case east: return QPixmap(":/Player/PlayerRight.png");
        default: return QPixmap(":/Player/PlayerDown.png");
        }
    }
}

/**
 * @brief Sets the player's sword status to true.
 */
void Player::setHasSword() {
    hasSword = true;
}

/**
 * @brief Sets whether the player is using a sword.
 *
 * @param use true to use a sword, false otherwise.
 */
void Player::setUseSword(bool use) {
    isUseSword = use;
}

/**
 * @brief Sets the player's bow usage status to true.
 */
void Player::setBow() {
    itsUseBow = true;
}

/**
 * @brief Increases the player's health points by 1.
 */
void Player::addPv() {
    itsPv++;
}

/**
 * @brief Gets the player's invincibility status.
 *
 * @return true if the player is invincible, false otherwise.
 */
bool Player::getItsInv() {
    return itsInv;
}

/**
 * @brief Changes the player's invincibility status.
 *
 * @param statue The new invincibility status.
 */
void Player::changeInvicibility(bool statue) {
    itsInv = statue;
}

/**
 * @brief Gets the player's current iframe.
 *
 * @return int The player's iframe value.
 */
int Player::getItsIframe() {
    return itsIFrame;
}

/**
 * @brief Gets the player's current direction.
 *
 * @return direction The player's direction.
 */
direction Player::getItsDirection() {
    return itsDirection;
}

/**
 * @brief Sets the player's position to the specified coordinates.
 *
 * @param aX The new X position.
 * @param aY The new Y position.
 */
void Player::setPos(int aX, int aY) {
    itsPositionX = aX;
    itsPositionY = aY;
}
