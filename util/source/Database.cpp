#include "../header/Database.h"

Database::Database() {
    this->database = QSqlDatabase::addDatabase(DATABASE);
    this->database.setDatabaseName(DB_NAME);
    this->database.setHostName(DB_HOST);
    this->database.setUserName(DB_USERNAME);
    this->database.setPassword(DB_PASSWORD);
    this->database.setPort(DB_PORT);

    this->is_connected = this->connect_to_database();
}

Database::~Database(){
    if(this->is_connected){
        this->database.close();
        this->database.removeDatabase(DATABASE);
        qDebug() << "Postgres connection successfully closed.";
    }
}

// Accessor: check if the database was successfully connected
bool Database::is_database_connected(){
    return this->is_connected;
}

// Attempt to connect to the database.
bool Database::connect_to_database(){
    return true ? this->database.open() : false;
}

/**
 * @brief Attempt to retrieve Pokemon data given the name of the pokemon
 * @param name of pokemon as QString
 * @return a SQL Query returning the results or none otherwise.
 */
QSqlQuery Database::get_pokemon_by_name(QString name){
    try{
        if(!this->is_connected)
            throw Database::DatabaseNotConnectedException();
        QSqlQuery query;
        query.prepare(QUERY_POKEMON_BY_NAME);
        query.bindValue(":name", name);
        query.exec();
        if(query.size() == 0)
            throw QueryNoResultsException();
        return query;
    }
    catch(Database::DatabaseNotConnectedException e){
        e.print_message();
        return QSqlQuery();
    }

    catch(Database::QueryNoResultsException e){
        e.print_message();
        return QSqlQuery();
    }
}

/**
 * @brief Attempt to retrieve Pokemon data given the id of the pokemon
 * @param id of pokemon as int
 * @return a SQL Query returning the results or none otherwise.
 */
QSqlQuery Database::get_pokemon_by_id(int id){
    try{
        if(!this->is_connected)
            throw Database::DatabaseNotConnectedException();
        QSqlQuery query;
        query.prepare(QUERY_POKEMON_BY_ID);
        query.bindValue(":id", id);
        query.exec();
        if(query.size() == 0)
            throw QueryNoResultsException();
        return query;
    }
    catch(Database::DatabaseNotConnectedException e){
        e.print_message();
        return QSqlQuery();
    }

    catch(Database::QueryNoResultsException e){
        e.print_message();
        return QSqlQuery();
    }
}


QSqlQueryModel* Database::get_all_pokemon(){
    try{
        if(!this->is_connected)
            throw Database::DatabaseNotConnectedException();
        QSqlQuery query;
        query.exec(QUERY_ALL_POKEMON);
        if(query.size() == 0)
            throw QueryNoResultsException();
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(std::move(query));
        return model;
    }
    catch(Database::DatabaseNotConnectedException e){
        e.print_message();
        return nullptr;//QSqlQueryModel();
    }

    catch(Database::QueryNoResultsException e){
        e.print_message();
        return nullptr;//QSqlQueryModel();
    }
}

int Database::get_num_pokemon(){
    try{
        if(!this->is_connected)
            throw Database::DatabaseNotConnectedException();
        QSqlQuery query;
        query.exec(QUERY_NUM_POKEMON);
        if(query.size() == 0)
            throw QueryNoResultsException();
        query.seek(0);
        return query.value(0).toInt();
    }
    catch(Database::DatabaseNotConnectedException e){
        e.print_message();
        return 0;
    }

    catch(Database::QueryNoResultsException e){
        e.print_message();
        return 0;
    }
}

QSqlQueryModel* Database::get_moves_by_id(int id){
    try{
        if(!this->is_connected)
            throw Database::DatabaseNotConnectedException();
        QSqlQuery query;
        query.prepare(QUERY_MOVES_BY_ID);
        query.bindValue(":id", id);
        query.exec();
        if(query.size() == 0)
            throw QueryNoResultsException();
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(std::move(query));
        return model;
    }
    catch(Database::DatabaseNotConnectedException e){
        e.print_message();
        return nullptr;//QSqlQueryModel();
    }

    catch(Database::QueryNoResultsException e){
        qDebug() << "ID:" << id;
        e.print_message();
        return nullptr;//QSqlQueryModel();
    }
}


