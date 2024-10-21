#ifndef ABILITY_H
#define ABILITY_H

#include <QString>

class Ability{
private:
    int id;
    QString name;
    QString effect;
    bool is_hidden;
public:
    Ability(int, QString, QString, bool = false);

    int get_id();
    QString get_name();
    QString get_effect();
    bool is_ability_hidden();
};

#endif // ABILITY_H
