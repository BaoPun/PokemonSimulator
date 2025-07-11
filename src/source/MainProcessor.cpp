#include "../header/MainProcessor.h"

MainProcessor::MainProcessor(int width, int height) : database(new Database()), game(width, height){
    // Make a connection to the Postgres SQL database
    if(!this->database->is_database_connected()){
        qDebug() << "Connection to the database failed...";
        delete this->database;
        this->database = nullptr;
    }
    else{
        QSqlQueryModel* pokemon_model = this->database->get_all_pokemon();
        for(int i = 0; i < pokemon_model->query().size(); i++){
            QSqlRecord pokemon_result = pokemon_model->record(i);
            Pokemon* newPokemon = new Pokemon(pokemon_result);

            // Adding all learnable moves to ALL pokemon at once is taking too much. Only render what is needed.
            // This is just testing Treecko
            if(newPokemon->get_dex_id() == 252){
                QSqlQueryModel* move_model = this->database->get_moves_by_id(newPokemon->get_dex_id());
                for(int j = 0; j < move_model->query().size(); j++){
                    QSqlRecord move_result = move_model->record(j);
                    newPokemon->add_learnable_move(move_result);
                }
                delete move_model;
            }

            this->pokemon[newPokemon->get_dex_id()] = newPokemon;
        }
        delete pokemon_model;

        // Add treecko to the party
        this->game.add_to_party(*this->pokemon[252]->encounter(5)->update_owner(666));

        // Pass all the collected map data into the Game object
        this->game.create_scene_battle(width, height);
    }
}

MainProcessor::~MainProcessor(){
    // Close the database connection, if not already closed
    this->close_database_connection();
}

void MainProcessor::run_game(){
    this->game.show(this->generate_available_pokemon());

    //this->game.add_to_party()

    // connection to determine wild pokemon
    // and to also determine if we need to switch scenes or not.
    this->connect(this->game.get_player_sprite(), SIGNAL(post_move()), this, SLOT(check_wild_pokemon()), Qt::UniqueConnection);

    // connection to determine when to switch scenes
    //this->connect(this->game.get_player_sprite(), SIGNAL(post_move()), this, SLOT(check_to_switch_scene()), Qt::UniqueConnection);
}

vector<Pokemon*> MainProcessor::generate_available_pokemon(){
    vector<Pokemon*> pokemon_in_scene;
    switch(this->game.get_current_display_index()){
    case 0:
        break;
    case 1:
        pokemon_in_scene.push_back(this->pokemon[280]->repopulate_data(2, 280, database));    // Ralts
        pokemon_in_scene.push_back(this->pokemon[821]->repopulate_data(10, 821, database));    // Rookidee
        pokemon_in_scene.push_back(this->pokemon[403]->repopulate_data(20, 403, database));    // Shinx
        pokemon_in_scene.push_back(this->pokemon[56]->repopulate_data(10, 56, database));     // Mankey
        pokemon_in_scene.push_back(this->pokemon[661]->repopulate_data(8, 661, database));    // Fletchling
        pokemon_in_scene.push_back(this->pokemon[194]->repopulate_data(15, 194, database));    // Wooper
        pokemon_in_scene.push_back(this->pokemon[919]->repopulate_data(15, 919, database));  // Nymble
        pokemon_in_scene.push_back(this->pokemon[917]->repopulate_data(20, 917, database));    // Tarountula
    case 2:
        break;
    }
    return pokemon_in_scene;
}

void MainProcessor::check_wild_pokemon(){
    // If the player is on the grass, allow a 5% chance to encounter a wild pokmeon
    QList<QGraphicsItem*> collision = this->game.get_player_sprite()->collidingItems();
    for(size_t i = 0; i < collision.size(); i++){
        auto& item = *collision[i];

        // If we're in the grass, see if we encounter a wild pokemon here.
        if(typeid(item) == typeid(TileSprite) && qgraphicsitem_cast<TileSprite*>(collision[i])->is_grass()){
            // 5% chance to encounter a wild pokemon
            int chance = QRandomGenerator::global()->bounded(1, 101);
            if(chance <= 5){
                // Which wild pokemon has shown up?
                Pokemon* found = this->game.get_current_display()->get_random_pokemon();
                found->print_battle_stats();

                // If wild pokemon is encountered, switch scenes.
                // Keep the player at the previous scene, as we will transition back to it after the battle
                this->game.switch_scene(0, found);

                // DEBUG: calculate damage
                // DEBUG: test out Treecko using Leafage vs the wild pokemon
                //this->game.damage_calculation(*this->game.get_player()->get_pokemon(0), found, this->game.get_player()->get_pokemon(0)->get_current_move(0));

                // Connection to return to the previous scene.
                connect(this->game.get_current_display(), SIGNAL(exit_battle()), this, SLOT(return_to_scene()), Qt::UniqueConnection);
            }
            break;
        }
        /*else if(typeid(item) == typeid(TileSprite) && ){

        }*/
    }
}

void MainProcessor::return_to_scene(){
    // Upon this slot's invocation, return to the previous scene stored by the game.
    this->game.switch_scene(this->game.get_previous_scene_index());

    // Reset stage changes for the player.
    for(size_t i = 0; i < this->game.get_player()->get_num_pokemon(); i++)
        this->game.reset_stat_changes(i);


    connect(this->game.get_player_sprite(), SIGNAL(post_move()), this, SLOT(check_wild_pokemon()), Qt::UniqueConnection);
}

void MainProcessor::close_database_connection(){
    // Close the database connection, if not already closed
    if(this->database != nullptr){
        delete this->database;
        this->database = nullptr;
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
}
