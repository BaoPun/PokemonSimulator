#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <map>
#include <QString>
#include <QColor>

//#include "../../util/header/Utility.h"

using std::vector;
using std::map;

/**
 * @brief An enum representing 18 different Types in Pokemon
 */
enum Type{
    FIRE, GRASS, WATER,
    DARK, PSYCHIC, FIGHTING,
    GROUND, ROCK, FLYING,
    POISON, BUG, STEEL,
    GHOST, DRAGON, NORMAL,
    ELECTRIC, ICE, FAIRY,
    STELLAR, UNKNOWN
};

Type id_to_type(int);
QString type_to_string(Type);
QColor type_to_color(Type);

/**
 * @brief a class representing the Pokemon TypeChart.
 */
class TypeChart{
private:
    /**
     * @brief A struccture that holds all of a type's list of other types that are either effective or not effective.
     * This should NEVER be public, so hide within the TypeChart class.
     *
     * Update: make these be a map for faster lookup
     */
    struct TypeEffectiveness{
        map<Type, double> advantages;
        map<Type, double> resistances;
        map<Type, double> immunities;
    };

    void add_type_advantages(Type, vector<Type>);
    void add_type_resistances(Type, vector<Type>);
    void add_type_immunities(Type, vector<Type>);

    map<Type, TypeEffectiveness> types;
public:
    TypeChart();

    double get_type_matchup(Type, Type);
};

#endif // TYPE_H
