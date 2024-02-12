#include "databasemanager.h"


QJsonDocument DataBaseManager::getUsersJSON(const std::string& path)
{
    QFile userList(QString::fromStdString(path));

    if (!userList.exists())
    {
        // If the file doesn't exist, create it with empty data
        userList.open(QIODevice::WriteOnly);
        userList.close();
        return QJsonDocument();
    }

    userList.open(QIODevice::ReadOnly);
    QByteArray data = userList.readAll();
    userList.close();

    return QJsonDocument::fromJson(data);
}

void DataBaseManager::saveUsers(const std::string& path, const QJsonDocument& doc)
{
    QFile userList(QString::fromStdString(path));
    userList.open(QIODevice::WriteOnly);
    userList.write(doc.toJson());
    userList.close();
}

vector<User> DataBaseManager::getUsers(QJsonDocument doc)
{
    std::vector<User> listUser;

    if (doc.isArray())
    {
        QJsonArray users = doc.array();

        for (const QJsonValue& userValue : users)
        {
            if (userValue.isObject())
            {
                QJsonObject user = userValue.toObject();

                QString name = user.value("name").toString();
                QString id = user.value("id").toString();
                QString password = user.value("password").toString();

                listUser.push_back(User(id.toStdString(), name.toStdString(), password.toStdString()));
            }
        }
    }

    return listUser;
}

void DataBaseManager::addUser(User& user, QJsonDocument& doc)
{
    if (!doc.isArray()) {
        // If the document is not an array, consider initializing it as an empty array
        doc = QJsonDocument(QJsonArray());
    }

    QJsonArray usersArray = doc.array();

    QJsonObject userObject;
    userObject["name"] = QString::fromStdString(user.getName());
    userObject["id"] = QString::fromStdString(user.getID());
    userObject["password"] = QString::fromStdString(user.getPassword());

    usersArray.append(userObject);

    doc.setArray(usersArray);
}

