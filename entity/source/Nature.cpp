#include "../header/Nature.h"

Nature id_to_nature(int id){
    switch(id){
    case 0:     return Nature(LONELY);
    case 1:     return Nature(BRAVE);
    case 2:     return Nature(ADAMANT);
    case 3:     return Nature(NAUGHTY);
    case 4:     return Nature(BOLD);
    case 5:     return Nature(RELAXED);
    case 6:     return Nature(IMPISH);
    case 7:     return Nature(LAX);
    case 8:     return Nature(MODEST);
    case 9:     return Nature(MILD);
    case 10:    return Nature(QUIET);
    case 11:    return Nature(RASH);
    case 12:    return Nature(CALM);
    case 13:    return Nature(GENTLE);
    case 14:    return Nature(SASSY);
    case 15:    return Nature(CAREFUL);
    case 16:    return Nature(TIMID);
    case 17:    return Nature(HASTY);
    case 18:    return Nature(JOLLY);
    case 19:    return Nature(NAIVE);
    case 20:    return Nature(HARDY);
    case 21:    return Nature(DOCILE);
    case 22:    return Nature(SERIOUS);
    case 23:    return Nature(BASHFUL);
    case 24:    return Nature(QUIRKY);
    default:    return Nature(NATURE_ERROR);
    }
}
