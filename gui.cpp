#include "gui.h"

gui::gui(QWidget *parent, Game* aGame)
    : QWidget(parent), itsGame(aGame)  // conserve le pointeur passé
{
    setFixedSize(600, 700);
    itsTimer.start(16);
    connect(&itsTimer, &QTimer::timeout, this, QOverload<>::of(&gui::update));
}

void gui::update() {
    if (itsGame) {
        itsGame->update();  // Appelle la méthode update de la classe Game
        repaint();  // Redessine l'écran après chaque mise à jour
    }
}

gui::~gui() {}


Game *gui::getItsGame() const
{
    return itsGame;
}
void gui::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false); // pas de lissage

    // Affichage du fond
    QImage image(":/Tiles/Room.png");
    image = image.scaled(600, 600, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    QPixmap background = QPixmap::fromImage(image);
    painter.drawPixmap(0, 100, background);

    // Affichage des items
    if (!itsGame) return;

    Donjon& donjon = itsGame->getCurrentDonjon();
    Room& room = donjon.getItsCurrentRoom();

    for (Item* item : room.getItsItems()) {
        if (!item) continue;

        // Obtenir et redimensionner le sprite
        QPixmap sprite = item->getItsSpriteItem();
        int x = item->getItsPositionX();
        int y = item->getItsPositionY();

        // Afficher le sprite
        sprite = sprite.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        painter.drawPixmap(x, y + 100, sprite);  // +100 pour tenir compte du HUD


    }

    itsGame->specialColision();

    // Affichage du joueur
    Player* player = itsGame->getItsPlayer();
    if (player) {
        QPixmap playerSprite = player->getItsSpritePlayer();
        playerSprite = playerSprite.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        int px = player->getItsPositionX();
        int py = player->getItsPositionY();
        painter.drawPixmap(px, py + 100, playerSprite);

        // Affichage de l'attaque de l'épée
        if (player->getItsUseSword()) {
            QRect attackHitbox = player->getAttackHitbox();

        }
    }


    // Affichage du HUD (identique à ce que tu avais)
    QRect rect(0, 0, 600, 100);
    QPixmap hudBack(":/Menu/HudBack.png");
    painter.drawPixmap(rect, hudBack);

    painter.setPen(Qt::white);
    QFont pixelFont("Pixel Emulator", 15);
    painter.setFont(pixelFont);
    string name = itsGame->getCurrentDonjon().getItsName() + to_string(itsGame->getCurrentDonjon().getItsCurrentRoom().getItsNumber());
    QString qName = QString::fromStdString(name);
    painter.drawText(QPoint(20, 60), qName);

    QString time =  QString::fromStdString(to_string(itsGame->getChrono().elapsed()/1000) + " second");
    painter.drawText(QPoint(250, 60), time);

    int aX=540, aY=35;
    int heartSize = 40;
    for(int pv = 0 ; pv<itsGame->getItsPlayer()->getItsPv(); ++pv)
    {
        painter.drawPixmap(aX, aY, heartSize, heartSize, QPixmap(":/Item/Hearth.png"));
        aX -= (heartSize + 10);
    }
}


void gui::keyPressEvent(QKeyEvent *event) {
    Player* player = itsGame->getItsPlayer();
    if (!player) return;

    Room& room = itsGame->getCurrentDonjon().getItsCurrentRoom();
    const std::vector<Item*>& items = room.getItsItems();

    const int step = 10;


    switch (event->key()) {
    case Qt::Key_Up:
        if (!player->checkCollisionWithWalls(items, 0, -step))
            player->moveUp();
        break;
    case Qt::Key_Down:
        if (!player->checkCollisionWithWalls(items, 0, step))
            player->moveDown();
        break;
    case Qt::Key_Left:
        if (!player->checkCollisionWithWalls(items, -step, 0))
            player->moveLeft();
        break;
    case Qt::Key_Right:
        if (!player->checkCollisionWithWalls(items, step, 0))
            player->moveRight();
        break;
    case Qt::Key_R:
        itsGame->pickUpNearbyItem(room);  // 👉 Ramassage
        break;
    case Qt::Key_A:
        player->attackSword(itsGame);
    default:
        return;
    }
    itsGame->update();  // Appelle la mise à jour de l'état du jeu
    update();


}

