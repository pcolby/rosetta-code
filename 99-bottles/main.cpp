#include <iostream>
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QObject>

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);

       QTranslator qtTranslator;
       qtTranslator.load("qt_" + QLocale::system().name(),
               QLibraryInfo::location(QLibraryInfo::TranslationsPath));
       app.installTranslator(&qtTranslator);
    for (int bottles(99); bottles > 0; --bottles) {
        std::cout << QApplication::tr("%Ln message(s) saved", "", bottles).toLocal8Bit().constData();

        std::cout << QObject::tr(
            "%1 bottle(s) of beer on the wall\n"
            "%1 bottle(s) of beer\n"
            "Take one down, pass it around\n"
            "%2 bottles of beer on the wall\n\n"
            ).arg(bottles).arg(bottles-1).toLocal8Bit().constData();
    }
}
