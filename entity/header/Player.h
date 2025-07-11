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

    // have the Player take ownership of their own sprite
    CharacterSprite* character;
    bool is_player;

    // Generate a unique 6 digit id for the player at the start.
    const int id;
    QString name;

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
    bool has_all_pokemon_fainted() const;
    Pokemon* get_pokemon(int);
    QString get_name() const;

    // Actions
    void add_pokemon(Pokemon);
    void set_focus();
    void reset_stage_modifiers(int);
    void set_name(QString);

};

#endif // PLAYER_H
