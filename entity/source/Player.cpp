#include "../header/Player.h"

Player::Player(int max_width, int max_height, bool is_player) : character(new CharacterSprite(max_width, max_height)) {
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
 * @brief Retrieve the pokemon at the given position
 * @return
 */
Pokemon* Player::get_pokemon(int idx){
    return (idx >= 0 && idx < this->num_party) ? &this->party[idx] : nullptr;
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
