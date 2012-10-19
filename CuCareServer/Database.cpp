#include "Database.h"
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include "QueryResult.h"

Database::Database()
    : pDb (NULL),
      connected (false),
      errorText (""),
      dbFilename ("cucare.db")
{
}

Database::~Database()
{
    if(connected)
        close();
}

bool Database::open()
{
    if(connected)
        return true;

    if(sqlite3_open(dbFilename, &pDb) == SQLITE_OK)
        return connected = true;

    close();    //If there's an error, we still have to close the connection
    return false;
}

bool Database::errorCheck()
{
    if(SQLITE_OK != sqlite3_errcode(pDb))
    {
        errorText = sqlite3_errmsg(pDb);
        return false;
    }
    errorText = "";
    return true;
}

bool Database::command(string query)
{
    if(!connected)
        throw new exception();

    sqlite3_stmt *pStatement;

    if(sqlite3_prepare_v2(pDb, query.c_str(), -1, &pStatement, 0) == SQLITE_OK)
    {
        sqlite3_step(pStatement);
        sqlite3_finalize(pStatement);
    }

    return errorCheck();
}

bool Database::query(string query, QueryResult*& pOutResults)
{
    if(!connected)
        throw new exception();

    sqlite3_stmt *pStatement;
    vector< vector <string>* >* pRows = new vector< vector <string>* >();

    if(sqlite3_prepare_v2(pDb, query.c_str(), -1, &pStatement, 0) == SQLITE_OK)
    {
        int numCols = sqlite3_column_count(pStatement);

        while(sqlite3_step(pStatement) == SQLITE_ROW)
        {
            vector<string>* pCols = new vector<string>();

            for(int col = 0; col < numCols; col++)
                pCols->push_back((char*)sqlite3_column_text(pStatement, col));

            pRows->push_back(pCols);
        }
    }

    pOutResults = new QueryResult(pRows);

    return errorCheck();
}

bool Database::close()
{
    if(sqlite3_close(pDb) == SQLITE_OK)
    {
        connected = false;
        return true;
    }
    return false;
}