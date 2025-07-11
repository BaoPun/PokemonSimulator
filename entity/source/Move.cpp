#include "../header/Move.h"

DamageClass convert_to_damage_class(QString damage_class){
    if(damage_class == "physical")
        return PHYSICAL;
    else if(damage_class == "special")
        return SPECIAL;
    else if(damage_class == "status")
        return STATUS;
    return DAMAGE_CLASS_ERROR;
}

Target convert_to_target(QString target){
    if(target == "random-opponent")
        return RANDOM_OPPONENT;
    else if(target == "all-opponents")
        return ALL_OPPONENTS;
    else if(target == "opponents-field")
        return OPPONENTS_FIELD;
    else if(target == "specific-move")
        return SPECIFIC_MOVE;
    else if(target == "selected-pokemon")
        return SELECTED_POKEMON;
    else if(target == "user-and-allies")
        return USER_AND_ALLIES;
    else if(target == "selected-pokemon-me-first")
        return SELECTED_POKEMON_MAX;
    else if(target == "entire-field")
        return ENTIRE_FIELD;
    else if(target == "fainting-pokemon")
        return FAINTING_POKEMON;
    else if(target == "user")
        return USER;
    else if(target == "ally")
        return ALLY;
    else if(target == "all-allies")
        return ALL_ALLIES;
    else if(target == "users-field")
        return USER_FIELD;
    else if(target == "all-other-pokemon")
        return ALL_OTHER_POKEMON;
    else if(target == "user-or-ally")
        return USER_OR_ALLY;
    else if(target == "all-pokemon")
        return ALL_POKEMON;
    else
        return TARGET_ERROR;
}

Ailment convert_to_ailment(QString ailment){
    if(ailment == "burn")
        return BURN;
    else if(ailment == "yawn")
        return YAWN;
    else if(ailment == "perish-song")
        return PERISH_SONG;
    else if(ailment == "poison")
        return POISON_;
    else if(ailment == "disable")
        return DISABLE;
    else if(ailment == "leech-seed")
        return LEECH_SEED;
    else if(ailment == "tar-shot")
        return TAR_SHOT;
    else if(ailment == "torment")
        return TORMENT;
    else if(ailment == "ingrain")
        return INGRAIN;
    else if(ailment == "confusion")
        return CONFUSION;
    else if(ailment == "unknown")
        return UNKNOWN_AILMENT;
    else if(ailment == "infatuation")
        return INFATUATION;
    else if(ailment == "sleep")
        return SLEEP;
    else if(ailment == "silence")
        return SILENCE;
    else if(ailment == "none")
        return NONE;
    else if(ailment == "paralysis")
        return PARALYSIS;
    else if(ailment == "trap")
        return TRAP;
    else if(ailment == "freeze")
        return FREEZE;
    return AILMENT_ERROR;
}

Method convert_to_method(QString method){
    if(method == "level-up")
        return LEVEL_UP;
    else if(method == "machine")
        return MACHINE;
    else if(method == "tutor")
        return TUTOR;
    else if(method == "egg")
        return EGG;
    else
        return METHOD_ERROR;
}

QString damage_class_to_string(DamageClass damage_class){
    switch(damage_class){
    case PHYSICAL:  return "Physical";
    case SPECIAL:   return "Special";
    case STATUS:    return "Status";
    default:        return "DAMAGE TYPE ERROR";
    }
}

QString stat_to_string(Stat stat){
    switch(stat){
    case HP:        return "HP";
    case ATK:       return "Attack";
    case DEF:       return "Defense";
    case SP_ATK:    return "Special Attack";
    case SP_DEF:    return "Special Defense";
    case SPEED:     return "Speed";
    case ACCURACY:  return "Accuracy";
    case EVASION:   return "Evasiveness";
    default:        return "ERROR";
    }
}

/**
 * @brief If a move were to be called via default, then it is automatically an invalid move.
 */
Move::Move(){
    this->id = -1;
    this->name = "N/A";
}

Move::Move(QSqlRecord record) {
    if(!record.isEmpty()){
        // Set up traits
        this->id = record.field(0).value().toInt();
        this->name = record.field(1).value().toString();
        this->description = record.field(2).value().toString();

        // For damage class, type, and target, convert to
        this->damage_class = convert_to_damage_class(record.field(3).value().toString());

        // Convert type id to enum
        this->type = id_to_type(record.field(4).value().toInt());

        // Target
        this->target = convert_to_target(record.field(5).value().toString());

        // More stats before the stat changes
        this->power = record.field(6).value().toInt();
        this->accuracy = record.field(7).value().toInt();
        this->max_pp = this->current_pp = record.field(8).value().toInt();
        this->priority_level = record.field(9).value().toInt();
        this->effect_chance = record.field(10).value().toInt();

        // 7 stat changes
        this->stat_change[ATK] = record.field(11).value().toInt();
        this->stat_change[DEF] = record.field(12).value().toInt();
        this->stat_change[SP_ATK] = record.field(13).value().toInt();
        this->stat_change[SP_DEF] = record.field(14).value().toInt();
        this->stat_change[SPEED] = record.field(15).value().toInt();
        this->stat_change[ACCURACY] = record.field(16).value().toInt();
        this->stat_change[EVASION] = record.field(17).value().toInt();

        // Ailment and ailment chance
        this->ailment = convert_to_ailment(record.field(18).value().toString());
        this->ailment_chance = record.field(19).value().toInt();

        // Remaining stats
        this->crit_bonus = record.field(20).value().toInt();
        this->drain = record.field(21).value().toInt();
        this->flinch = record.field(22).value().toInt();
        this->stat_change_chance = record.field(23).value().toInt();
        this->min_hits = record.field(24).value().toInt();
        this->max_hits = record.field(25).value().toInt();
        this->min_turns = record.field(26).value().toInt();
        this->max_turns = record.field(27).value().toInt();
        this->method = convert_to_method(record.field(28).value().toString());
        this->level_learned = record.field(29).value().toInt();

        //qDebug() << "Name of move:" << this->name;
    }
    else{
        qDebug() << "YIKES";
        this->id = -1;
    }
}

int Move::get_id(){
    return this->id;
}

QString Move::get_name(){
    return this->name;
}

QString Move::get_description(){
    return this->description;
}

DamageClass Move::get_damage_class(){
    return this->damage_class;
}

Type Move::get_type(){
    return this->type;
}

Target Move::get_target(){
    return this->target;
}

int Move::get_power(){
    return this->power;
}

int Move::get_accuracy(){
    return this->accuracy;
}

int Move::get_current_pp(){
    return this->current_pp;
}

int Move::get_max_pp(){
    return this->max_pp;
}

int Move::get_priority_level(){
    return this->priority_level;
}

int Move::get_effect_chance(){
    return this->effect_chance;
}

int Move::get_stat_change_at(Stat stat){
    return this->stat_change.at(stat);
}


Ailment Move::get_ailment(){
    return this->ailment;
}

int Move::get_ailment_chance(){
    return this->ailment_chance;
}

int Move::get_crit_bonus(){
    return this->crit_bonus;
}

int Move::get_drain(){
    return this->drain;
}

int Move::get_flinch(){
    return this->flinch;
}

int Move::get_stat_change_chance(){
    return this->stat_change_chance;
}

int Move::get_min_hits(){
    return this->min_hits;
}

int Move::get_max_hits(){
    return this->max_hits;
}

int Move::get_min_turns(){
    return this->min_turns;
}

int Move::get_max_turns(){
    return this->max_turns;
}

Method Move::get_method(){
    return this->method;
}

int Move::get_level_learned(){
    return this->level_learned;
}

bool Move::operator==(const Move& other){
    // Check both the name and the id of the move: they should be the same.
    return this->id == other.id && this->name == other.name;
}

