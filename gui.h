#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "game.h"
#include <QPixmap>
#include <QPaintEvent>

class gui : public QWidget
{
    Q_OBJECT
private :
    QTimer itsTimer;
    Game* itsGame;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    gui(QWidget *parent = nullptr, Game* aGame=nullptr);
    ~gui();
    void drawDonjon();
    void keyPressEvent(QKeyEvent *event) override;
    Game *getItsGame() const;
    void update();
};
#endif // GUI_H
