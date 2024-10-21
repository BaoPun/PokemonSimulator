#ifndef POKEMON_H
#define POKEMON_H

#include "../../util/header/Database.h"
#include "./Nature.h"
#include "./Ability.h"
#include "./Move.h"
#include "./Item.h"

#include <QDebug>
#include <QRandomGenerator>

/**
 * @brief A generic Pokemon class with various characteristics:
 *
 * vector of up to two types (separate class for Type)
 * vector of abilities (separate class for Ability)
 * Nature
 * maybe make stats list for later? (HP, ATK, DEF, SPATK, SPDEF, SPD)
 */
class Pokemon
{
private:
    // Descriptor
    int dex_id;                                                         // (Will be in DB)
    QString name;                                                       // (Will be in DB)
    vector<Type> types;                                                 // (Will be in DB)
    vector<Ability> abilities;                                          // (Will be in DB)
    Nature nature;

    // Stats
    int level;                      // Between 1 and 100
    int current_exp;                // This is calculated after the level
    map<Stat, int> base;            // base stats (not the final display) (will be in DB)
    map<Stat, int> ev;              // EVS for each stat.  Up to 512, only 256 maximum per stat.
                                    // Every 4 EVS in 1 stat = +1 on final stat
    map<Stat, int> iv;              // IVS for each stat.  Cannot be modified (between 0 and 31)
    map<Stat, int> total;
    int current_hp;
    map<Stat, int> modifier;        // Stat modifiers for 7 stats   // -6 up to +6.  Base is 3/3

    // A sublist of Pokemon.  This is just different forms that the current pokemon has.
    vector<Pokemon> forms;          // Also in db.

    // Other notable stats
    // How much ev yield for each stat upon defeating this Pokemon
    map<Stat, int> yield;           // in DB

    // Base exp upon defeating this Pokemon
    int base_EXP;                   // (Will be in DB)

    // What type of experience gains?  Id pulled from database, but the vector is stored as a constant
    int exp_id;
    vector<int> exp_gains;

    // Base happiness, catch rate, whether or not a pokemon evolves into this one.
    int base_happiness;
    int catch_rate;
    int evolved_from_id;

    // List of moves the pokemon can learn and have currently learned (WIP)
    vector<Move> level_up;
    vector<Move> machine;
    vector<Move> tutor;
    vector<Move> egg;
    vector<Move> current_moves;

    /**
     * @brief Calculate the total stat points for all 6 stats.
     */
    void calculate_total_stats();

    // Updates (probability, list of learnable moves, and encounter)
    void update_probability(int);
    void set_learnable_moves(int, Database*);

    // Probability of the pokemon being encountered.  Differs per route
    // Whole number out of 100
    int probability= 0;

    // What status was the pokemon afflicted with?  Default is none
    Ailment status;

    // Does this pokemon belong to the player? (False by default)
    int trainer_id = -1;

public:
    /**
     * @brief Base constructor for a single Pokemon that will set the dex id to -1,
     * marking this as an invalid Pokemon.
     */
    Pokemon();
    /**
     * @brief Populate data for a given Pokemon via a given query and then
     * fetches information given that name.  Also passes in a nature, a level, preset evs, and prest ivs (all default)
     */
    Pokemon(QSqlRecord, NatureNames = HARDY, int = 50, vector<int> = {0,0,0,0,0,0},
            vector<int> = {QRandomGenerator::global()->bounded(0,32), QRandomGenerator::global()->bounded(0,32), QRandomGenerator::global()->bounded(0,32),
                            QRandomGenerator::global()->bounded(0,32), QRandomGenerator::global()->bounded(0,32), QRandomGenerator::global()->bounded(0,32)});

    // Repopulates pokemon data and/or adds additional information
    Pokemon* repopulate_data(int, int, Database*);
    void add_learnable_move(QSqlRecord);


    // Getters
    int get_dex_id();
    QString get_name();
    int get_level();
    int get_base_exp();
    int get_base(Stat);
    int get_yield(Stat);
    int get_ev(Stat);
    int get_iv(Stat);
    int get_total(Stat);
    int get_num_moves_learned_by(Method);   // number of moves learned via a given method
    int get_probability();
    double get_modifier(Stat);
    vector<Type> get_types();
    int get_current_hp();
    Move& get_current_move(int);
    Ailment get_status_ailment();
    int get_num_current_moves();
    vector<Move> get_current_moves();
    bool is_owned_by_trainer();


    // When encountering a pokemon from the wild or as a gift, change the level.
    // In most cases, the nature will also be randomized, but may be given in special circumstances
    Pokemon* encounter(int, int = QRandomGenerator::global()->bounded(0,25));
    Pokemon* update_owner(int);

    // Change the stat modifier
    void change_modifier(Stat, int);

    // Move calculations
    bool is_move_stab(Type);

    // Modify the hp once struck
    void taken_damage(int);

    // Invalidate the pokemon by setting the id to -1
    void invalidate_pokemon();


    // DEBUG: print stats of pokemon to make sure data came through just fine.
    void print_total_stats();
    void print_battle_stats();
};

#endif // POKEMON_H
