#include "dbpath.h"

DBPath::DBPath()
{

}

QString DBPath::Path_db = "";

QString DBPath::getDBPath()
{
    return DBPath::Path_db;
}

void DBPath::setDBPath(QString path)
{
    DBPath::Path_db = path;
}
