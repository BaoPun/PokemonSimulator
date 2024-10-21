#include "../header/CharacterSprite.h"

CharacterSprite::CharacterSprite(int max_width, int max_height){
    this->max_width = max_width;
    this->max_height = max_height;
}

/**
 * @brief CustomRectItem::keyPressEvent
 * @param keyEvent
 */
void CharacterSprite::keyPressEvent(QKeyEvent* keyEvent){
    // Move 16 pixels in a certain direction
    if(keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_A){
        if(this->x() - 16 >= 0){
            this->setPos(this->x() - 16, this->y());

            // But if this collides with a tile, undo the direction
            QList<QGraphicsItem*> collision = this->collidingItems();
            for(size_t i = 0; i < collision.size(); i++){
                auto& item = *collision[i];
                if(typeid(item) == typeid(TileSprite) && !qgraphicsitem_cast<TileSprite*>(collision[i])->is_walkable()){
                    this->setPos(this->x() + 16, this->y());
                    break;
                }
            }

        }
        // EMIT SIGNAL
        Q_EMIT this->post_move();
    }
    else if(keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_D){
        if(this->x() + 16 + this->pixmap().width() <= this->max_width){
            this->setPos(this->x() + 16, this->y());

            // But if this collides with a tile, undo the direction
            QList<QGraphicsItem*> collision = this->collidingItems();
            for(size_t i = 0; i < collision.size(); i++){
                auto& item = *collision[i];
                if(typeid(item) == typeid(TileSprite) && !qgraphicsitem_cast<TileSprite*>(collision[i])->is_walkable()){
                    this->setPos(this->x() - 16, this->y());
                    break;
                }
            }
        }
        // EMIT SIGNAL
        Q_EMIT this->post_move();
    }
    else if(keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_W){
        if(this->y() - 16 >= 0){
            this->setPos(this->x(), this->y() - 16);

            // But if this collides with a tile, undo the direction
            QList<QGraphicsItem*> collision = this->collidingItems();
            for(size_t i = 0; i < collision.size(); i++){
                auto& item = *collision[i];
                if(typeid(item) == typeid(TileSprite) && !qgraphicsitem_cast<TileSprite*>(collision[i])->is_walkable()){
                    this->setPos(this->x(), this->y() + 16);
                    break;
                }
            }
        }
        // EMIT SIGNAL
        Q_EMIT this->post_move();
    }
    else if(keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_S){
        if(this->y() + 16 + this->pixmap().height() <= this->max_height){
            this->setPos(this->x(), this->y() + 16);

            // But if this collides with a tile, undo the direction
            QList<QGraphicsItem*> collision = this->collidingItems();
            for(size_t i = 0; i < collision.size(); i++){
                auto& item = *collision[i];
                if(typeid(item) == typeid(TileSprite) && !qgraphicsitem_cast<TileSprite*>(collision[i])->is_walkable()){
                    this->setPos(this->x(), this->y() - 16);
                    break;
                }
            }
        }
        // EMIT SIGNAL
        Q_EMIT this->post_move();
    }



    // Print out coordinates of player
    //qDebug() << this->x() << "," << this->y();
}
