#include "menuwidget.h"
#include <QPainter>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent),
    state(ShowingMenu),
    menuPixmap(":/Menu/menu.png"),
    storyPixmap(":/Menu/Story screen.png")
{
    setFixedSize(600, 700);
}

void MenuWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    QSize widgetSize = size();
    QPixmap pix = (state == ShowingMenu) ? menuPixmap : storyPixmap;
    painter.drawPixmap(rect(), pix.scaled(widgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MenuWidget::keyPressEvent(QKeyEvent *event)
{
    if (state == ShowingMenu) {
        if (event->key() == Qt::Key_H) {
            state = ShowingStory;
            update();
        }
        else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            emit startGameRequested(); // Lancer le jeu depuis le menu
        }
    }
    else if (state == ShowingStory) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            state = ShowingMenu;
            update();
        }
    }
}
