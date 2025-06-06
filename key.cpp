#include "key.h"


Door *Key::getItsDoor() const
{
    return itsDoor;
}

void Key::setItsDoor(Door* aDoor){
    itsDoor=aDoor;
}


int Key::getNbDoor(){
    return nbDoor;
}
