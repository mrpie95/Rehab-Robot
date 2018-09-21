#include <TreeFrogModel>
#include "tablet.h"
#include "tabletobject.h"

Tablet::Tablet()
    : TAbstractModel(), d(new TabletObject())
{
    d->userId = 0;
}

Tablet::Tablet(const Tablet &other)
    : TAbstractModel(), d(new TabletObject(*other.d))
{ }

Tablet::Tablet(const TabletObject &object)
    : TAbstractModel(), d(new TabletObject(object))
{ }

Tablet::~Tablet()
{
    // If the reference count becomes 0,
    // the shared data object 'TabletObject' is deleted.
}

int Tablet::userId() const
{
    return d->userId;
}

QString Tablet::username() const
{
    return d->username;
}

void Tablet::setUsername(const QString &username)
{
    d->username = username;
}

QString Tablet::password() const
{
    return d->password;
}

void Tablet::setPassword(const QString &password)
{
    d->password = password;
}

QString Tablet::name() const
{
    return d->name;
}

void Tablet::setName(const QString &name)
{
    d->name = name;
}

Tablet &Tablet::operator=(const Tablet &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Tablet Tablet::create(const QString &username, const QString &password, const QString &name)
{
    TabletObject obj;
    obj.username = username;
    obj.password = password;
    obj.name = name;
    if (!obj.create()) {
        return Tablet();
    }
    return Tablet(obj);
}

Tablet Tablet::create(const QVariantMap &values)
{
    Tablet model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Tablet Tablet::get(int userId)
{
    TSqlORMapper<TabletObject> mapper;
    return Tablet(mapper.findByPrimaryKey(userId));
}

int Tablet::count()
{
    TSqlORMapper<TabletObject> mapper;
    return mapper.findCount();
}

QList<Tablet> Tablet::getAll()
{
    return tfGetModelListByCriteria<Tablet, TabletObject>(TCriteria());
}

QJsonArray Tablet::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<TabletObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<TabletObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Tablet(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Tablet::modelData()
{
    return d.data();
}

const TModelObject *Tablet::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Tablet &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Tablet &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Tablet)
