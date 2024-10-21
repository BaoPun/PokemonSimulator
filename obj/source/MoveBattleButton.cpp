#include "../header/MoveBattleButton.h"

MoveBattleButton::MoveBattleButton(Move move, int top_x, int top_y, QColor color) : BattleButton(move.get_name(), top_x, top_y){
    // Main difference: specify a color for the move button (this represents the type)
    // And also store the current move.
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);       // Qt::DiagCrossPattern
    brush.setColor(color);
    this->setBrush(std::move(brush));
    this->change_text_color(QColor(0, 0, 0));
    this->move = move;
}

Move MoveBattleButton::get_move(){
    return this->move;
}

void MoveBattleButton::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Space){
        qDebug() << "From the button's key event," << move.get_name() << "was detected.";
    }
}
