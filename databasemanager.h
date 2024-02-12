#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "user.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QString>

class DataBaseManager
{
  public:
    DataBaseManager();
    QJsonDocument getUsersJSON(const std::string& path);
    void saveUsers(const std::string& path, const QJsonDocument& doc);
    vector<User> getUsers(QJsonDocument doc);
    void addUser(User& user, QJsonDocument& doc);
    string generateID();

};

#endif // DATABASEMANAGER_H
