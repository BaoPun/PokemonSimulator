#ifndef GAME_H
#define GAME_H

#include "../../obj/header/Display.h"
#include "../../entity/header/Player.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Game : public QObject
{
    Q_OBJECT
private:
    TypeChart typechart;
    Player* player;
    QVector<Display*> display;
    int current_scene, previous_scene;

    bool battle_scene_created;

    // Create multiple scenes
    void create_scene_1(int, int);
    void create_scene_2(int, int);

    double calculate_type_matchup(Type, Type);

    // The game contains a Field
    Field field;

    // Event filter, specifically for the button
    //bool eventFilter(QObject*, QEvent*);

private slots:
    void process_move(int);
    void perform_move();

public:
    Game(int, int);
    ~Game();

    // Getters
    Player* get_player();
    CharacterSprite* get_player_sprite();
    Display* get_current_display();
    int get_current_display_index();
    int get_previous_scene_index();

    // Create the battle scene (make sure to do this once)
    void create_scene_battle(int, int);

    // Add and remove pokemon from the battle scene
    void add_opposing_pokemon_to_battle(Pokemon);
    void remove_opposing_pokemon_from_battle();
    void add_player_pokemon_to_battle(int);
    void remove_player_pokemon_from_battle();

    // Operations on the player's party
    void add_to_party(Pokemon);

    // Manipulate scenes
    void show(vector<Pokemon*>);
    void switch_scene(int, Pokemon* = nullptr);

    // Calculate damage
    int damage_calculation(Pokemon&, Pokemon&, Move);
};

#endif // GAME_H
