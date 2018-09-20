#include <QtCore>
#include <TreeFrogView>
#include "tablet.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT tablet_indexView : public TActionView
{
  Q_OBJECT
public:
  tablet_indexView() : TActionView() { }
  QString toString();
};

QString tablet_indexView::toString()
{
  responsebody.reserve(1895);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh("Log In Page");
  responsebody += QLatin1String("</title>\r\n</head>\r\n<body>\r\n\r\n<h1>Log In</h1>\r\n\r\n<form method=\"post\">\r\n  <p>\r\n    <label>Username<br /><input />");
  eh(i.username());
  responsebody += QLatin1String("</label>\r\n  </p>\r\n  <p>\r\n    <label>Password<br /><input />");
  eh(i.password());
  responsebody += QLatin1String("</label>\r\n  </p>\r\n  <p>\r\n    <input type=\"submit\" value=\"Log In\" />\r\n  </p>\r\n</form>\r\n");
  echo(linkTo("Register", urla("create")));
  responsebody += QLatin1String("<br /><br />\r\n<a>Forgot password</a><br />\r\n\r\n<p>Table of users: for testing purposes.</p>\r\n<table border=\"1\" cellpadding=\"5\" style=\"border: 1px #d0d0d0 solid; border-collapse: collapse;\">\r\n  <tr>\r\n    <th>UserId</th>\r\n    <th>Username</th>\r\n    <th>Password</th>\r\n    <th>Name</th>\r\n    <th></th>\r\n  </tr>\r\n  ");
  tfetch(QList<Tablet>, tabletList);
for (const auto &i : tabletList) {
  responsebody += QLatin1String("<tr>\r\n    <td>");
  eh(i.userId());
  responsebody += QLatin1String("</td>\r\n    <td>");
  eh(i.username());
  responsebody += QLatin1String("</td>\r\n    <td>");
  eh(i.password());
  responsebody += QLatin1String("</td>\r\n    <td>");
  eh(i.name());
  responsebody += QLatin1String("</td>\r\n    <td>\r\n      ");
  echo(linkTo("Show", urla("show", i.userId())));
  responsebody += QLatin1String("\r\n      ");
  echo(linkTo("Edit", urla("save", i.userId())));
  responsebody += QLatin1String("\r\n      ");
  echo(linkTo("Remove", urla("remove", i.userId()), Tf::Post, "confirm('Are you sure?')"));
  responsebody += QLatin1String("\r\n    </td>\r\n  </tr>");
  };
  responsebody += QLatin1String("</table>\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(tablet_indexView)

#include "tablet_indexView.moc"
