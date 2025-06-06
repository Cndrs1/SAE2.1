#include "room.h"

std::vector<Item*> Room::getItsItems() const
{
    return itsItems;
}

void Room::addItems(Item* newItems)
{
    itsItems.push_back(newItems);
}

void Room::removeItem(Item* item)
{

    auto it = std::find(itsItems.begin(), itsItems.end(), item);
    if (it != itsItems.end()) {
        itsItems.erase(it);  // Supprime l'item de la liste
    }
}

std::vector<Item*>& Room::getItsItems() {
    return itsItems;
}

int Room::getItsNumber()
{
    return itsNumber;
}
