#ifndef BATTLEBUTTON_H
#define BATTLEBUTTON_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QFont>
#include <QKeyEvent>

class BattleButton : public QObject, public QGraphicsRectItem{
    Q_OBJECT
private:
    QGraphicsTextItem* content;

    // TODO: add a sound effect

protected:
    qreal get_text_width();
    qreal get_text_height();
    void set_text_pos(qreal, qreal);

public:
    BattleButton(QString, int, int);
    ~BattleButton();

    QString get_text();

    bool is_bold();
    void setBold(bool);

    void update_content(QString);
    void change_text_color(QColor);
    void change_text_font(int);
    bool is_valid_move();

    virtual void keyPressEvent(QKeyEvent*);

};

#endif // BATTLEBUTTON_H
