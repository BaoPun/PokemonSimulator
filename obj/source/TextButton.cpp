#include "../header/TextButton.h"

TextButton::TextButton(QString content, int top_x, int top_y, int x, int y) : BattleButton(content, top_x, top_y){
    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);       // Qt::DiagCrossPattern
    brush.setColor(QColor(128, 255, 4));
    this->setBrush(std::move(brush));
    this->change_text_color(QColor(0, 0, 0));
    this->change_text_font(24);

    // Update the text coordinates
    qreal p_x = ((top_x + (top_x + x - this->get_text_width())) / 2);
    qreal p_y = ((top_y + (top_y + y - this->get_text_height())) / 2);
    this->set_text_pos(p_x, p_y);
    this->setRect(top_x, top_y, x, y);
}

void TextButton::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Space){
        qDebug() << "From TextButton, space was detected.";
    }
}
