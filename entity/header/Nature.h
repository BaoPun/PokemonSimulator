#ifndef NATURE_H
#define NATURE_H

#include <QString>

enum NatureNames{
    LONELY, BRAVE, ADAMANT, NAUGHTY,            // + ATK
    BOLD, RELAXED, IMPISH, LAX,                 // + DEF
    MODEST, MILD, QUIET, RASH,                  // + SPATK
    CALM, GENTLE, SASSY, CAREFUL,               // + SPDEF
    TIMID, HASTY, JOLLY, NAIVE,                 // + SPD
    HARDY, DOCILE, SERIOUS, BASHFUL, QUIRKY,    // Neutral
    NATURE_ERROR
};

struct Nature{
    QString name;
    double HP{1.}, ATK{1.}, DEF{1.}, SPATK{1.}, SPDEF{1.}, SPD{1.};

    Nature(NatureNames name = HARDY){
        switch(name){
        case LONELY:
            this->ATK += 0.1; this->DEF -= 0.1; this->name = "Lonely";
            break;
        case BRAVE:
            this->ATK += 0.1; this->SPD -= 0.1; this->name = "Brave";
            break;
        case ADAMANT:
            this->ATK += 0.1; this->SPATK -= 0.1; this->name = "Adamant";
            break;
        case NAUGHTY:
            this->ATK += 0.1; this->SPDEF -= 0.1; this->name = "Naughty";
            break;
        case BOLD:
            this->DEF += 0.1; this->ATK -= 0.1; this->name = "Bold";
            break;
        case RELAXED:
            this->DEF += 0.1; this->SPD -= 0.1; this->name = "Relaxed";
            break;
        case IMPISH:
            this->DEF += 0.1; this->SPATK -= 0.1; this->name = "Impish";
            break;
        case LAX:
            this->DEF += 0.1; this->SPDEF -= 0.1; this->name = "Lax";
            break;
        case MODEST:
            this->SPATK += 0.1; this->ATK -= 0.1; this->name = "Modest";
            break;
        case MILD:
            this->SPATK += 0.1; this->DEF -= 0.1; this->name = "Mild";
            break;
        case QUIET:
            this->SPATK += 0.1; this->SPD -= 0.1; this->name = "Quiet";
            break;
        case RASH:
            this->SPATK += 0.1; this->SPDEF -= 0.1; this->name = "Rash";
            break;
        case CALM:
            this->SPDEF += 0.1; this->ATK -= 0.1; this->name = "Calm";
            break;
        case GENTLE:
            this->SPDEF += 0.1; this->DEF -= 0.1; this->name = "Gentle";
            break;
        case SASSY:
            this->SPDEF += 0.1; this->SPD -= 0.1; this->name = "Sassy";
            break;
        case CAREFUL:
            this->SPDEF += 0.1; this->SPATK -= 0.1; this->name = "Careful";
            break;
        case TIMID:
            this->SPD += 0.1; this->ATK -= 0.1; this->name = "Timid";
            break;
        case HASTY:
            this->SPD += 0.1; this->DEF -= 0.1; this->name = "Hasty";
            break;
        case JOLLY:
            this->SPD += 0.1; this->SPATK -= 0.1; this->name = "Jolly";
            break;
        case NAIVE:
            this->SPD += 0.1; this->SPDEF -= 0.1; this->name = "Naive";
            break;
        case HARDY:
            this->name = "Hardy";
            break;
        case DOCILE:
            this->name = "Docile";
            break;
        case SERIOUS:
            this->name = "Serious";
            break;
        case BASHFUL:
            this->name = "Bashful";
            break;
        case QUIRKY:
            this->name = "Quirky";
            break;
        default:
            this->name = "N/A";
            break;
        }
    }
};

Nature id_to_nature(int);

#endif // NATURE_H
