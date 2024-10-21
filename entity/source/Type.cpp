#include "../header/Type.h"

/**
 * @brief Convert the given type ID into a Type enum.
 * @param id - integer
 * @return enum Type representing one of the 19 possible types in the game.
 */
Type id_to_type(int id){
    switch(id){
    case 1: return NORMAL;
    case 2: return FIGHTING;
    case 3: return FLYING;
    case 4: return POISON;
    case 5: return GROUND;
    case 6: return ROCK;
    case 7: return BUG;
    case 8: return GHOST;
    case 9: return STEEL;
    case 10: return FIRE;
    case 11: return WATER;
    case 12: return GRASS;
    case 13: return ELECTRIC;
    case 14: return PSYCHIC;
    case 15: return ICE;
    case 16: return DRAGON;
    case 17: return DARK;
    case 18: return FAIRY;
    case 19: return STELLAR;
    case -1:
    default: return UNKNOWN;
    }
}

/**
 * @brief Convert enum Type to a string representation
 * @param type - enum Type
 * @return QString - string representation of enum
 */
QString type_to_string(Type type){
    switch(type){
    case FIRE:
        return "Fire";
    case GRASS:
        return "Grass";
    case WATER:
        return "Water";
    case DARK:
        return "Dark";
    case PSYCHIC:
        return "Psychic";
    case FIGHTING:
        return "Fighting";
    case GROUND:
        return "Ground";
    case ROCK:
        return "Rock";
    case FLYING:
        return "Flying";
    case POISON:
        return "Poison";
    case BUG:
        return "Bug";
    case STEEL:
        return "Steel";
    case GHOST:
        return "Ghost";
    case DRAGON:
        return "Dragon";
    case NORMAL:
        return "Normal";
    case ELECTRIC:
        return "Electric";
    case ICE:
        return "Ice";
    case FAIRY:
        return "Fairy";
    case STELLAR:
        return "Stellar";
    default:
        return "";
    }
}

/**
 * @brief Convert enum Type to a Color representation in rgb values
 * @param type - enum Type
 * @return QColor - color representation of enum
 */
QColor type_to_color(Type type){
    switch(type){
    case FIRE:
        return QColor(222, 6, 6);
    case GRASS:
        return QColor(30, 233, 7);
    case WATER:
        return QColor(0, 118, 236);
    case DARK:
        return QColor(55, 32, 5);
    case PSYCHIC:
        return QColor(206, 61, 80);
    case FIGHTING:
        return QColor(255, 145, 0);
    case GROUND:
        return QColor(212, 123, 22);
    case ROCK:
        return QColor(216, 170, 17);
    case FLYING:
        return QColor(42, 215, 242);
    case POISON:
        return QColor(154, 73, 247);
    case BUG:
        return QColor(133, 158, 51);
    case STEEL:
        return QColor(59, 120, 161);
    case GHOST:
        return QColor(106, 1, 198);
    case DRAGON:
        return QColor(52, 36, 195);
    case NORMAL:
        return QColor(160, 160, 160);
    case ELECTRIC:
        return QColor(255, 213, 0);
    case ICE:
        return QColor(0, 255, 255);
    case FAIRY:
        return QColor(255, 0, 255);
    case STELLAR:
        return QColor(30, 226, 141);
    default:
        return QColor();
    }
}

/**
 * @brief Helper function that sets up the list of types (advantages) that the base type hits super effectively
 * @param base - the main type
 * @param advantages - the list of types the base type hits super effectively against
 */
void TypeChart::add_type_advantages(Type base, vector<Type> advantages){
    for(Type advantage : advantages){
        this->types[base].advantages[advantage] = 2.0;
    }
}

/**
 * @brief TypeChart::add_type_resistances
 * @param base
 * @param resistances
 */
void TypeChart::add_type_resistances(Type base, vector<Type> resistances){
    for(Type resist : resistances){
        this->types[base].resistances[resist] = 0.5;
    }
}

/**
 * @brief TypeChart::add_type_immunities
 * @param base
 * @param immunities
 */
void TypeChart::add_type_immunities(Type base, vector<Type> immunities){
    for(Type immunity : immunities){
        this->types[base].immunities[immunity] = 0.;
    }
}

/**
 * @brief Constructor that sets up all 18 types and their effectiveness vs other types
 */
TypeChart::TypeChart(){
    // Set up all 18 types
    this->add_type_advantages(FIRE, {GRASS, BUG, STEEL, ICE});
    this->add_type_resistances(FIRE, {FIRE, GRASS, BUG, STEEL, ICE, FAIRY});

    this->add_type_advantages(WATER, {FIRE, GROUND, ROCK});
    this->add_type_resistances(WATER, {FIRE, WATER, STEEL, ICE});

    this->add_type_advantages(GRASS, {WATER, GROUND, ROCK});
    this->add_type_resistances(GRASS, {GRASS, WATER, GROUND, ELECTRIC});

    this->add_type_advantages(DARK, {PSYCHIC, GHOST});
    this->add_type_resistances(DARK, {DARK, GHOST});
    this->add_type_immunities(DARK, {PSYCHIC});

    this->add_type_advantages(PSYCHIC, {POISON, FIGHTING});
    this->add_type_resistances(PSYCHIC, {PSYCHIC, FIGHTING});

    this->add_type_advantages(FIGHTING, {ROCK, STEEL, ICE, DARK, NORMAL});
    this->add_type_resistances(FIGHTING, {BUG, ROCK, DARK});

    this->add_type_advantages(GROUND, {ROCK, STEEL, FIRE, ELECTRIC, POISON});
    this->add_type_resistances(GROUND, {POISON, ROCK});

    this->add_type_advantages(ROCK, {FIRE, ICE, FLYING, BUG});
    this->add_type_resistances(ROCK, {FIRE, NORMAL, POISON, FLYING});

    this->add_type_advantages(FLYING, {GRASS, BUG, FIGHTING});
    this->add_type_resistances(FLYING, {GRASS, BUG, FIGHTING});
    this->add_type_immunities(FLYING, {GROUND});

    this->add_type_advantages(POISON, {GRASS, FAIRY});
    this->add_type_resistances(POISON, {GRASS, FIGHTING, POISON, BUG, FAIRY});

    this->add_type_advantages(BUG, {GRASS, DARK, PSYCHIC});
    this->add_type_resistances(BUG, {GRASS, FIGHTING, GROUND});

    this->add_type_advantages(STEEL, {ROCK, FAIRY});
    this->add_type_resistances(STEEL, {GRASS, PSYCHIC, ROCK, FLYING, BUG, STEEL, NORMAL, DRAGON, ICE, FAIRY});
    this->add_type_immunities(STEEL, {POISON});

    this->add_type_advantages(GHOST, {PSYCHIC, GHOST});
    this->add_type_resistances(GHOST, {POISON, BUG});
    this->add_type_immunities(GHOST, {NORMAL, FIGHTING});

    this->add_type_advantages(DRAGON, {DRAGON});
    this->add_type_resistances(DRAGON, {FIRE, WATER, GRASS, ELECTRIC});

    this->add_type_immunities(NORMAL, {GHOST});

    this->add_type_advantages(ELECTRIC, {WATER, FLYING});
    this->add_type_resistances(ELECTRIC, {ELECTRIC, FLYING, STEEL});

    this->add_type_advantages(ICE, {GRASS, GROUND, FLYING, DRAGON});
    this->add_type_resistances(ICE, {ICE});

    this->add_type_advantages(FAIRY, {DARK, FIGHTING, DRAGON});
    this->add_type_resistances(FAIRY, {DARK, FIGHTING, BUG});
    this->add_type_immunities(FAIRY, {DRAGON});
}

/**
 * @brief Returns a multiplier indicating how effective type 1 is against type 2.
 * @return 0 if type 2 is immune to type 1, 0.5 if type 2 resists type 1, 2.0 if type 2 is weak to type 1, or 1. otherwise.
 */
double TypeChart::get_type_matchup(Type type1, Type type2){
    // First check if type2 is immune to type1
    map<Type, double>::iterator immunity = this->types[type2].immunities.find(type1);
    if(immunity != this->types[type2].immunities.end())
        return immunity->second;

    // Then, check if type1 is not very effective against type2
    map<Type, double>::iterator resistance = this->types[type2].resistances.find(type1);
    if(resistance != this->types[type2].resistances.end())
        return resistance->second;

    // Then, check if type1 is super effective against type2
    map<Type, double>::iterator advantage = this->types[type1].advantages.find(type2);
    if(advantage != this->types[type1].advantages.end())
        return advantage->second;

    // All checks are done, so return 1.
    return 1.0;
}


