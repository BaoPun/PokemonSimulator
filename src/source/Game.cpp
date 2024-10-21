#include "../header/Game.h"

Game::Game(int width, int height) : player(new Player(width, height)) {
    // Create multiple scenes, but the battle scene (first scene) is nullptr
    this->display.push_back(nullptr);       // empty scene for now.
    this->create_scene_1(width, height);
    this->create_scene_2(width, height);

    // We have not created the battle scene yet.
    this->battle_scene_created = false;

    // Preset the current scene to be the first scene.  Default w/o saves, scene = 1
    this->current_scene = 1;

    // There is no previous scene
    this->previous_scene = -1;
}

Game::~Game(){
    // Upon closing the window, delete the player, the background, the view, the scene, the background music
    if(this->player != nullptr)
        delete this->player;
    for(size_t i = 0; i < this->display.size(); i++){
        if(this->display.at(i) != nullptr)
            delete this->display.at(i);
    }
    qDebug() << "Game destructor called and finished.";
}

Player* Game::get_player(){
    return this->player;
}

CharacterSprite* Game::get_player_sprite(){
    return this->player->get_sprite();
}

Display* Game::get_current_display(){
    return this->display.at(this->current_scene);
}

int Game::get_current_display_index(){
    return this->current_scene;
}

int Game::get_previous_scene_index(){
    return this->previous_scene;
}

void Game::show(vector<Pokemon*> available_pokemon){
    // First, hide all views that were added
    for(size_t i = 0; i < this->display.size(); i++){
        if(this->display.at(i) != nullptr && i != this-> current_scene)
            this->display.at(i)->hide_view();
    }

    // If the current scene is -1, then the databse is not up.
    // Do not play the game in that case
    if(this->current_scene < 0){
        qDebug() << "CANNOT PLAY THE GAME";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error, data not loaded properly.");
        msgBox.setText("Error, there was an error with the internal data.  Exiting now.");
        msgBox.exec();
        return;
    }

    // For the view, add certain pokemon depending on the route.
    this->display.at(this->current_scene)->show_view(available_pokemon);
    this->display.at(this->current_scene)->play_background_music();
}

void Game::switch_scene(int current_scene, Pokemon* opponent){
    // Make sure to stop the music playing from the current scene first
    this->display.at(this->current_scene)->stop_background_music();

    // And update the previous scene
    this->previous_scene = this->current_scene;

    // Hide the current view, update the new scene, and play its background music
    this->display.at(this->current_scene)->hide_view();
    this->current_scene = current_scene;
    this->display.at(this->current_scene)->show_view();
    this->display.at(this->current_scene)->play_background_music();

    if(this->current_scene > 0)
        this->player->set_focus();

    // If the scene to switch to is the battle scene, then also add the leading pokemon.
    else{
        // Add all pokemon to battle via the display
        this->remove_opposing_pokemon_from_battle();
        this->add_opposing_pokemon_to_battle(*opponent);
        this->remove_player_pokemon_from_battle();
        int first_pokemon_idx = -1;
        for(int i = 0; i < this->player->get_num_pokemon(); i++){
            if(this->player->get_pokemon(i)->get_current_hp() > 0){
                first_pokemon_idx = i;
                break;
            }
        }
        this->add_player_pokemon_to_battle(first_pokemon_idx);

        // TODO: Also add to the field.
        this->field.load_single_battle(this->player->get_pokemon(first_pokemon_idx), opponent);

        // Add all the menus
        this->display.at(this->current_scene)->add_all_battle_menus();

        // Begin battling.
        // DEBUG: print out the stats of the first pokemon
        //this->player->get_pokemon(first_pokemon_idx)->print_battle_stats();
        this->field.get_ally1_pokemon()->print_battle_stats();

        // Give control over to the battle display
        // TODO: instead of the focus button, display text instead.
        // CHANGE PRIOR TO DIALOG
        QQueue<QString> dialog_text;
        dialog_text.append(QString("A wild %1 appeared!").arg(opponent->get_name()));
        this->display.at(this->current_scene)->add_dialogs(dialog_text);
        this->display.at(this->current_scene)->show_dialog();

        // SIGNAL from the battle scene
        connect(this->get_current_display(), SIGNAL(chosen_move(int)), this, SLOT(process_move(int)), Qt::UniqueConnection);
    }
}

void Game::process_move(int move_idx){
    this->field.load_ally1_move(&this->field.get_ally1_pokemon()->get_current_move(move_idx));

    // TODO: pass to the field, and determine moves
    if(this->field.is_single_battle()){
        // If single battle, we know the player's move.
        // Add both the player's move and the opponent's move
        int num_moves_opponent = this->field.get_opponent1_pokemon()->get_num_current_moves();
        this->field.load_ally1_move(&this->field.get_ally1_pokemon()->get_current_move(move_idx));
        this->field.load_opponent1_move(&this->field.get_opponent1_pokemon()->get_current_move(QRandomGenerator::global()->bounded(0,num_moves_opponent)));

        // Determine move order.
        vector<PokemonUsedMove> order = this->field.determine_move_order();
        this->display.at(this->current_scene)->add_move_order(order);
        this->display.at(this->current_scene)->show_dialog();

        // TODO: create a connection to begin an attack.
        connect(this->get_current_display(), SIGNAL(perform_move()), this, SLOT(perform_move()), Qt::UniqueConnection);
    }
}

void Game::perform_move(){
    if(this->field.is_single_battle()){
        // Is the move a status move?
        if(this->field.get_top_move()->get_damage_class() == STATUS){
            qDebug() << "STATUS MOVE.  APPLY BUFF/DEBUFF";

        }
        else{
            qDebug() << "DAMAGING MOVE.  DAMAGE CALCULATION TIME";

        }

    }


    // After processing current move, get rid of it from the top
    this->field.remove_top_move();
}

void Game::add_player_pokemon_to_battle(int pokemon_id){
    if(this->player->get_num_pokemon() > 0 && pokemon_id >= 0 && pokemon_id < this->player->get_num_pokemon()){
        this->display.at(0)->send_player_pokemon_to_battle(*this->player->get_pokemon(pokemon_id));
    }
}

void Game::remove_player_pokemon_from_battle(){
    // Remove the player pokemon previously here, if it is there.
    if(this->display.at(0)->get_player_pokemon().get_dex_id() > -1){
        this->display.at(0)->remove_player_pokemon_from_battle();
    }
}

void Game::add_opposing_pokemon_to_battle(Pokemon pokemon){
    if(this->display.at(0)->get_opponent_pokemon().get_dex_id() == -1){
        this->display.at(0)->send_opponent_pokemon_to_battle(pokemon);
    }
}

void Game::remove_opposing_pokemon_from_battle(){
    // Remove the opponent pokemon previously here, if it is there.
    if(this->display.at(0)->get_opponent_pokemon().get_dex_id() > -1){
        this->display.at(0)->remove_opponent_pokemon_from_battle();
    }
}

void Game::add_to_party(Pokemon pokemon){
    this->player->add_pokemon(pokemon);
}

double Game::calculate_type_matchup(Type user, Type opponent){
    return this->typechart.get_type_matchup(user, opponent);
}

/**
 * @brief Calculates damage done to the opponent
 * @param user - Pokemon that used the "move"
 * @param target - Pokemon that was targetted by the "move"
 * @param move - "move" that was used
 * @return int - a floored calculation taken from https://bulbapedia.bulbagarden.net/wiki/Damage#Damage_calculation
 */
int Game::damage_calculation(Pokemon& user, Pokemon& opponent, Move move){
    double base = 0;
    if(move.get_damage_class() == PHYSICAL)
        base = (((2 * user.get_level() / 5.) + 2) * move.get_power() * (user.get_total(ATK)*1.0/opponent.get_total(DEF)) / 50.) + 2;
    else if(move.get_damage_class() == SPECIAL)
        base = (((2 * user.get_level() / 5.) + 2) * move.get_power() * (user.get_total(SP_ATK)*1.0/opponent.get_total(SP_DEF)) / 50.) + 2;
    else
        base = 0;

    // For now, can assume target is always 1 since currently working on single battle.
    // Change once double battles are implemented
    double target = 1;

    // Parental bond (Only applies with pokemon with "Parental Bond" ability.  Otherwise set to 1.)
    double PB = 1;

    // Weather (for now, set to 1.  Will implement later)
    double weather = 1;

    // Glaive Rush (either 1 or 2, but always 1 for now).  Only becomes 2 if the target used Glaive Rush on the previous turn.
    double GR = 1;

    // Critical: mainly influenced between items or specific move interactions, but for now set to a 1/24 chance
    double critical = (QRandomGenerator::global()->bounded(1, 241) <= 10 ? 1.5 : 1);

    // random -> between 0.85 and 1
    double random = QRandomGenerator::global()->bounded(85, 101) / 100.;

    // STAB: if the move used matches one of the pokemon's types, then 1.5; otherwise 1.
    double stab = (user.is_move_stab(move.get_type()) ? 1.5 : 1);

    // Determine type matchup vs opposing pokemon
    double type_effectiveness = 1;
    for(size_t i = 0; i < opponent.get_types().size(); i++){
        type_effectiveness *= this->calculate_type_matchup(move.get_type(), opponent.get_types().at(i));
    }

    // Burn: if the user's status is Burn, a physical attack was used, and the attack was not Facade, then multiplier is 0.5
    // 1 otherwise.
    double burn = (user.get_status_ailment() == BURN && move.get_damage_class() == PHYSICAL && move.get_id() != 263) ? 0.5 : 1.;

    // TODO: other, Z Moves.
    // Other:

    // Display a message if there was super effective damage or if there was a crit
    qDebug() << user.get_name() << "used" << move.get_name();
    if(type_effectiveness > 1)
        qDebug() << "Super effective!";
    else if(type_effectiveness < 1)
        qDebug() << "Not very effective...";
    if(critical > 1)
        qDebug() << "Critical hit!";

    int total_damage = (int)floor(base * target * PB * weather * GR * critical * random * stab * type_effectiveness * burn);
    if(total_damage <= 0)
        total_damage = 1;
    if(opponent.get_current_hp() > total_damage)
        qDebug() << opponent.get_name() << "has" << (opponent.get_current_hp() - total_damage) << "left!";
    else
        qDebug() << opponent.get_name() << "fainted!";

    return total_damage;
}
