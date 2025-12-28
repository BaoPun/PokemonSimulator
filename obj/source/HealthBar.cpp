#include "../header/HealthBar.h"

HealthBar::HealthBar(int current_hp, int max_hp, int x, int y){
    this->health_bar = new QProgressBar();
    this->health_bar->setMaximum(max_hp);
    this->health_bar->setValue(current_hp);
    this->proxy = new QGraphicsProxyWidget();
    this->proxy->setWidget(this->health_bar);
    this->proxy->setPos(x, y);
}

HealthBar::~HealthBar(){
    if(this->proxy != nullptr){
        delete this->proxy;
        this->proxy = nullptr;
    }
}

void HealthBar::set_current_hp(int current_hp){
    this->health_bar->setValue(current_hp);
}

QGraphicsProxyWidget* HealthBar::get_proxy(){
    return this->proxy;
}
