#include <QtCore>
#include <TreeFrogView>
#include "tablet.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT tablet_showView : public TActionView
{
  Q_OBJECT
public:
  tablet_showView() : TActionView() { }
  QString toString();
};

QString tablet_showView::toString()
{
  responsebody.reserve(1108);
  tfetch(Tablet, tablet);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\r\n\r\n<h1>Showing Tablet</h1>\r\n<dt>UserId</dt><dd>");
  eh(tablet.userId());
  responsebody += QLatin1String("</dd><br />\r\n<dt>Username</dt><dd>");
  eh(tablet.username());
  responsebody += QLatin1String("</dd><br />\r\n<dt>Password</dt><dd>");
  eh(tablet.password());
  responsebody += QLatin1String("</dd><br />\r\n<dt>Name</dt><dd>");
  eh(tablet.name());
  responsebody += QLatin1String("</dd><br />\r\n\r\n");
  echo(linkTo("Edit", urla("save", tablet.userId())));
  responsebody += QLatin1String(" |\r\n");
  echo(linkTo("Back", urla("index")));
  responsebody += QLatin1String("\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(tablet_showView)

#include "tablet_showView.moc"
