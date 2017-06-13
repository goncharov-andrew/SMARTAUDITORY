#ifndef DBPATH_H
#define DBPATH_H

#include <QString>

class DBPath
{
public:
    explicit DBPath();
    static QString getDBPath();
    static void setDBPath(QString path);
private:
    static QString Path_db;
};

#endif // DBPATH_H
