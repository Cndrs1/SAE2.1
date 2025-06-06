
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>
#include <QDebug>
#include "game.h"
#include "donjon.h"
#include "enemy.h"
#include "scores.h"



using namespace std;

std::vector<Donjon> Game::getItsDonjon() const
{
    return itsDonjon;
}

Donjon& Game::getCurrentDonjon() {
    if (itsDonjon.empty()) {
        throw std::runtime_error("Aucun donjon disponible !");
    }
    return itsDonjon.front();
}

Player *Game::getItsPlayer() const
{
    return itsPlayer;
}

int Game::getItsTime() const
{
    return itsTime;
}

Game::Game(int time) {

    itsTime = time;
    QPixmap playerSprite(":/Player/PlayerDown.png");
    itsPlayer = new Player(3, 300,500, 0, 0,playerSprite, north);

    Donjon donjon1("First Donjon");
    donjon1.createRoom(":/Map/Donjon1.json");
    donjon1.setCurrentRoom(&donjon1.getItsRooms().front());
    itsDonjon.push_back(donjon1);


    // Donjon donjon3("Boss Donjon");
    // donjon3.createRoom(":/Map/Donjon3.json");
    // donjon3.setCurrentRoom(&donjon3.getItsRooms().front());
    // itsDonjon.push_back(donjon3);


    itsScores = {};
    //qDebug() << "Game initialized with" << itsDonjon.size() << "dungeons.";
    itschrono.start();
    lastIFrame = 0;
    lastUseSword = 0;

}


Game::~Game() {
    saveScore();
    delete itsPlayer;
}


void Game::saveScore()
{
    string name;
    cout << "Entrez votre nom pour enregistrer votre score : ";
    cin >> name;

    addTime(name, itsTime);  // ajoute le score dans la liste

    // enregistre le dernier score
    if (!itsScores.empty())
    {
        itsScores.back().saveToFile("scores.txt");
    }

    cout << "Score enregistré ! Merci d’avoir joué, " << name << " !" << endl;
}



void Game::displayLeadBoard()
{
    vector<Scores> fileScores;

    ifstream file("scores.txt"); // ouvre le fichier

    if (!file)
    {
        cout << "Impossible d'ouvrir le fichier des scores." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {

        string name;
        int time;

        std::istringstream iss(line);
        if (iss >> name >> time) {
            fileScores.emplace_back(name, time);
        }

    }
    file.close();

    // tri meilleur temps
    sort(fileScores.begin(), fileScores.end(), [](const Scores& a, const Scores& b)
    {
        return a.getItsTime() < b.getItsTime();
    });

    cout << "===== CLASSEMENT =====" << endl;
    int rank = 1;

    for (const auto& score : fileScores) {
        cout << setw(2) << rank++ << ". "
             << setw(10) << score.getItsName()
             << " - Temps : " << score.getItsTime() << "s" << endl;
        if (rank > 4) break; // affiche les 4 meilleurs
    }
}

void Game::addTime(string name, int time)
{
    itsScores.push_back(Scores(name, time));
}

QElapsedTimer Game::getChrono(){
    return itschrono;
}

Room &Game::getCurrentRoom()
{

        Donjon& currentDonjon = getCurrentDonjon();  // Récupère le donjon actuel
        return currentDonjon.getItsCurrentRoom();   // Récupère la salle courante de ce donjon
    }

void Game::pickUpNearbyItem(Room& room) {
    auto& items = room.getItsItems();
    QRect playerHitbox = itsPlayer->getItsPlayerHitbox();

    for (auto it = items.begin(); it != items.end(); ++it) {
        Item* item = *it;

        // Vérifie la proximité
        if (playerHitbox.intersects(item->getItsItemHitbox())) {
            // Vérifie si c'est un item ramassable
            itemType type = item->getItsItemType();

            if (type == sword || type == life && itsPlayer->getItsPv()<3 || type == key) {
                if (type == life ) {
                    itsPlayer->addPv();
                } else if (type == sword) {
                    itsPlayer->setHasSword();          // ✅ Marque qu'on a l'épée
                    //itsPlayer->getItsSpritePlayer();    // ✅ Met à jour le sprite du joueur
                }else if (type == key){
                    Key* aKey = dynamic_cast<Key*>(item);
                    getCurrentDonjon().openDoor(aKey);

                }

                delete item;
                items.erase(it);
                break;
            }
        }
    }
}

void Game::update() {
    // Mettre à jour les actions de chaque ennemi
    for (auto it = getCurrentRoom().getItsItems().begin(); it != getCurrentRoom().getItsItems().end();) {
        if ((*it)->getItsItemType() == orc || (*it)->getItsItemType() == skeleton) {  // vérifier si l'item est un ennemi
            Enemy* enemy = dynamic_cast<Enemy*>(*it);
            if (enemy) {
                // L'ennemi attaque le joueur
                enemy->attack(*itsPlayer);

                // Si l'ennemi est mort
                if (enemy->getPv() <= 0) {
                    enemy->die();  // Appel de la méthode de mort de l'ennemi
                    // Supprimer l'ennemi de la liste des items de la salle
                    it = getCurrentRoom().getItsItems().erase(it);
                    continue;  // On ne veut pas d'incrémentation ici, car on a déjà effacé un élément
                }
            }
        }
        ++it;  // Continue d'itérer si l'ennemi n'est pas mort
    }
}



void Game::specialColision() {
    QRect hitbox = itsPlayer->getItsPlayerHitbox();

    for (Item* item : getCurrentDonjon().getItsCurrentRoom().getItsItems()) {
        if (!item) continue;

        // Gérer l'invincibilité du joueur
        if ((itschrono.elapsed() / 1000) - lastIFrame > itsPlayer->getItsIframe() && itsPlayer->getItsInv() == true) {
            itsPlayer->changeInvicibility(false);
            lastIFrame = itschrono.elapsed() / 1000;
        }

        // Gérer l'attaque de l'épée du joueur
        if ((itschrono.elapsed() / 1000) - lastUseSword > 0.7 && itsPlayer->getItsUseSword() == true) {
            itsPlayer->setUseSword(false);
            lastUseSword = itschrono.elapsed() / 1000;
        }

        // Si l'objet est une porte
        if (item->getItsItemType() == door) {
            Door* aDoor = dynamic_cast<Door*>(item);
            if (aDoor->getIsOpen() == 1 && hitbox.intersects(item->getItsItemHitbox())) {
                getCurrentDonjon().setCurrentRoom(aDoor->getNextRoom());
                direction aDir = itsPlayer->getItsDirection();
                if (aDir == north) {
                    itsPlayer->setPos(300, 500);
                } else if (aDir == south) {
                    itsPlayer->setPos(300, 100);
                } else if (aDir == east) {
                    itsPlayer->setPos(50, 300);
                } else if (aDir == west) {
                    itsPlayer->setPos(500, 300);
                }
            }
        }

        // Si l'objet est un ennemi (orc) et que le joueur est invincible
        else if (item->getItsItemType() == orc && itsPlayer->getItsInv() == false) {
            Enemy* aEnemy = dynamic_cast<Enemy*>(item);

            // Si l'ennemi n'est pas invincible et que le joueur entre en collision avec lui
            if (aEnemy && !aEnemy->getIsInvincible() && hitbox.intersects(item->getItsItemHitbox())) {
                itsPlayer->takeDamage(aEnemy->getItsDamage());
                itsPlayer->changeInvicibility(true);

                // L'ennemi devient invincible pendant un certain temps
                aEnemy->setInvincible(true);
                aEnemy->setIFrame(itschrono.elapsed() / 1000);  // Enregistrer le temps de l'I-Frame
            }
        }

        // Si l'objet est du magma et que le joueur est invincible
        else if (item->getItsItemType() == magma && itsPlayer->getItsInv() == false) {
            if (hitbox.intersects(item->getItsItemHitbox())) {
                itsPlayer->takeDamage(item->getItsDamage());
                itsPlayer->changeInvicibility(true);
            }
        }
    }

    // Mise à jour de l'I-Frame des ennemis après chaque collision
    for (Item* item : getCurrentDonjon().getItsCurrentRoom().getItsItems()) {
        if (item->getItsItemType() == orc) {  // Si c'est un ennemi
            Enemy* aEnemy = dynamic_cast<Enemy*>(item);
            if (aEnemy) {
                // Mise à jour de l'invincibilité de l'ennemi selon le temps écoulé
                double deltaTime = itschrono.elapsed() / 1000.0 - aEnemy->getIFrame();
                aEnemy->updateIFrame(deltaTime);  // Mettre à jour l'invincibilité de l'ennemi
            }
        }
    }
}
