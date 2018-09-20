#include "tabletcontroller.h"
#include "tablet.h"


void TabletController::index()
{
    auto tabletList = Tablet::getAll();
    texport(tabletList);
    render();
}

void TabletController::show(const QString &userId)
{
    auto tablet = Tablet::get(userId.toInt());
    texport(tablet);
    render();
}

void TabletController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto tablet = httpRequest().formItems("tablet");
        auto model = Tablet::create(tablet);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.userId()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(tablet);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void TabletController::save(const QString &userId)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Tablet::get(userId.toInt());
        if (!model.isNull()) {
            auto tablet = model.toVariantMap();
            texport(tablet);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = Tablet::get(userId.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", userId));
            break;
        }

        auto tablet = httpRequest().formItems("tablet");
        model.setProperties(tablet);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.userId()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(tablet);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void TabletController::remove(const QString &userId)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto tablet = Tablet::get(userId.toInt());
    tablet.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(TabletController)
