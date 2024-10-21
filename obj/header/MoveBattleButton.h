#ifndef MOVEBATTLEBUTTON_H
#define MOVEBATTLEBUTTON_H

#include "./BattleButton.h"
#include "../../entity/header/Move.h"

class MoveBattleButton : public BattleButton{
    Q_OBJECT
private:
    Move move;
public:
    MoveBattleButton(Move, int, int, QColor);

    Move get_move();

    void keyPressEvent(QKeyEvent*);
};

#endif // MOVEBATTLEBUTTON_H
