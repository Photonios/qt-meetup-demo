#include <QUrl>
#include <QQuickView>
#include <QQmlContext>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

	MainWindow window(&app);

    QQuickView view(QUrl::fromLocalFile("main.qml"));
	view.rootContext()->setContextProperty("_mainWindow", &window); 

    view.show();
    return app.exec();
}
