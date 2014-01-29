#include <QApplication>
#include "UScene3D.h"

#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qsrand( QDateTime::currentMSecsSinceEpoch() );

    UScene3D window;    
    window.resize(500, 500);

    int number = 7000;

    int width = window.width();
    int height = window.height();

    for ( int i = 0; i < number; i++ )
    {
        QPointF pos( qrand() % width - width / 2,
                     qrand() % height - height / 2 );
        float size = /*3*/ qrand() % 3 + 1;
        QColor color( qrand() % 255, qrand() % 255, qrand() % 255 );
        QPointF moveTo( qrand() % width / 100.0 - 2.4,
                        qrand() % height / 100.0 - 2.4 );

        window.addObject( pos, size, color, moveTo );
    }

    window.show();

    return app.exec();
}
