#ifndef DATABASE_H
#define DATABASE_H

#include "./Utility.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>

class Database
{
private:
    QSqlDatabase database;
    bool is_connected;

    // Connect to the db.
    bool connect_to_database();

public:
    Database();
    ~Database();

    // Exception classes
    struct DatabaseNotConnectedException{
        DatabaseNotConnectedException(){}
        void print_message(){
            qDebug() << "Error, there was no connection to the database.";
        }
    };

    struct QueryNoResultsException{
        QueryNoResultsException(){}
        void print_message(){
            qDebug() << "Error, query returned no results.";
        }
    };

    // Check the status of the connection
    bool is_database_connected();

    // Getters
    QSqlQuery get_pokemon_by_name(QString);
    QSqlQuery get_pokemon_by_id(int);
    QSqlQueryModel* get_all_pokemon();
    int get_num_pokemon();
    QSqlQueryModel* get_moves_by_id(int);

};

#endif // DATABASE_H
