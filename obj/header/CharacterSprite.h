#ifndef CHARACTERSPRITE_H
#define CHARACTERSPRITE_H

//#include <QGraphicsRectItem>
#include "./TileSprite.h"
#include <QKeyEvent>

class CharacterSprite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int max_width, max_height;

signals:
    void post_move();

public:
    CharacterSprite(int, int);
    // Override so that we can trigger on key presses
    void keyPressEvent(QKeyEvent*);
};

#endif // CHARACTERSPRITE_H
