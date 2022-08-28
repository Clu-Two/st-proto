#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include "..\Dependencies\sqlite\sqlite3.h"

#include "database.h"

master_db DBO;

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{

    float* getVarPtr = (float*)NotUsed;
    *getVarPtr = std::stof(argv[0]); // string to float

    return 0;
}

const char* sqlstatement(const char* format, ...)
{
    //std::string str;

    char str[1024];

    va_list args;
    va_start(args, format);
    vprintf(str, args);
    va_end(args);
    return str;
}

bool master_db::Load_sql3(const char* sz_filename, master_db& DBO)
{

    char* dbl_error;
    int rc;

    sqlite3* MASTER_DB;

    // Open db
    rc = sqlite3_open_v2(sz_filename, &MASTER_DB, SQLITE_OPEN_READONLY, NULL);
    // If db NOT exist
    if (rc != SQLITE_OK)
    {
        return (rc == SQLITE_OK);
    }

    //// Fetch Variables from db
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);
    //rc = sqlite3_exec(MASTER_DB, "SELECT thing FROM tbale WHERE item = 'value';", callback, &variable, &dbl_error);

    sqlite3_close(MASTER_DB);
    return (rc == SQLITE_OK);
}

bool master_db::Load_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
{
    bool result = false;
    //std::string in
    switch (db_type) // sorry 1 second
    {
    case DB_Type::FILE:
    {
        std::ifstream inFile{ sz_filename, std::ios::in | std::ios::binary };
        if (inFile.good())
        {
            //inFile.read(reinterpret_cast<char*>(&MASTER_DB), sizeof(PetVars));
            //inFile.read(reinterpret_cast<char*>(&food_dish_obj), sizeof(food_dish));
            result = true;
        }
        inFile.close();
    }break;

    case DB_Type::SQLITE:
    {
        if (!Load_sql3(sz_filename, DBO))
        {
            Make_sql3(sz_filename);
            if (!Load_sql3(sz_filename, DBO))
            {
                throw "error save/create db !!";
            }
        }
        result = true;
    }break;
    default: break;
    }
    return result;
}

bool master_db::Make_sql3(const char* sz_filename)
{
    char* create_db_error;
    //int bDB_Ok;
    sqlite3* master_db;

    int rc = sqlite3_open_v2(sz_filename, &master_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc == SQLITE_OK)
    {
        // SHIP - TYPE, HEALTH - MAX CARGO
        sqlite3_exec(master_db, "INSERT INTO ship_type_a (type_pk, health, max_cargo) values ('Agrippa', '100', 20);", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_type_a (type_pk, health, max_cargo) values ('Acheron', '150', 100);", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_type_a (type_pk, health, max_cargo) values ('Braxir', '300', 500);", NULL, NULL, &create_db_error);

        // SHIP - TYPE, MAX SPEED, MAX FUEL
        sqlite3_exec(master_db, "INSERT INTO ship_type_b (type_pk, max_speed, max_fuel) values ('Agrippa', '50', 10);", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_type_b (type_pk, max_speed, max_fuel) values ('Acheron', '100', 20);", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_type_b (type_pk, max_speed, max_fuel) values ('Braxir', '150', 250);", NULL, NULL, &create_db_error);

        // SHIP - TYPE , NAME 
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('AG01','Agrippa, 'West-Marina');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('AG02','Agrippa, 'North-Star');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('AC01','Acheron, 'Terran Star');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('AC02','Acheron, 'Apache');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('BR01','Braxir, 'Reckoning');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_a (ship_id_pk, type_fk, name) values ('BR02','Braxir, 'Defender');", NULL, NULL, &create_db_error);
        
        // SHIP - SPEED , ETA
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('AG01','0, '0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('AG02','0, '0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('AC01','0, '0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('AC02','0, '0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('BR01','0, '0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_b (ship_id_pk, speed, eta) values ('BR02','0, '0');", NULL, NULL, &create_db_error);
        
        // SHIP - CARGO
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('AG01','0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('AG02','0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('AC01','0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('AC02','0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('BR01','0');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_c (ship_id_pk, cargo) values ('BR02','0');", NULL, NULL, &create_db_error);

        // SHIP - LOCATION , DESTINATION
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('AG01','sT01', 'N/A');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('AG02','sT01', 'N/A');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('AC01','sN02', 'N/A');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('AC02','sN02', 'N/A');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('BR01','sN01', 'N/A');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO ship_id_d (ship_id_pk, destination, location) values ('BR02','sN01', 'N/A');", NULL, NULL, &create_db_error);
        
        // STATION - DATA
        sqlite3_exec(master_db, "INSERT INTO station_id_a (station_id_pk, name, parent_planet) values ('sN01','Ninth', 'Titan');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_a (station_id_pk, name, parent_planet) values ('sN02','New_Path', 'Mars');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_a (station_id_pk, name, parent_planet) values ('sT01','Terran Dock', 'Earth');", NULL, NULL, &create_db_error);
        
        // STATION - BAYS
        sqlite3_exec(master_db, "INSERT INTO station_id_b (station_id_pk, bays) values ('sN01','4');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_b (station_id_pk, bays) values ('sN02','5');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_b (station_id_pk, bays) values ('sT01','6');", NULL, NULL, &create_db_error);

        // STATION / MARKET
        sqlite3_exec(master_db, "INSERT INTO station_id_c (station_id_pk, market_id_fk) values ('sN01','1');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_c (station_id_pk, market_id_fk) values ('sN02','2');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_c (station_id_pk, market_id_fk) values ('sN02','3');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_id_c (station_id_pk, market_id_fk) values ('sT01','3');", NULL, NULL, &create_db_error);

        // MARKET - NAME , PRICE
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, name, unit_price) values ('1', 'Graphene', '10');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, name, unit_price) values ('2', 'Kryptonite', '5');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, name, unit_price) values ('3', 'Hydrogen', '1');", NULL, NULL, &create_db_error);

        // MARKET - WEIGHT
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, weight) values ('1', '5');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, weight) values ('2', '50');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO market_id_a (market_id_pk, weight) values ('3', '1');", NULL, NULL, &create_db_error);

        // STATION GRAPH
        sqlite3_exec(master_db, "INSERT INTO station_graph (station_id_pk, station_id_pk) values ('sN01','sN02');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_graph (station_id_pk, station_id_pk) values ('sN02','sN01');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_graph (station_id_pk, station_id_pk) values ('sN02','sT01');", NULL, NULL, &create_db_error);
        sqlite3_exec(master_db, "INSERT INTO station_graph (station_id_pk, station_id_pk) values ('sT01','sN02');", NULL, NULL, &create_db_error);

        // where , ids , values , correct ?

    }
    sqlite3_close(master_db);
    return (rc == SQLITE_OK);
}