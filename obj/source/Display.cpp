#include "../header/Display.h"

Display::Display(int width, int height, int min_level, int max_level, QString music, bool is_battle_scene, QObject *parent) : QObject{parent}{
    // Set up the width and height of the view/screen
    this->width = width;
    this->height = height;

    // Set up min/max level of wild pokemon in this area
    this->min_level = min_level;
    this->max_level = max_level;

    // Initialize the scene, view, and background music
    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(this->scene);
    this->background_music = new QMediaPlayer();

    // Set both scene and view to be a fixed width and height
    this->view->setFixedSize(width, height);
    this->scene->setSceneRect(0,0,width,height);

    // Set up view properties
    this->view->setWindowTitle("Pokemon Simulator by Bao Phung");
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set up background music
    this->set_background_music(music);

    // Indicate whether or not the constructed Display is a battle scene
    // If true, add 4 buttons
    this->is_battle_scene = is_battle_scene;

    // Determine which menu is being shown in the battle
    this->battle_menu_shown = false;
    this->item_menu_shown = false;
    this->pokemon_menu_shown = false;

    // Preset player pokemon and opponent pokemon to be nullptr
    // Will always be nullptr except for when the display is a battle scene
    this->player_pokemon_sprite = nullptr;
    this->opponent_pokemon_sprite = nullptr;
    this->player_hp = nullptr;
    this->opponent_hp = nullptr;

    // Add white background
    this->scene->setBackgroundBrush(Qt::white);

    // By default, the move action flag is set to False
    this->is_move_action = false;

    // Give the view event filter
    this->view->installEventFilter(this);
}

Display::~Display(){
    this->remove_battle_options();
    this->remove_move_selection();
    for(int i = 0; i < this->available_pokemon.size(); i++){
        if(this->available_pokemon[i] != nullptr)
            delete this->available_pokemon[i];
    }
    this->available_pokemon.clear();
    while(!this->dialogs.isEmpty())
        this->remove_dialog();
    if(this->view != nullptr)
        delete this->view;
    if(this->scene != nullptr)
        delete this->scene;
    if(this->background_music != nullptr)
        delete this->background_music;
}

void Display::set_background_music(QString music){
    this->background_music->setAudioOutput(new QAudioOutput());
    this->background_music->setSource(QUrl("qrc:/sounds/Sounds/" + music));
    this->background_music->audioOutput()->setVolume(15);
    this->background_music->setLoops(QMediaPlayer::Infinite);
}

void Display::add_battle_options(){
    if(this->is_battle_scene && this->battle_button.empty()){
        this->battle_button.push_back(new BattleButton("Battle", 608, 736));
        this->scene->addItem(this->battle_button.back());
        this->battle_button.push_back(new BattleButton("Item", 752, 736));
        this->scene->addItem(this->battle_button.back());
        this->battle_button.push_back(new BattleButton("Pokemon", 608, 816));
        this->scene->addItem(this->battle_button.back());
        this->battle_button.push_back(new BattleButton("Run", 752, 816));
        this->scene->addItem(this->battle_button.back());
    }
}

void Display::remove_battle_options(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->battle_button.size(); i++){
            if(this->battle_button[i] != nullptr){
                this->remove_from_scene(this->battle_button[i]);
                delete this->battle_button[i];
            }
        }
        this->battle_button.clear();
    }
}

void Display::show_battle_options(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->battle_button.size(); i++){
            this->battle_button[i]->show();
        }
    }
}

void Display::hide_battle_options(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->battle_button.size(); i++){
            this->battle_button[i]->hide();
        }
    }
}

void Display::add_move_selection(){
    if(this->is_battle_scene && this->move_button.empty()){
        // Add move 1 to top left corner
        if(this->player_pokemon.get_num_current_moves() > 0)
            this->move_button.push_back(new MoveBattleButton(this->player_pokemon.get_current_move(0), 320, 736, type_to_color(this->player_pokemon.get_current_move(0).get_type())));
        else
            this->move_button.push_back(new MoveBattleButton(Move(), 320, 736, QColor()));
        this->scene->addItem(this->move_button.back());

        // Add move 2 to top right corner
        if(this->player_pokemon.get_num_current_moves() > 1)
            this->move_button.push_back(new MoveBattleButton(this->player_pokemon.get_current_move(1), 464, 736, type_to_color(this->player_pokemon.get_current_move(1).get_type())));
        else
            this->move_button.push_back(new MoveBattleButton(Move(), 464, 736, QColor()));
        this->scene->addItem(this->move_button.back());

        // Add move 3 to bottom left corner
        if(this->player_pokemon.get_num_current_moves() > 2)
            this->move_button.push_back(new MoveBattleButton(this->player_pokemon.get_current_move(2), 320, 816, type_to_color(this->player_pokemon.get_current_move(2).get_type())));
        else
            this->move_button.push_back(new MoveBattleButton(Move(), 320, 816, QColor()));
        this->scene->addItem(this->move_button.back());

        // Add move 4 to bottom right corner
        if(this->player_pokemon.get_num_current_moves() > 3)
            this->move_button.push_back(new MoveBattleButton(this->player_pokemon.get_current_move(3), 464, 816, type_to_color(this->player_pokemon.get_current_move(3).get_type())));
        else
            this->move_button.push_back(new MoveBattleButton(Move(), 464, 816, QColor()));
        this->scene->addItem(this->move_button.back());


        this->battle_menu_shown = true;
    }
}

void Display::remove_move_selection(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->move_button.size(); i++){
            if(this->move_button[i] != nullptr){
                this->remove_from_scene(this->move_button[i]);
                delete this->move_button[i];
            }
        }
        this->move_button.clear();
        this->battle_menu_shown = false;
    }
}

void Display::hide_move_selection(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->move_button.size(); i++){
            this->move_button[i]->hide();
        }
        this->battle_menu_shown = false;
    }
}

void Display::show_move_selection(){
    if(this->is_battle_scene){
        for(int i = 0; i < this->move_button.size(); i++){
            this->move_button[i]->show();
        }
        this->battle_menu_shown = true;
    }
}

void Display::add_to_scene(QGraphicsItem* item){
    this->scene->addItem(item);
}

void Display::remove_from_scene(QGraphicsItem* item){
    this->scene->removeItem(item);
}

// Methods to manipulate view
void Display::show_view(vector<Pokemon*> available_pokemon){
    this->view->show();

    // Add the available list of pokemon here, but only if the initial list is empty
    if(this->available_pokemon.empty())
        this->available_pokemon = available_pokemon;

    // DEBUG: print out how many pokemon here
    if(this->available_pokemon.size() > 0)
        qDebug() << "There are" << this->available_pokemon.size() << "available pokemon on this route.";
}

void Display::hide_view(){
    this->view->hide();
}

// Methods to manipulate background music
void Display::play_background_music(){
    if(!this->background_music->isPlaying())
        this->background_music->play();
}

void Display::pause_background_music(){
    if(this->background_music->isPlaying())
        this->background_music->pause();
}

void Display::stop_background_music(){
    this->background_music->stop();
}

Pokemon Display::get_player_pokemon(){
    return this->player_pokemon;
}

Pokemon Display::get_opponent_pokemon(){
    return this->opponent_pokemon;
}

void Display::add_all_battle_menus(){
    if(this->is_battle_scene){
        this->add_battle_options();
        this->hide_battle_options();
        this->add_move_selection();
        this->hide_move_selection();
    }
}

void Display::send_player_pokemon_to_battle(Pokemon pokemon){
    // Can assume that this will ALWAYS be valid.  Checked for validity within the Game class.
    this->player_pokemon = pokemon;
    this->player_pokemon_sprite = new TileSprite(-1, 176, 448, QString("./PokemonHomeImages/%1.png").arg(pokemon.get_dex_id()), 144, 144);
    this->add_to_scene(this->player_pokemon_sprite);

    // Add health bar above the sprite (QProgressBar)
    this->player_hp = new HealthBar(this->player_pokemon.get_current_hp(), this->player_pokemon.get_total(HP), 176, 416);
    this->add_to_scene(this->player_hp->get_proxy());
}

void Display::send_opponent_pokemon_to_battle(Pokemon pokemon){
    // Can assume that this will ALWAYS be valid.  Checked for validity within the Game class.
    this->opponent_pokemon = pokemon;
    this->opponent_pokemon_sprite = new TileSprite(-1, 576, 160, QString("./PokemonHomeImages/%1.png").arg(pokemon.get_dex_id()), 144, 144);
    this->add_to_scene(this->opponent_pokemon_sprite);

    // Add health bar above the sprite (QProgressBar)
    this->opponent_hp = new HealthBar(this->opponent_pokemon.get_current_hp(), this->opponent_pokemon.get_total(HP), 576, 128);
    this->add_to_scene(this->opponent_hp->get_proxy());

    // TODO: add name of opposing pokemon on top of the health bar

}

void Display::remove_player_pokemon_from_battle(){
    // set id to -1, remove sprite from the view, and then deallocate the sprite.
    this->player_pokemon.invalidate_pokemon();
    this->remove_from_scene(this->player_pokemon_sprite);
    delete this->player_pokemon_sprite;
    this->player_pokemon_sprite = nullptr;

    // And delete the opponent health bar as well
    this->remove_from_scene(this->player_hp->get_proxy());
    delete this->player_hp; qDebug() << "Nice deletion";
    this->player_hp = nullptr;
}

void Display::remove_opponent_pokemon_from_battle(){
    // set id to -1, remove sprite from the view, and then deallocate the sprite.
    this->opponent_pokemon.invalidate_pokemon();
    this->remove_from_scene(this->opponent_pokemon_sprite);
    delete this->opponent_pokemon_sprite;
    this->opponent_pokemon_sprite = nullptr;

    // and delete the opponent health bar as well
    this->remove_from_scene(this->opponent_hp->get_proxy());
    delete this->opponent_hp;
    this->opponent_hp = nullptr;

    qDebug() << "Nice";
}

Pokemon* Display::get_random_pokemon(){
    // First, choose a random number between 1 and 100
    int random = QRandomGenerator::global()->bounded(1, 101);
    //qDebug() << "Random number:" << random;

    // Then, iterate through the list of pokemon (minus 1) to see bounded ranges
    int low = 0, high = 0;
    for(size_t i = 0; i < this->available_pokemon.size() - 1; i++){
        // Recompute low and high
        low = (low == 0 ? 1 : high + 1);
        high += this->available_pokemon.at(i)->get_probability();

        // If the computed random number is between low and high, then this is our pokemon (return it)
        if(low <= random && random <= high){
            qDebug() << "A wild" << this->available_pokemon.at(i)->get_name() << "appeared!";
            return this->available_pokemon.at(i)->encounter(QRandomGenerator::global()->bounded(this->min_level, this->max_level + 1));
        }
    }

    // If nothing was returned by the time we escape the for loop, then it's the last pokemon
    qDebug() << "A wild" << this->available_pokemon.back()->get_name() << "appeared!";
    return this->available_pokemon.back()->encounter(QRandomGenerator::global()->bounded(this->min_level, this->max_level + 1));
}

bool Display::is_battle(){
    return this->is_battle_scene;
}

void Display::set_focus_battle_button(int idx){
    if(!this->is_battle())
        return;
    for(int i = 0; i < this->battle_button.size(); i++){
        if(i == idx)
            this->battle_button[i]->setBold(true);
        else
            this->battle_button[i]->setBold(false);
    }
}

void Display::set_focus_move_button(int idx){
    // Do not show the list of moves if either the display isn't the battle scene or we haven't chosen to battle
    if(!this->is_battle() || !this->battle_menu_shown)
        return;
    for(int i = 0; i < this->move_button.size(); i++){
        if(i == idx)
            this->move_button[i]->setBold(true);
        else
            this->move_button[i]->setBold(false);
    }
}

void Display::add_dialogs(QQueue<QString> dialogs){
    while(!dialogs.isEmpty()){
        this->dialogs.enqueue(new TextButton(dialogs.head(), 1, 736, 896, 160));
        this->scene->addItem(this->dialogs.back());
        this->dialogs.back()->hide();
        dialogs.pop_front();
    }
}

void Display::add_battle_dialogs(QQueue<QString> dialogs){
    while(!dialogs.empty()){
        this->dialogs.insert(this->dialogs.cbegin(), new TextButton(dialogs.last(), 1, 736, 896, 160));
        this->scene->addItem(this->dialogs.front());
        this->dialogs.front()->hide();
        dialogs.pop_back();
    }
}

void Display::remove_dialog(){
    if(!this->dialogs.isEmpty()){
        TextButton* old_dialog = this->dialogs.front();
        this->scene->removeItem(old_dialog);
        delete old_dialog;
        this->dialogs.dequeue();
    }
}

void Display::show_dialog(){
    if(!this->dialogs.isEmpty())
        this->dialogs.front()->show();
}

void Display::update_player_pokemon(Pokemon p){
    this->player_pokemon = p;
    this->player_hp->set_current_hp(this->player_pokemon.get_current_hp());
}

void Display::update_opponent_pokemon(Pokemon p){
    this->opponent_pokemon = p;
    this->opponent_hp->set_current_hp(this->opponent_pokemon.get_current_hp());
}

void Display::add_move_order(vector<PokemonUsedMove> move_order){
    //this->move_order = move_order;
    QQueue<QString> battle_text;
    for(int i = 0; i < /*this->*/move_order.size(); i++){
        battle_text.enqueue(/*this->*/move_order[i].get_action_text());
    }
    this->add_dialogs(battle_text);
}

bool Display::eventFilter(QObject* object, QEvent* event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        // Close the program when CTRL + Q hotkey is pressed
        if(keyEvent->key() == Qt::Key_Q && (keyEvent->modifiers() & Qt::ControlModifier)){
            this->view->close();
            return true;
        }
        // Pause/play the background music when P is pressed
        else if(keyEvent->key() == Qt::Key_P){
            if(this->background_music->isPlaying())
                this->background_music->pause();
            else
                this->background_music->play();
            return true;
        }
        // Battle interactions
        else if(this->is_battle()){
            if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Space){
                // Priority over any and all dialog boxes
                if(!this->dialogs.isEmpty()){
                    // Close the dialog box.
                    QString text = this->dialogs.front()->get_text();
                    this->remove_dialog();

                    // Does the player NOT have any more usable pokemon?
                    if(text.contains("whited out")){
                        this->view->close();
                    }

                    // Did a pokemon faint?
                    if(text.contains(" fainted!")){
                        // If an opponent's pokemon (or wild) faints, give exp
                        if(this->opponent_pokemon.get_current_hp() <= 0){
                            qDebug() << "Opponent has fainted.  TODO: implement exp gain.";
                            this->dialogs.clear();
                            Q_EMIT gain_exp();
                        }

                        // Exit the battle only if the wild pokemon is gone
                        //       or if the player has no more usable pokemon
                        else if(this->dialogs.empty() || this->opponent_pokemon.get_current_hp() == 0){
                            Q_EMIT exit_battle();
                            this->dialogs.clear();
                         }
                    }


                    // If the first dialog is a move being used.
                    else if(text.contains("used")){
                        Q_EMIT perform_move();
                        if(this->dialogs.empty())
                            this->is_move_action = false;
                    }

                    // If there are more dialog boxes in queue, show the next one waiting
                    if(!this->dialogs.isEmpty()){
                        this->dialogs.front()->show();
                    }

                    // If we chose to run away, display that prompt here.
                    else if(text == "Ran away successfully!"){
                        Q_EMIT exit_battle();
                        this->dialogs.clear();

                        // TODO: Also clear out the sprites
                        // Maybe not needed, actually...
                    }

                    // Otherwise, show the battle menu
                    else{
                        // If opponent is defeated, exit the battle
                        if(this->opponent_pokemon.get_current_hp() == 0){
                            Q_EMIT exit_battle();
                            this->dialogs.clear();
                            return true;
                        }

                        this->show_battle_options();
                        this->set_focus_battle_button(0);
                    }
                    return true;
                }

                // If neither the battle, item, nor pokemon menus are shown, then it's the default menu
                else if(!this->battle_menu_shown && !this->item_menu_shown && !this->pokemon_menu_shown){
                    // If we pressed ENTER on the battle menu, switch to the list of possible moves.
                    if(this->battle_button[0]->is_bold()){
                        // Hide the buttons and show the list of possible moves.
                        qDebug() << "You have chosen to battle the pokemon.";
                        this->hide_battle_options();
                        this->show_move_selection();
                        this->set_focus_move_button(0);
                        return true;
                    }

                    // If we pressed ENTER on the item menu, switch to the item menu
                    // TODO: figure out how to implement this though...
                    else if(this->battle_button[1]->is_bold()){
                        qDebug() << "You have chosen to look at the available items";
                        return true;
                    }

                    // If we pressed ENTER on the pokemon menu, switch to the pokemon menu
                    // TODO: figure out how to implement this...
                    else if(this->battle_button[2]->is_bold()){
                        qDebug() << "You have chosen to switch pokemon";
                        return true;
                    }

                    // If we pressed ENTER on the run away menu, then exit the battle and go back to the previous display
                    else if(this->battle_button[3]->is_bold()){
                        // TODO: calculate the probability of running away
                        qDebug() << "You have ran away from the battle successfully!";
                        //this->move_order.clear();
                        this->dialogs.append(new TextButton("Ran away successfully!", 1, 736, 896, 160));
                        this->scene->addItem(this->dialogs.back());
                        this->show_dialog();
                        this->hide_battle_options();
                        return true;
                    }
                }
                // If we pressed ENTER on a selected move that is valid.
                else if(this->battle_menu_shown){
                    // Pressing on a move will confirm the move being used.
                    for(int i = 0; i < this->move_button.size(); i++){
                        if(this->move_button[i]->is_bold() && this->move_button[i]->is_valid_move()){
                            // After determining attack order, close the move screen
                            this->hide_move_selection();

                            // Emit a signal to the Game class
                            // For single battle, this will then generate a series of messages to pass back here
                            // And each message becomes a textbox.
                            Q_EMIT chosen_move(i);

                            // After emitting the signal, update the move action flag to true
                            this->is_move_action = true;

                            return true;
                        }
                    }
                }
            }
            // When we click the left arrow key
            else if(keyEvent->key() == Qt::Key_Left){
                // Going left on the main battle menu
                if(this->dialogs.isEmpty() && !this->battle_menu_shown && !this->item_menu_shown && !this->pokemon_menu_shown){
                    // If the "RUN" or "ITEM" button is focused,
                    // then unfocus it and switch focus to the "POKEMON" or "BATTLE" button
                    if(this->battle_button[1]->is_bold()){
                        this->set_focus_battle_button(0);
                        return true;
                    }
                    else if(this->battle_button[3]->is_bold()){
                        this->set_focus_battle_button(2);
                        return true;
                    }
                }
                // Going left on the move menu
                else if(this->battle_menu_shown){
                    if(this->move_button[1]->is_bold()){
                        this->set_focus_move_button(0);
                        return true;
                    }
                    else if(this->move_button[3]->is_bold()){
                        this->set_focus_move_button(2);
                        return true;
                    }
                }
                return true;
            }
            // When we click the right arrow key
            else if(keyEvent->key() == Qt::Key_Right){
                if(this->dialogs.isEmpty() && !this->battle_menu_shown && !this->item_menu_shown && !this->pokemon_menu_shown){
                    if(this->battle_button[0]->is_bold()){
                        this->set_focus_battle_button(1);
                        return true;
                    }
                    else if(this->battle_button[2]->is_bold()){
                        this->set_focus_battle_button(3);
                        return true;
                    }
                }
                else if(this->battle_menu_shown){
                    if(this->move_button[0]->is_bold()){
                        this->set_focus_move_button(1);
                        return true;
                    }
                    else if(this->move_button[2]->is_bold()){
                        this->set_focus_move_button(3);
                        return true;
                    }
                }
                return true;
            }
            // When we click the up arrow key
            else if(keyEvent->key() == Qt::Key_Up){
                if(this->dialogs.isEmpty() && !this->battle_menu_shown && !this->item_menu_shown && !this->pokemon_menu_shown){
                    if(this->battle_button[2]->is_bold()){
                        this->set_focus_battle_button(0);
                        return true;
                    }
                    else if(this->battle_button[3]->is_bold()){
                        this->set_focus_battle_button(1);
                        return true;
                    }
                }
                else if(this->battle_menu_shown){
                    if(this->move_button[2]->is_bold()){
                        this->set_focus_move_button(0);
                        return true;
                    }
                    else if(this->move_button[3]->is_bold()){
                        this->set_focus_move_button(1);
                        return true;
                    }
                }
            }
            // When we click the down arrow key
            else if(keyEvent->key() == Qt::Key_Down){
                if(this->dialogs.isEmpty() && !this->battle_menu_shown && !this->item_menu_shown && !this->pokemon_menu_shown){
                    if(this->battle_button[0]->is_bold()){
                        this->set_focus_battle_button(2);
                        return true;
                    }
                    else if(this->battle_button[1]->is_bold()){
                        this->set_focus_battle_button(3);
                        return true;
                    }
                }
                else if(this->battle_menu_shown){
                    if(this->move_button[0]->is_bold()){
                        this->set_focus_move_button(2);
                        return true;
                    }
                    else if(this->move_button[1]->is_bold()){
                        this->set_focus_move_button(3);
                        return true;
                    }
                }
            }
            else if(keyEvent->key() == Qt::Key_X){
                if(this->battle_menu_shown){
                    this->hide_move_selection();
                    this->show_battle_options();
                    this->set_focus_battle_button(0);
                    return true;
                }
            }
        }
    }

    return false;
}
