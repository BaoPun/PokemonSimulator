#include "../header/BattleButton.h"

BattleButton::BattleButton(QString content, int top_x, int top_y){
    // Draw the button
    this->setRect(top_x, top_y, 144, 80);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(76, 243, 243));
    this->setBrush(std::move(brush));

    // Add text to the button
    this->content = new QGraphicsTextItem(content, this);
    qreal p_x = ((top_x + (top_x + 144 - this->content->boundingRect().width())) / 2);
    qreal p_y = ((top_y + (top_y + 80 - this->content->boundingRect().height())) / 2);
    this->content->setPos(p_x, p_y);
    this->setBold(true);
    this->change_text_color(QColor(0, 0, 0));
}

BattleButton::~BattleButton(){
    if(this->content != nullptr)
        delete this->content;
}

QString BattleButton::get_text(){
    return this->content->toPlainText();
}

void BattleButton::setBold(bool isBold){
    if(isBold){
        QFont bold;
        bold.setBold(true);
        this->content->setFont(std::move(bold));
    }
    else{
        QFont bold;
        bold.setBold(false);
        this->content->setFont(std::move(bold));
    }
}

bool BattleButton::is_bold(){
    return this->content->font().weight() == QFont::Bold;
}

void BattleButton::update_content(QString content){
    this->content->setPlainText(content);
}

void BattleButton::change_text_color(QColor color){
    this->content->setDefaultTextColor(color);
}

void BattleButton::change_text_font(int font_size){
    QFont font = this->content->font();
    font.setPointSize(font_size);
    this->content->setFont(font);
}

bool BattleButton::is_valid_move(){
    return this->content->toPlainText() != "N/A";
}

void BattleButton::keyPressEvent(QKeyEvent* event){
    qDebug() << "From BattleButton.";
    if(event->key() == Qt::Key_Space){
        qDebug() << "Space detected.";
    }
}

qreal BattleButton::get_text_width(){
    return this->content->boundingRect().width();
}

qreal BattleButton::get_text_height(){
    return this->content->boundingRect().height();
}

void BattleButton::set_text_pos(qreal x, qreal y){
    this->content->setPos(x, y);
}

