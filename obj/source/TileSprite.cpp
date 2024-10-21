#include "../header/TileSprite.h"

TileSprite::TileSprite(int type, int width, int height, QString image_uri, int s_x, int s_y) {
    // Depending on the type, load the specified tile.
    switch(type){
    case -1:
        this->setPixmap(QPixmap(image_uri).scaled(s_x, s_y));
        this->walk = false;
        this->grass = false;
        break;
    case 1:
        this->setPixmap(QPixmap(":/graphics/Sprites/GROUND DETAIL 1 - DAY.png"));
        this->walk = true;
        this->grass = false;
        break;
    case 2:
        this->setPixmap(QPixmap(":/graphics/Sprites/HOUSE 2 - DAY.png"));
        this->walk = false;
        this->grass = false;
        break;
    case 3:
        this->setPixmap(QPixmap(":/graphics/Sprites/GRASS DETAIL 3 - DAY.png"));
        this->walk = true;
        this->grass = true;
        break;
    case 4:
        this->setPixmap(QPixmap(":/graphics/Sprites/FENCE 2 - DAY.png"));
        this->setTransformOriginPoint(8,8);
        this->setRotation(180);
        this->walk = false;
        this->grass = false;
        break;
    case 5:
        this->setPixmap(QPixmap(":/graphics/Sprites/TREE 3 - DAY.png"));
        this->walk = false;
        this->grass = false;
        break;
    case 6:
        this->setPixmap(QPixmap(":/graphics/Sprites/WATER TILE - NIGHT.png"));
        this->walk = false;
        this->grass = false;
        break;
    case 7:
        this->setPixmap(QPixmap(":/graphics/Sprites/TERRAIN SET 3 CURVES - DAY.png"));
        this->walk = false;
        this->grass = false;
        break;
    case 8:
        this->setPixmap(QPixmap(":/graphics/Sprites/TERRAIN SET 3 CURVES - DAY.png"));
        this->setTransformOriginPoint(16,16);
        this->setRotation(90);
        this->walk = false;
        this->grass = false;
        break;
    case 9:
        this->setPixmap(QPixmap(":/graphics/Sprites/TERRAIN SET 2 - DAY.png").scaled(16, 16));
        this->walk = true;
        this->grass = false;
        break;
    default:
        break;
    }

    // All cases set the position of the sprite and its z value to 0.
    if(width > -1 && height > -1)
        this->setPos(width, height);
    this->setZValue(0);
}

TileSprite::~TileSprite(){

}

bool TileSprite::is_walkable() const{
    return this->walk;
}

bool TileSprite::is_grass() const{
    return this->grass;
}
