#include "../header/Ability.h"

Ability::Ability(int id, QString name, QString effect, bool is_hidden) {
    this->id = id;
    this->name = name;
    this->effect = effect;
    this->is_hidden = is_hidden;
}

int Ability::get_id(){
    return this->id;
}

QString Ability::get_name(){
    return this->name;
}

QString Ability::get_effect(){
    return this->effect;
}

bool Ability::is_ability_hidden(){
    return this->is_hidden;
}
