#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsProxyWidget>
#include <QProgressBar>
#include <QGraphicsPixmapItem>

class HealthBar : public QGraphicsPixmapItem{
private:
    QProgressBar* health_bar;
    QGraphicsProxyWidget* proxy;

public:
    HealthBar(int, int, int, int);
    ~HealthBar();

    void set_current_hp(int);
    QGraphicsProxyWidget* get_proxy();

};

#endif // HEALTHBAR_H
