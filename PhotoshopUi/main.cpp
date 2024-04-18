#include "photoshop.h"
#include "qframe.h"

// #include <library/Image_Class.h>

#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PhotoshopUi_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    // w.setStyleSheet("background-image: url(:/background.jpg) no-repeat center;"
    //                 "background-position: center;"
    //                 "background-size: 100%;"
    //                 "background-repeat: no-repeat;"
    //                 "background-clip: border-box;"
    //                 "background-origin: padding-box;");
    w.setWindowIcon(QIcon(":/Logo.png"));
    // QFrame frame(&w);
    // frame.setStyleSheet("background-color: transparent;");
    w.setWindowTitle("Pixelretex");
    return a.exec();
}
