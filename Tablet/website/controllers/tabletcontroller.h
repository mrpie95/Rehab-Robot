#ifndef TABLETCONTROLLER_H
#define TABLETCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT TabletController : public ApplicationController
{
    Q_OBJECT
public:
    TabletController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &userId);
    void create();
    void save(const QString &userId);
    void remove(const QString &userId);
};

#endif // TABLETCONTROLLER_H
