#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "./BattleButton.h"

// Each text will have an id.
// 1 = A wild {pokemon} appeared
// 2 = battle-based text ({Pokemon} used {move}), (Super effective), etc.
class TextButton : public BattleButton{
    Q_OBJECT
private:

public:
    TextButton(QString, int, int, int = 144, int = 80);


    void keyPressEvent(QKeyEvent*);
};

#endif // TEXTBUTTON_H
