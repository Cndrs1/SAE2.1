#include <QApplication>
#include <QFontDatabase>
#include <QPainter>
#include "menuwidget.h"
#include "gui.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set Font for Hud and other screen.
    int id = QFontDatabase::addApplicationFont(":/Font/Pixel Emulator.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);


    // Create the menu widget (initial screen)
    MenuWidget *menu = new MenuWidget();

    // When Enter is pressed in the menu, start the game
    QObject::connect(menu, &MenuWidget::startGameRequested, [&]() {
        Game *game = new Game();
        gui *gameGui = new gui(nullptr, game);
        gameGui->show();
        menu->hide();
        gameGui->setFocus(); // So it gets keyboard input
    });

    menu->show();

    return app.exec();
}
