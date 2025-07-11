#include "../header/Player.h"

Player::Player(int max_width, int max_height, bool is_player) : character(new CharacterSprite(max_width, max_height)), id(999999) {
    this->num_party = 0;
    this->is_player = is_player;

    // Set properties of the character sprite representation
    if(this->is_player){
        this->character->setFlag(QGraphicsItem::ItemIsFocusable);
        this->character->setFocus();
        this->character->setPixmap(QPixmap(":/graphics/Sprites/idle.png").copy(QRect(0, 0, 128, 128)).scaled(QSize(64,64)));
        this->character->setPos(480, 400);
        this->character->setZValue(2);
    }
}

Player::~Player(){
    if(this->character != nullptr)
        delete this->character;

    qDebug() << "Player destructor done.";
}

CharacterSprite* Player::get_sprite(){
    return this->character;
}

QList<QGraphicsItem*> Player::getCollidingItems(){
    return this->character->collidingItems();
}

/**
 * @brief Function to return the # of pokemon in the party.
 * @return the # of pokemon in the party
 */
int Player::get_num_pokemon() const{
    return this->num_party;
}

/**
 * @brief Function to check if the party is full.
 * @return True if full (6 pokemon are occupied), False otherwise
 */
bool Player::is_party_full() const{
    return this->num_party == 6;
}

/**
 * @brief Function to determine if all pokemon in the player's party fainted.
 * @return True if all pokemon's hp hits 0, False otherwise
 */
bool Player::has_all_pokemon_fainted() const{
    for(size_t i = 0; i < this->num_party; i++){
        if(this->party.at(i).get_current_hp() > 0)
            return false;
    }
    return true;
}

/**
 * @brief Retrieve the pokemon at the given position
 * @return
 */
Pokemon* Player::get_pokemon(int idx){
    return (idx >= 0 && idx < this->num_party) ? &this->party[idx] : nullptr;
}

QString Player::get_name() const{
    return this->name;
}

/**
 * @brief If the party is not full, add the pokemon to the party.
 * @param pokemon - a Pokemon to add to the party
 */
void Player::add_pokemon(Pokemon pokemon){
    if(!this->is_party_full()){
        this->party.push_back(pokemon);
        ++this->num_party;
    }
}

void Player::set_focus(){
    this->character->setFocus();
}

/**
 * @brief After battle or when the pokemon is switched out, reset stage changes to 0
 */
void Player::reset_stage_modifiers(int idx){
    this->party.at(idx).reset_modifiers();
}

void Player::set_name(QString name){
    this->name = name;
}
