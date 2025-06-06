#ifndef PLAYER_H
#define PLAYER_H

#include <QPixmap>
#include <QRect>
#include <vector>

#include "arrow.h"
#include "direction.h"
#include "item.h"

class Game;

/**
 * @brief The Player class represents a player character in the game.
 */
class Player
{
    // Private member variables
    QRect itsPlayerHitbox;      ///< Hitbox for collision detection
    int itsPv;                  ///< Player's health points
    int itsPositionX;           ///< Player's X position
    int itsPositionY;           ///< Player's Y position
    bool isUseSword;            ///< Whether the player is using a sword
    bool itsUseBow;             ///< Whether the player is using a bow
    Arrow* itsArrow;            ///< Pointer to the player's arrow (if using bow)
    QPixmap itsSpritePlayer;    ///< Player's sprite image
    direction itsDirection;     ///< Direction the player is facing
    bool itsInv;                ///< Invincibility status
    int itsIFrame;              ///< Time frame for invincibility (if applicable)
    bool hasSword;              ///< Whether the player has a sword

public:
    // Constructor
    Player(int pv, int PositionX, int PositionY, bool useSword, bool useBow, QPixmap spritePlayer, direction direction);

    // Movement functions
    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();

    // Attack functions
    void attackSword(Game* game);
    void attackBow();

    // Damage and death handling
    void takeDamage(int damage);
    void die();

    // Getters and Setters
    QRect getAttackHitbox() const;         ///< Get the player's attack hitbox
    QRect getItsPlayerHitbox() const;      ///< Get the player's hitbox
    QPixmap getItsSpritePlayer() const;    ///< Get the player's sprite
    direction getItsDirection();           ///< Get the player's facing direction
    int getItsPv() const;                  ///< Get the player's health points
    int getItsPositionX() const;           ///< Get the player's X position
    int getItsPositionY() const;           ///< Get the player's Y position
    bool getItsInv();                      ///< Get the player's invincibility status
    bool getItsUseSword() const;           ///< Check if the player is using a sword
    bool getHasSword() const;              ///< Check if the player has a sword
    int getItsIframe();                    ///< Get the player's invincibility frames

    // Setter functions
    void setHasSword();                    ///< Set the player to have a sword
    void setUseSword(bool use);            ///< Set whether the player is using a sword
    void setBow();                         ///< Set the player to use a bow
    void setPos(int aX, int aY);           ///< Set the player's position
    void addPv();                          ///< Increase the player's health points
    void changeInvicibility(bool statue);  ///< Change the player's invincibility status

    // Helper functions
    void updateSpriteWithSword();          ///< Update the sprite based on sword usage
    bool checkCollisionWithWalls(const std::vector<Item*>& items, int dx, int dy); ///< Check for collisions with walls
    void setItsSpritePlayer(const QPixmap &newItsSpritePlayer);
};

#endif // PLAYER_H
