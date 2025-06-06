#include "donjon.h"
#include "enemy.h"


void Donjon::createRoom(QString donjonPath) {
    QFile file(donjonPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Impossible d'ouvrir le fichier JSON du donjon.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qWarning("Le fichier JSON du donjon n'est pas un tableau.");
        return;
    }

    QJsonArray roomsArray = doc.array();

    vector<Item*> keyList; //Liste de clé que l'on utilisera plus tard.
    vector<Item*> doorList;

    for (int i = 0; i < roomsArray.size(); ++i) {
        QJsonValue value = roomsArray[i];
        if (!value.isObject()) continue;

        QJsonObject roomObj = value.toObject();
        QString roomId = roomObj["room_id"].toString();
        int roomNumber = roomId.toInt();

        Room newRoom(roomNumber);
        QJsonArray rows = roomObj["room"].toArray();

        int aY = -50;
        for (int j = 0; j < rows.size(); ++j) {
            QJsonArray row = rows[j].toArray();
            int aX = -50;
            aY += 50;
            for (int k = 0; k < row.size(); ++k) {
                aX += 50;
                QString itemType = row[k].toString();
                Item* item = nullptr;

                if (itemType == "end_level")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Stairs.png"), 0, theExit);
                else if (itemType == "floor")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Floor.png"), 0, theFloor);
                else if (itemType == "sword")
                    item = new Item(aX, aY, QPixmap(":/Item/Sword.png"), 0, sword);
                else if (itemType == "bow")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 0, bow);
                else if (itemType == "hearth")
                    item = new Item(aX, aY, QPixmap(":/Item/Hearth.png"), 0, life);
                else if(itemType[0] == 'k' and itemType[1] == 'e' and itemType[2] == 'y')
                {
                    item = new Key(aX, aY, QPixmap(":/Item/Key1.png"), 0, key, itemType[3].digitValue());
                    keyList.push_back(item);
                }
                else if (itemType == "wall"){
                    item = new Item(aX, aY, QPixmap(":/Item/Wall.png"), 0, wall);}
                else if (itemType == "magma")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 1, magma);
                else if (itemType == "void")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Void.png"), 0, theVoid);
                else if (itemType[0] == 'd' and itemType[1] == 'o' and itemType[2] == 'o' and itemType[3] == 'r' ){
                    item = new Door(aX, aY, QPixmap(":/Tiles/Door1.png"), 0, door, itemType[4].digitValue(), itemType[5].digitValue() ,itemType[6].digitValue(),nullptr, itemType[7].unicode());
                    doorList.push_back(item);
                }
                else if (itemType == "mimic")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 1, mimic);
                else if (itemType == "target")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 0, target);
                else if (itemType == "trap")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 1, trap);
                else if (itemType == "skeleton")
                    item = new Item(aX, aY, QPixmap(":/Tiles/Magma.png"), 1, skeleton);
                else if (itemType == "orc")
                    item = new Enemy(aX, aY, QPixmap(":/Enemy/Orc.png"), 1, orc,2,0,1);
                else if (itemType == "bossHead")
                    item = new Item(aX, aY, QPixmap(":/Enemy/BossHead.png"), 1, bossHead);
                else if (itemType == "bossBody")
                    item = new Item(aX, aY, QPixmap(":/Enemy/BossBody.png"), 1, bossBody);
                else if (itemType == "bossWeakPoint")
                    item = new Item(aX, aY, QPixmap(":/Enemy/BossTail.png"), 1, bossWeakPoint);
                newRoom.addItems(item);
                //qDebug()<<item->getItsItemType();
            }

        }

        itsRooms.push_back(newRoom);
        itsRooms.emplace_back(itsRooms.size());
    }

    if (!itsRooms.empty()) {
        itsCurrentRoom = &itsRooms[0];
    }

    //Donner les bonne portes à chaque clés
    for(Item* aItem : keyList){
        Key* aKey = dynamic_cast<Key*>(aItem);
        for (Item* aSecondItem : doorList){
            Door* aDoor = dynamic_cast<Door*>(aSecondItem);
            if (aKey->getNbDoor() == aDoor->getItsIdDoor())
            {
                aKey->setItsDoor(aDoor);
            }
        }
    }

    //Associer les Salles aux bonne portes
    for(Item* aItem : doorList){
        Door* aDoor = dynamic_cast<Door*>(aItem);
        for (Room& aRoom: itsRooms){
            if (aDoor->getNbRoom() - 64 == aRoom.getItsNumber())
            {
                aDoor->setNextRoom(&aRoom);
                qDebug() << "Salle " << aRoom.getItsNumber() << " associé à la porte " << aDoor->getItsIdDoor();
            }
        }
    }


}

// Dans Donjon.cpp
void Donjon::moveEnemies() {
    for (Room& room : itsRooms) {
        // Récupère tous les ennemis dans la salle
        std::vector<Enemy*> enemies = room.getEnemies();
        for (Enemy* enemy : enemies) {
            if (enemy) {
                enemy->move();  // Déplace l'ennemi
            }
        }
    }
}


void Donjon::setCurrentRoom(Room* newCurrentRoom) {
    itsCurrentRoom = newCurrentRoom;
}

void Donjon::openDoor(Key* aKey)
{
    Door* targetDoor = aKey->getItsDoor();
    if (!targetDoor)return;

    for (Room& r : itsRooms){
        for (Item* i : r.getItsItems()) {

            Door* d =dynamic_cast<Door*>(i);
            if (d && d == targetDoor && !d->getIsOpen()){
                d->open();
                d->setSprite(QPixmap(":/Tiles/Floor.png"));
                return;
            }

        }
    }
}

Room& Donjon::getItsCurrentRoom() {
    if (!itsCurrentRoom) {
        throw std::runtime_error("Salle courante invalide !");
    }
    return *itsCurrentRoom;
}

vector<Room> Donjon::getItsRooms() const
{
    return itsRooms;
}

string Donjon::getItsName() const
{
    return itsName;
}


