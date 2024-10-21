#ifndef PLAYER_H
#define PLAYER_H

#include "../../obj/header/CharacterSprite.h"
#include "./Pokemon.h"

/**
 * @brief A Player that represents us.  A player owns up to 6 pokemon and can hold multiple items
 */
class Player : public QObject
{
    Q_OBJECT
private:
    vector<Pokemon> party;
    int num_party;

    // TODO: have the Player take ownership of their own sprite
    CharacterSprite* character;
    bool is_player;

    // TODO later: Also add a list of items the player owns

public:
    Player(int, int, bool = true);
    ~Player();

    // Getters for the sprite
    CharacterSprite* get_sprite();
    QList<QGraphicsItem*> getCollidingItems();

    // Getters
    int get_num_pokemon() const;
    bool is_party_full() const;
    Pokemon* get_pokemon(int);

    // Actions
    void add_pokemon(Pokemon);
    void set_focus();

};

#endif // PLAYER_H
