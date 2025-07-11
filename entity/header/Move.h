#ifndef MOVE_H
#define MOVE_H

#include "../../util/header/Database.h"
#include "./Type.h"
#include <QString>

/**
 * @brief An enum representing the 8 different stat types.
 */
enum Stat{
    HP, ATK, DEF, SP_ATK, SP_DEF, SPEED, ACCURACY, EVASION
};

enum DamageClass{
    PHYSICAL, SPECIAL, STATUS, DAMAGE_CLASS_ERROR
};

enum Target{
    RANDOM_OPPONENT, ALL_OPPONENTS,
    OPPONENTS_FIELD, SPECIFIC_MOVE,
    SELECTED_POKEMON, USER_AND_ALLIES,
    SELECTED_POKEMON_MAX,
    ENTIRE_FIELD, FAINTING_POKEMON,
    USER, ALLY, ALL_ALLIES,
    USER_FIELD, ALL_OTHER_POKEMON,
    USER_OR_ALLY, ALL_POKEMON, TARGET_ERROR
};

enum Ailment{
    BURN, PARALYSIS, FREEZE, SLEEP,
    TRAP, POISON_, CONFUSION,
    YAWN, PERISH_SONG, DISABLE,
    LEECH_SEED, TAR_SHOT,
    TORMENT, INGRAIN, UNKNOWN_AILMENT,
    INFATUATION, SILENCE,
    NONE, AILMENT_ERROR
};

enum Method{
    LEVEL_UP, MACHINE, TUTOR, EGG, METHOD_ERROR
};

// Helper functions to convert from QString to various enums
DamageClass convert_to_damage_class(QString);
Target convert_to_target(QString);
Ailment convert_to_ailment(QString);
Method convert_to_method(QString);

// Helper functions to convert from given enum to String
QString damage_class_to_string(DamageClass);
QString stat_to_string(Stat);



class Move
{
private:
    int id;
    QString name;
    QString description;
    DamageClass damage_class;
    Type type;
    Target target;
    int power;
    int accuracy;
    int current_pp;
    int max_pp;
    int priority_level;
    int effect_chance;

    map<Stat, int> stat_change;   // 8; 6 from HP-SPD, 2 from accuracy and evasion

    Ailment ailment;
    int ailment_chance;
    int crit_bonus;
    int drain;
    int flinch;
    int stat_change_chance;
    int min_hits;
    int max_hits;
    int min_turns;
    int max_turns;
    Method method;
    int level_learned;


public:
    Move();
    Move(QSqlRecord);

    int get_id();
    QString get_name();
    QString get_description();
    DamageClass get_damage_class();
    Type get_type();
    Target get_target();
    int get_power();
    int get_accuracy();
    int get_current_pp();
    int get_max_pp();
    int get_priority_level();
    int get_effect_chance();

    int get_stat_change_at(Stat);

    Ailment get_ailment();
    int get_ailment_chance();
    int get_crit_bonus();
    int get_drain();
    int get_flinch();
    int get_stat_change_chance();
    int get_min_hits();
    int get_max_hits();
    int get_min_turns();
    int get_max_turns();
    Method get_method();
    int get_level_learned();

    // overloading ==
    bool operator==(const Move&);
};

#endif // MOVE_H
