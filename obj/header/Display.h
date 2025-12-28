#ifndef DISPLAY_H
#define DISPLAY_H

#include "../../entity/header/Pokemon.h"
#include "./MoveBattleButton.h"
#include "./TextButton.h"
#include "./TileSprite.h"
#include  "../../entity/header/Field.h"
#include "./HealthBar.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QKeyEvent>
#include <QQueue>
#include <QProgressBar>
#include <QGraphicsProxyWidget>

class Display : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QMediaPlayer* background_music;
    int width, height;
    vector<Pokemon*> available_pokemon;
    int min_level, max_level;

    // Battle menu
    vector<BattleButton*> battle_button;
    vector<MoveBattleButton*> move_button;

    // Each display has a text dialog
    //TextButton* dialog;
    QQueue<TextButton*> dialogs;

    // If the display is a battle, then there will be 4 pokemon: 2 on enemy side and 2 on ally side
    // For now, only handle single battles (so 2 separate Pokemon pointers)
    // In double battle implementation, use vectors
    bool is_battle_scene;
    Pokemon player_pokemon, opponent_pokemon;
    TileSprite *player_pokemon_sprite, *opponent_pokemon_sprite;
    //QGraphicsProxyWidget* player_hp, *opponent_hp;
    HealthBar* player_hp, *opponent_hp;
    //vector<PokemonUsedMove> move_order;

    // Setup methods are private
    void set_background_music(QString);
    void add_battle_options();
    void remove_battle_options();
    void show_battle_options();
    void hide_battle_options();
    void add_move_selection();
    void remove_move_selection();
    void show_move_selection();
    void hide_move_selection();

    bool battle_menu_shown;
    bool item_menu_shown;
    bool pokemon_menu_shown;

    // Indicate whether or not the sent signal was a move.
    bool is_move_action;


    // Overriding event filter
    bool eventFilter(QObject*, QEvent*);

signals:
    void exit_battle();
    void chosen_move(int);
    void perform_move();
    void gain_exp();

public:
    explicit Display(int, int, int, int, QString, bool = false, QObject *parent = nullptr);
    ~Display();

    // Methods to set up the scene
    void add_to_scene(QGraphicsItem*);
    void remove_from_scene(QGraphicsItem*);

    // Methods to manipulate view
    void show_view(vector<Pokemon*> = {});
    void hide_view();

    // Methods to manipulate background music
    void play_background_music();
    void pause_background_music();
    void stop_background_music();

    // Methods to get player and opposing pokemon
    Pokemon get_player_pokemon();
    Pokemon get_opponent_pokemon();

    // Add all the menus, but hide them by default
    void add_all_battle_menus();

    // Methods to add player and opposing pokemon to battle
    void send_player_pokemon_to_battle(Pokemon);
    void send_opponent_pokemon_to_battle(Pokemon);
    void remove_player_pokemon_from_battle();
    void remove_opponent_pokemon_from_battle();

    // Function to determine which wild pokemon has been chosen
    Pokemon* get_random_pokemon();

    // Is this display a battle scene?
    bool is_battle();

    // Battle scene specific functions
    void set_focus_battle_button(int);
    void set_focus_move_button(int);

    // Dialog specific functions
    void add_dialogs(QQueue<QString>);
    void add_battle_dialogs(QQueue<QString>);
    void remove_dialog();
    void show_dialog();

    // Update pokemon
    void update_player_pokemon(Pokemon);
    void update_opponent_pokemon(Pokemon);

    // Add the move order to the field
    void add_move_order(vector<PokemonUsedMove>);
};

#endif // DISPLAY_H
