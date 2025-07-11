#ifndef FIELD_H
#define FIELD_H

#include "./Pokemon.h"

struct PokemonUsedMove{
    Pokemon* pokemon;
    Move* move;
    int target;     // 1-4; 1=ally1, 2=opponent1, 3=ally2, 4=opponent2
    int type;       // 1-4; 1=ally1, 2=opponent1, 3=ally2, 4=opponent2

    PokemonUsedMove(){
        this->pokemon = nullptr;
        this->move = nullptr;
    }

    void load_pokemon(Pokemon* pokemon, int type){
        this->pokemon = pokemon;
        this->type = type;
    }

    void load_move(Move* move){
        this->move = move;
    }

    QString get_action_text(){
        return QString("%1 used %2!").arg(this->pokemon->get_name(), this->move->get_name());
    }

    void clear_pokemon(){
        this->pokemon = nullptr;
        this->move = nullptr;
    }

    bool exists(){
        return this->pokemon != nullptr && this->move != nullptr;
    }

    bool operator>(const PokemonUsedMove& other) const{
        if(this->move->get_priority_level() > other.move->get_priority_level())
            return true;
        else if(this->move->get_priority_level() > other.move->get_priority_level()){
            if(this->pokemon->get_total(SPEED) > other.pokemon->get_total(SPEED))
                return true;

            // In the event of a speed tie, do a coin flip.
            else if(this->pokemon->get_total(SPEED) == other.pokemon->get_total(SPEED))
                return QRandomGenerator::global()->bounded(0, 2) == 0 ? true : false;
        }
        return false;
    }
};

class Field{
private:
    PokemonUsedMove ally1;
    PokemonUsedMove ally2;
    PokemonUsedMove opponent1;
    PokemonUsedMove opponent2;

    bool is_double;

    // Actions to attack
    void ally1_attack();
    void opponent1_attack();

    // The field will also determine the move order of the involved Pokemon
    vector<PokemonUsedMove> move_order;


public:
    Field();

    void clear_single_field();
    void clear_double_field();

    void load_single_battle(Pokemon*, Pokemon*);
    void load_ally1_move(Move*);
    void load_opponent1_move(Move*);

    //Pokemon* get_pokemon_from_target(int);

    Pokemon* get_ally1_pokemon();
    Move* get_ally1_move();

    Pokemon* get_opponent1_pokemon();
    Move* get_opponent1_move();

    // Get top move.
    Move* get_top_move();
    int get_top_move_type();
    PokemonUsedMove get_top_move_order();


    bool is_single_battle();
    bool is_double_battle();

    // Method to determine move order.
    vector<PokemonUsedMove> determine_move_order();
    void remove_top_move();

    // Use top move

    // Get # of moves remaining from move order
    int num_moves_left_order();


};

#endif // FIELD_H
