#include "../header/MainProcessor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainProcessor processor(896, 896);
    //processor.run_main_window();
    qDebug() << a.applicationDirPath();

    processor.run_game();

    /*
    Pokemon sceptile("Sceptile", 254, {GRASS}, {70, 85, 65, 105, 85, 120});
    sceptile.print_total_stats();

    Pokemon garchomp("Garchomp", 445, {DRAGON, GROUND}, {108, 130, 95, 80, 85, 102});
    garchomp.print_total_stats();
    */


    return a.exec();
}
