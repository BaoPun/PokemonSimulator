#include "../header/Pokemon.h"

/**
 * @brief Calculate the Pokemon's total stats.  Formula provided via following resource:
 * https://bulbapedia.bulbagarden.net/wiki/Stat
 */
void Pokemon::calculate_total_stats(){
    this->total[HP] = floor(((2 * this->base[HP] + this->iv[HP] + floor(this->ev[HP] / 4)) * this->level) / 100) + this->level + 10;
    this->total[ATK] = floor((floor(((2 * this->base[ATK] + this->iv[ATK] + floor(this->ev[ATK] / 4)) * this->level) / 100) + 5) * this->nature.ATK);
    this->total[DEF] = floor((floor(((2 * this->base[DEF] + this->iv[DEF] + floor(this->ev[DEF] / 4)) * this->level) / 100) + 5) * this->nature.DEF);
    this->total[SP_ATK] = floor((floor(((2 * this->base[SP_ATK] + this->iv[SP_ATK] + floor(this->ev[SP_ATK] / 4)) * this->level) / 100) + 5) * this->nature.SPATK);
    this->total[SP_DEF] = floor((floor(((2 * this->base[SP_DEF] + this->iv[SP_DEF] + floor(this->ev[SP_DEF] / 4)) * this->level) / 100) + 5) * this->nature.SPDEF);
    this->total[SPEED] = floor((floor(((2 * this->base[SPEED] + this->iv[SPEED] + floor(this->ev[SPEED] / 4)) * this->level) / 100) + 5) * this->nature.SPD);
}

/**
 * @brief If the base constructor ever has to be called, then this is an Invalid Pokemon.
 * Invalid pokemon = dex_id = -1
 */
Pokemon::Pokemon(){
    this->dex_id = -1;
    this->trainer_id = -1;
}

/**
 * @brief Populate data for a given Pokemon via results already fetched from the database.
 * However, there must be data in the first place
 */
Pokemon::Pokemon(QSqlRecord record, NatureNames nature, int level, vector<int> evs, vector<int> ivs)
    : nature(nature), level(level)
{
    // If there is a result.
    if(!record.isEmpty()){
        // Set up traits
        // First, set id and name
        this->dex_id = record.field(0).value().toInt();
        this->name = record.field(1).value().toString();

        // Set up abilities.  Ability 3 is guaranteed to be the hidden ability.
        this->abilities.push_back(Ability(record.field(2).value().toInt(), record.field(3).value().toString(), record.field(4).value().toString()));
        int ability2_id = record.field(5).value().toInt();
        int ability3_id = record.field(8).value().toInt();
        if(ability2_id != -1)
            this->abilities.push_back(Ability(ability2_id, record.field(6).value().toString(), record.field(7).value().toString()));
        if(ability3_id != -1)
            this->abilities.push_back(Ability(ability3_id, record.field(9).value().toString(), record.field(10).value().toString(), true));

        // Set up types
        this->types.push_back(id_to_type(record.field(11).value().toInt()));
        int type2_id = record.field(12).value().toInt();
        if(type2_id != -1)
            this->types.push_back(id_to_type(type2_id));

        // Set up base exp and stat ev yields upon defeating this pokemon
        this->base_EXP = record.field(13).value().toInt();
        this->yield[HP] = record.field(14).value().toInt();
        this->yield[ATK] = record.field(15).value().toInt();
        this->yield[DEF] = record.field(16).value().toInt();
        this->yield[SP_ATK] = record.field(17).value().toInt();
        this->yield[SP_DEF] = record.field(18).value().toInt();
        this->yield[SPEED] = record.field(19).value().toInt();

        this->base[HP] = record.field(20).value().toInt();
        this->base[ATK] = record.field(21).value().toInt();
        this->base[DEF] = record.field(22).value().toInt();
        this->base[SP_ATK] = record.field(23).value().toInt();
        this->base[SP_DEF] = record.field(24).value().toInt();
        this->base[SPEED] = record.field(25).value().toInt();

        // And the experience type.
        this->exp_id = record.field(26).value().toInt();
        for(int i = 0; i < EXP_LIST.at(this->exp_id - 1).size(); i++)
            this->exp_gains.push_back(EXP_LIST.at(this->exp_id - 1).at(i));

        // Add the base happiness, capture rate, and whether a pokemon evolves into this one.
        this->base_happiness = record.field(27).value().toInt();
        this->catch_rate = record.field(28).value().toInt();
        this->evolved_from_id = record.field(29).value().toInt();

        // Set up other data not stored in database (mainly the evs and ivs)
        this->ev[HP] = evs.at(0);
        this->ev[ATK] = evs.at(1);
        this->ev[DEF] = evs.at(2);
        this->ev[SP_ATK] = evs.at(3);
        this->ev[SP_DEF] = evs.at(4);
        this->ev[SPEED] = evs.at(5);
        this->iv[HP] = ivs.at(0);
        this->iv[ATK] = ivs.at(1);
        this->iv[DEF] = ivs.at(2);
        this->iv[SP_ATK] = ivs.at(3);
        this->iv[SP_DEF] = ivs.at(4);
        this->iv[SPEED] = ivs.at(5);

        // All of the stat modifiers
        this->modifier[ATK] = 0;
        this->modifier[DEF] = 0;
        this->modifier[SP_ATK] = 0;
        this->modifier[SP_DEF] = 0;
        this->modifier[SPEED] = 0;
        this->modifier[ACCURACY] = 0;
        this->modifier[EVASION] = 0;

        // Default status is None
        this->status = NONE;

        // Finally, calculate total stats
        this->calculate_total_stats();
    }
    else
        this->dex_id = -1;  // invalid id
}

void Pokemon::add_learnable_move(QSqlRecord record){
    Move move(record);
    switch(move.get_method()){
    case LEVEL_UP:
        this->level_up.push_back(std::move(move));
        break;
    case MACHINE:
        this->machine.push_back(std::move(move));
        break;
    case TUTOR:
        this->tutor.push_back(std::move(move));
        break;
    case EGG:
        this->egg.push_back(std::move(move));
        break;
    default:
        break;
    }
}

int Pokemon::get_dex_id() const{
    return this->dex_id;
}

QString Pokemon::get_name(){
    return this->name;
}

int Pokemon::get_level() const{
    return this->level;
}

int Pokemon::get_base_exp() const{
    return this->base_EXP;
}

int Pokemon::get_base(Stat stat){
    return this->base[stat];
}

int Pokemon::get_yield(Stat stat) const{
    return this->yield.at(stat);
}

int Pokemon::get_ev(Stat stat){
    return this->ev[stat];
}

int Pokemon::get_iv(Stat stat){
    return this->iv[stat];
}

int Pokemon::get_total(Stat stat){
    return this->total[stat] * this->get_modifier(stat);
}

int Pokemon::get_num_moves_learned_by(Method method){
    switch(method){
    case LEVEL_UP:
        return this->level_up.size();
    case MACHINE:
        return this->machine.size();
    case TUTOR:
        return this->tutor.size();
    case EGG:
        return this->egg.size();
    default:
        return 0;
    }
}

/**
 * @brief Makes pokemon with given nat dex id a wild pokemon with a "probability" (out of 100)
 * @param probability - probability (out of 100) that the pokemon will appear
 * @param id - national dex id
 * @param database - database query to fetch this pokemon
 * @return
 */
Pokemon* Pokemon::repopulate_data(int probability, int id, Database* database){
    this->update_probability(probability);
    this->set_learnable_moves(id, database);

    return this;
}

int Pokemon::get_probability(){
    return this->probability;
}

/**
 * @brief Get the modifier multiplier.  By default, the modifiers are all at 0
 * @param stat - given stat to get the modifier for
 * @return formula (in boolean) to compute the multiplier
 */
double Pokemon::get_modifier(Stat stat){
    return (this->modifier[stat] >= 0) ? ((3 + this->modifier[stat]) / 3.0) : (3 / (3.0 + (-1 * this->modifier[stat])));
}

vector<Type> Pokemon::get_types(){
    return this->types;
}

int Pokemon::get_current_hp() const{
    return this->current_hp;
}

Move& Pokemon::get_current_move(int idx){
    return this->current_moves[idx];
}

Ailment Pokemon::get_status_ailment(){
    return this->status;
}

vector<Move> Pokemon::get_current_moves(){
    return this->current_moves;
}

int Pokemon::get_num_current_moves(){
    return this->current_moves.size();
}

bool Pokemon::is_owned_by_trainer(){
    return this->trainer_id > -1;
}

void Pokemon::update_probability(int probability){
    if(probability > 0)
        this->probability = probability;
}

void Pokemon::set_learnable_moves(int id, Database* database){
    // Make sure the id matches with the dex id already
    if(id == this->dex_id){
        QSqlQueryModel* move_model = database->get_moves_by_id(id);
        for(int i = 0; i < move_model->query().size(); i++){
            QSqlRecord move = move_model->record(i);
            this->add_learnable_move(move);
        }
        delete move_model;
    }
}

Pokemon* Pokemon::encounter(int level, int nature_id){
    // Update the level.  However, if not between 1 and 100, then yikes
    if(level < 1 || level > 100)
        return nullptr;

    // Otherwise, update the level and the 4 most recent moves
    this->level = level;
    this->current_exp = this->exp_gains[this->level - 1];

    // Also update the chosen nature
    this->nature = id_to_nature(nature_id);

    // TODO: set the 4 most recent moves from the learned via level up.
    // Works by iterating backwards and checking if the given level >= learned by level up
    // And also make sure that move is NOT already in the list
    for(int i = this->level_up.size() - 1; i >= 0 && this->current_moves.size() < 4; --i){
        if(this->level >= this->level_up.at(i).get_level_learned() && this->level_up.at(i).get_level_learned() > 0
            && std::find(this->current_moves.begin(), this->current_moves.end(), this->level_up.at(i)) == this->current_moves.end()){
            this->current_moves.push_back(this->level_up.at(i));
        }
    }

    // Finally, update the total stats
    this->calculate_total_stats();
    this->current_hp = this->total[HP];

    return this;
}

Pokemon* Pokemon::update_owner(int trainer_id){
    this->trainer_id = trainer_id;
    return this;
}

/**
 * @brief Modifies a given stat by the delta, up to -6 or +6.
 * @brief Returns True if modification was successful, or False otherwise
 * @param stat - which stat to affect?  Cannot be HP
 * @param delta - how much of an increase?
 * @return True if change was successful, or False otherwise.
 */
bool Pokemon::change_modifier(Stat stat, int delta){
    // HP's modifier should never be changed.
    if(stat == HP)
        return false;
    if(-6 <= this->modifier[stat] + delta && this->modifier[stat] + delta <= 6){
        this->modifier[stat] += delta;
        return true;
    }
    return false;
}

/**
 * @brief Similar to Pokemon::change_modifier, but this only checks if the change is possible.
 * @return True if the requested delta at the given stat can happen
 */
bool Pokemon::can_change_modifier(Stat stat, int delta){
    // HP's modifier should never be changed.
    return (stat == HP ? false : this->modifier[stat] + delta <= 6 && this->modifier[stat] + delta >= -6);
}

/**
 * @brief If a pokemon is out of battle (not in battle or switched out), then reset all modifiers to 0
 */
void Pokemon::reset_modifiers(){
    this->modifier[ATK] = 0;
    this->modifier[DEF] = 0;
    this->modifier[SP_ATK] = 0;
    this->modifier[SP_DEF] = 0;
    this->modifier[SPEED] = 0;
    this->modifier[ACCURACY] = 0;
    this->modifier[EVASION] = 0;
}

bool Pokemon::is_move_stab(Type type){
    for(size_t i = 0; i < this->types.size(); i++){
        if(this->types.at(i) == type)
            return true;
    }
    return false;
}

// Helper function: do we have any evs remaining?
bool Pokemon::has_available_evs(Stat stat) const{
    return this->ev.at(stat) < 255 && this->ev.at(HP) + this->ev.at(ATK) + this->ev.at(DEF) + this->ev.at(SP_ATK) + this->ev.at(SP_DEF) + this->ev.at(SPEED) < 510;
}

void Pokemon::taken_damage(int damage){
    if(damage >= this->current_hp)
        this->current_hp = 0;
    else
        this->current_hp -= damage;
}

void Pokemon::invalidate_pokemon(){
    this->dex_id = -1;
}

/**
 * @brief Gain experience based on the defeated pokemon.
 * @brief https://bulbapedia.bulbagarden.net/wiki/Experience
 * @param defeated
 */
int Pokemon::gain_experience(const Pokemon& defeated, QQueue<QString>& battle_dialogs){
    // ((b*L/5) * (1/s) * exp( (2L+10)/(L+Lp+10) , 2.5) + 1) * t*e*v*f*p
    // If we're level 100, then don't do anything...
    if(this->level == 100)
        return 0;

    // Otherwise, implement formula
    int total_exp_gain = 0;

    // Three components together
    float bL = (this->level * defeated.get_level()) / 5.;
    float invS = 1 / 1; // 1/s => s = {1 if pokemon participated in battle, 2 if pokemon did not participate in battle and exp share is active)
    float exponent = qPow((2*defeated.get_level() + 10.) / (defeated.get_level() + this->level + 10.), 2.5);
    float component_1 = bL * invS * exponent;

    qDebug() << this->level << defeated.get_level();
    qDebug() << bL << invS << exponent;

    // The rest: t*e*v*f*p
    float t = 1;
    float e = 1;
    float v = 1;
    float f = 1;
    float p = 1;

    // Combine components together via multiplication, and then truncate afterwards
    total_exp_gain += component_1 * t * e * v * f * p;

    // Increase current exp by total exp gain
    this->current_exp += total_exp_gain;

    // Implement ev gains for all 6 stats.
    // Same formula; just change for specific stat as needed
    if(this->has_available_evs(HP)){
        this->ev[HP] = (this->ev[HP] + defeated.get_yield(HP)) > 255 ? 255 : (this->ev[HP] + defeated.get_yield(HP));
    }
    if(this->has_available_evs(ATK)){
        this->ev[ATK] = (this->ev[ATK] + defeated.get_yield(ATK)) > 255 ? 255 : (this->ev[ATK] + defeated.get_yield(ATK));
    }
    if(this->has_available_evs(DEF)){
        this->ev[DEF] = (this->ev[DEF] + defeated.get_yield(DEF)) > 255 ? 255 : (this->ev[DEF] + defeated.get_yield(DEF));
    }
    if(this->has_available_evs(SP_ATK)){
        this->ev[SP_ATK] = (this->ev[SP_ATK] + defeated.get_yield(SP_ATK)) > 255 ? 255 : (this->ev[SP_ATK] + defeated.get_yield(SP_ATK));
    }
    if(this->has_available_evs(SP_DEF)){
        this->ev[SP_DEF] = (this->ev[SP_DEF] + defeated.get_yield(SP_DEF)) > 255 ? 255 : (this->ev[SP_DEF] + defeated.get_yield(SP_DEF));
    }
    if(this->has_available_evs(SPEED)){
        this->ev[SPEED] = (this->ev[SPEED] + defeated.get_yield(SPEED)) > 255 ? 255 : (this->ev[SPEED] + defeated.get_yield(SPEED));
    }

    // Determine if we have leveled up
    if(this->current_exp >= this->exp_gains[this->level]){
        battle_dialogs.append("Gained a level.  You are now level " + QString::fromStdString(std::to_string(++this->level)));
    }

    // Update base stats
    this->calculate_total_stats();

    // Return the total amount of exp gained
    return total_exp_gain;
}

void Pokemon::print_total_stats(){
    qDebug() << " NatDex:" << this->dex_id;
    qDebug() << "   Name:" << this->name;

    {
        QDebug typeDebug = qDebug();
        typeDebug << "  TYPES:" << type_to_string(this->types.at(0));
        if(this->types.size() > 1)
            typeDebug << type_to_string(this->types.at(1));
    }
    {
        QDebug abilityDebug = qDebug();
        abilityDebug.nospace() << "ABILITY: " << this->abilities.at(0).get_name();
        if(this->abilities.size() > 1){
            abilityDebug.nospace() << ", " << this->abilities.at(1).get_name();
            if(this->abilities.size() > 2)
                abilityDebug.nospace() << ", " << this->abilities.at(2).get_name();
        }
    }

    qDebug() << "     HP:" << this->get_total(HP);
    qDebug() << "    ATK:" << this->get_total(ATK);
    qDebug() << "    DEF:" << this->get_total(DEF);
    qDebug() << "  SPATK:" << this->get_total(SP_ATK);
    qDebug() << "  SPDEF:" << this->get_total(SP_DEF);
    qDebug() << "    SPD:" << this->get_total(SPEED);
    qDebug() << " Nature:" << this->nature.name;
    qDebug() << "    EXP:" << this->exp_gains[this->level - 1];


    qDebug() << Qt::endl;
}

void Pokemon::print_battle_stats(){
    {
        QDebug typeDebug = qDebug();
        typeDebug << "  TYPES:" << type_to_string(this->types.at(0));
        if(this->types.size() > 1)
            typeDebug << type_to_string(this->types.at(1));
    }
    qDebug() << "Level" << this->level;
    qDebug() << "Moves:";
    for(size_t i = 0; i < this->current_moves.size(); i++){
        qDebug().nospace()  << this->current_moves.at(i).get_name()
                            << ", Power: " << this->current_moves.at(i).get_power()
                            << ", PP: "
                            << this->current_moves.at(i).get_current_pp() << "/" << this->current_moves.at(i).get_max_pp()
                            << ", Type: " << type_to_string(this->current_moves.at(i).get_type())
                           << ", " << damage_class_to_string(this->current_moves.at(i).get_damage_class());
    }



    // Stats
    qDebug() << "     HP:" << this->get_total(HP) << "+" << this->ev[HP] << "evs";
    qDebug() << "    ATK:" << this->get_total(ATK) << "+" << this->ev[ATK] << "evs";
    qDebug() << "    DEF:" << this->get_total(DEF) << "+" << this->ev[DEF] << "evs";
    qDebug() << "  SPATK:" << this->get_total(SP_ATK) << "+" << this->ev[SP_ATK] << "evs";
    qDebug() << "  SPDEF:" << this->get_total(SP_DEF) << "+" << this->ev[SP_DEF] << "evs";
    qDebug() << "    SPD:" << this->get_total(SPEED) << "+" << this->ev[SPEED] << "evs";
    qDebug() << " Nature:" << this->nature.name;
    if(this->level < 100)
        qDebug() << "Curr XP:" << this->current_exp << "/" << this->exp_gains[this->level];
    else
        qDebug() << "Curr XP:" << this->exp_gains[99] << "/" << this->exp_gains[99];
    qDebug() << "Current HP:" << this->current_hp << "/" << this->total[HP];
    qDebug();
}

