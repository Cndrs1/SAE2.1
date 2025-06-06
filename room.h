#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "item.h"
#include "enemy.h"

class Room
{
    int itsNumber;
    std::vector<Item*> itsItems;

public:
    Room(int number) : itsNumber(number) {}
    int getItsNumber();
    std::vector<Item*> getItsItems() const;
    void addItems(Item* newItems);
    void removeItem(Item* item);
    std::vector<Item*>& getItsItems();  // Version modifiable

    // Méthode pour récupérer les ennemis dans la salle
    std::vector<Enemy*> getEnemies() {
        std::vector<Enemy*> enemies;
        for (Item* item : itsItems) {
            Enemy* enemy = dynamic_cast<Enemy*>(item);
            if (enemy) {
                enemies.push_back(enemy);
            }
        }
        return enemies;
    }
};

#endif // ROOM_H
