#ifndef MAINPROCESSOR_H
#define MAINPROCESSOR_H

#include "./Game.h"

class MainProcessor : public QObject
{
    Q_OBJECT
private:
    Database* database;
    map<int, Pokemon*> pokemon;

    // MainProcessor is also responsible for handling game states
    Game game;

    // Close database connection (do not allow public access)
    void close_database_connection();

private slots:
    void check_wild_pokemon();
    void return_to_scene();

public:
    MainProcessor(int, int);
    ~MainProcessor();

    vector<Pokemon*> generate_available_pokemon();

    void run_game();
    double calculate_type_matchup(Type, Type);
};

#endif // MAINPROCESSOR_H
