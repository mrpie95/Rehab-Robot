#include <QtCore>
#include <TreeFrogView>
#include "tablet.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT tablet_createView : public TActionView
{
  Q_OBJECT
public:
  tablet_createView() : TActionView() { }
  QString toString();
};

QString tablet_createView::toString()
{
  responsebody.reserve(2372);
  tfetch(QVariantMap, tablet);
  responsebody += QLatin1String("<!DOCTYPE html>\r\n");
    responsebody += QLatin1String("<html>\r\n<head>\r\n  <meta charset=\"UTF-8\">\r\n  <title>");
  eh("Register");
  responsebody += QLatin1String("</title>\r\n</head>\r\n<body>\r\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\r\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\r\n\r\n<h1>New User</h1>\r\n\r\n<form ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<form method=\"post\">\r\n  "), (formTag(urla("create")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("<p>\r\n    <label>Username<br /><input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input />"), (inputTextTag("tablet[username]", tablet["username"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</label>\r\n  </p>\r\n  <p>\r\n    <label>Password<br /><input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input />"), (inputTextTag("tablet[password]", tablet["password"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</label>\r\n  </p>\r\n  <p>\r\n    <label>Name<br /><input ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<input />"), (inputTextTag("tablet[name]", tablet["name"].toString()))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(" />");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</label>\r\n  </p>\r\n  <p>\r\n    <input type=\"submit\" value=\"Create\" />\r\n  </p>\r\n</form>\r\n\r\n<a ");
  do { THtmlParser ___pr = THtmlParser::mergeElements(tr("<a href=\"#\">Back"), (linkTo("Back", urla("index")))); echo(___pr.at(1).attributesString());
  responsebody += QLatin1String(">");
  eh(___pr.at(1).text); echo(___pr.childElementsToString(1)); } while (0);
  responsebody += QLatin1String("</a>\r\n\r\n</body>\r\n</html>\r\n");

  return responsebody;
}

T_DEFINE_VIEW(tablet_createView)

#include "tablet_createView.moc"
