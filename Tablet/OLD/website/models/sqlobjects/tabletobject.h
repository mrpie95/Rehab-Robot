#ifndef TABLETOBJECT_H
#define TABLETOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT TabletObject : public TSqlObject, public QSharedData
{
public:
    int userId {0};
    QString username;
    QString password;
    QString name;

    enum PropertyIndex {
        UserId = 0,
        Username,
        Password,
        Name,
    };

    int primaryKeyIndex() const override { return UserId; }
    int autoValueIndex() const override { return UserId; }
    QString tableName() const override { return QLatin1String("tablet"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int userId READ getuserId WRITE setuserId)
    T_DEFINE_PROPERTY(int, userId)
    Q_PROPERTY(QString username READ getusername WRITE setusername)
    T_DEFINE_PROPERTY(QString, username)
    Q_PROPERTY(QString password READ getpassword WRITE setpassword)
    T_DEFINE_PROPERTY(QString, password)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
};

#endif // TABLETOBJECT_H
