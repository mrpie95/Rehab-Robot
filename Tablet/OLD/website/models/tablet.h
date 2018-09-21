#ifndef TABLET_H
#define TABLET_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class TabletObject;
class QJsonArray;


class T_MODEL_EXPORT Tablet : public TAbstractModel
{
public:
    Tablet();
    Tablet(const Tablet &other);
    Tablet(const TabletObject &object);
    ~Tablet();

    int userId() const;
    QString username() const;
    void setUsername(const QString &username);
    QString password() const;
    void setPassword(const QString &password);
    QString name() const;
    void setName(const QString &name);
    Tablet &operator=(const Tablet &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Tablet create(const QString &username, const QString &password, const QString &name);
    static Tablet create(const QVariantMap &values);
    static Tablet get(int userId);
    static int count();
    static QList<Tablet> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<TabletObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Tablet &model);
    friend QDataStream &operator>>(QDataStream &ds, Tablet &model);
};

Q_DECLARE_METATYPE(Tablet)
Q_DECLARE_METATYPE(QList<Tablet>)

#endif // TABLET_H
