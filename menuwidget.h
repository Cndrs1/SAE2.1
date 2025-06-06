#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QKeyEvent>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void startGameRequested();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    enum State { ShowingMenu, ShowingStory };
    State state;
    QPixmap menuPixmap;
    QPixmap storyPixmap;
};

#endif // MENUWIDGET_H
