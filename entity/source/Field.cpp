#include "../header/Field.h"

Field::Field(){
    // By default, make this be single battle
    this->is_double = false;
}

void Field::clear_single_field(){
    this->ally1.clear_pokemon();
    this->opponent1.clear_pokemon();
}

void Field::clear_double_field(){
    this->clear_single_field();
    this->ally2.clear_pokemon();
    this->opponent2.clear_pokemon();
}

void Field::load_single_battle(Pokemon* user, Pokemon* enemy){
    this->ally1.load_pokemon(user, 1);
    this->opponent1.load_pokemon(enemy, 2);
}

void Field::load_ally1_move(Move* move){
    this->ally1.load_move(move);

    if(this->is_single_battle()){
        if(move->get_target() == RANDOM_OPPONENT || move->get_target() == ALL_OPPONENTS
            || move->get_target() == SELECTED_POKEMON || move->get_target() == OPPONENTS_FIELD
            || move->get_target() == ALL_OTHER_POKEMON){
            this->ally1.target = 2;
        }
        else if(move->get_target() == USER_AND_ALLIES || move->get_target() == USER
                   || move->get_target() == ENTIRE_FIELD){
            this->ally1.target = 1;
        }
    }
}

void Field::load_opponent1_move(Move* move){
    this->opponent1.load_move(move);

    if(this->is_single_battle()){
        if(move->get_target() == RANDOM_OPPONENT || move->get_target() == ALL_OPPONENTS
            || move->get_target() == SELECTED_POKEMON || move->get_target() == OPPONENTS_FIELD
            || move->get_target() == ALL_OTHER_POKEMON){
            this->opponent1.target = 2;
        }
        else if(move->get_target() == USER_AND_ALLIES || move->get_target() == USER
                 || move->get_target() == ENTIRE_FIELD){
            this->opponent1.target = 1;
        }
    }
}

Pokemon* Field::get_ally1_pokemon(){
    return this->ally1.pokemon;
}

Move* Field::get_ally1_move(){
    return this->ally1.move;
}

Pokemon* Field::get_opponent1_pokemon(){
    return this->opponent1.pokemon;
}

Move* Field::get_opponent1_move(){
    return this->opponent1.move;
}

Move* Field::get_top_move(){
    return this->move_order.front().move;
}

int Field::get_top_move_type(){
    return this->move_order.front().type;
}

PokemonUsedMove Field::get_top_move_order(){
    return this->move_order.front();
}

void Field::remove_top_move(){
    this->move_order.erase(this->move_order.begin());
}

void Field::ally1_attack(){
    // If single battle, then things are easy: either target user or opponent
    if(this->is_single_battle()){
        // Is this a status move?
        if(this->ally1.move->get_damage_class() == STATUS){

        }

        // Or is it a damaging move?
        else{

        }
    }
}

void Field::opponent1_attack(){
    // If single battle, then things are easy: either target user or opponent
    if(this->is_single_battle()){

    }
}

vector<PokemonUsedMove> Field::determine_move_order(){
    vector<PokemonUsedMove> order;

    // Add both ally1 and opponent1 by default
    order.push_back(this->ally1);
    order.push_back(this->opponent1);

    // If double battle, also add ally2 and opponent2
    if(this->is_double_battle()){
        order.push_back(this->ally2);
        order.push_back(this->opponent2);
    }

    // Then, begin sorting.
    // Priority first, and then user's speed.
    std::sort(order.begin(), order.end(), std::greater<PokemonUsedMove>());

    // Return the order.
    this->move_order = order;
    return this->move_order;
}

bool Field::is_single_battle(){
    return !this->is_double;
}

bool Field::is_double_battle(){
    return this->is_double;
}




int Field::num_moves_left_order(){
    return this->move_order.size();
}
