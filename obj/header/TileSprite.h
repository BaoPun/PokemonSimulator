#ifndef TILESPRITE_H
#define TILESPRITE_H

#include <QGraphicsPixmapItem>

class TileSprite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    bool walk;
    bool grass;

signals:
    void post_move();

public:
    TileSprite(int, int = -1, int = -1, QString = "", int = -1, int = -1);
    ~TileSprite();

    bool is_walkable() const;
    bool is_grass() const;
};

#endif // TILESPRITE_H
