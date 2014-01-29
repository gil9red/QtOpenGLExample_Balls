#ifndef USCENE3D_H
#define USCENE3D_H

#include <QGLWidget>
#include <QVector>
#include <QVariantMap>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

#include <math.h>

#include <GL/glu.h>


typedef QVariantMap UGLObject;

/*
 * Алгоритм притягивания точек взят отсюда:
 * https://code.google.com/p/cplusplus-lessons/source/browse/lesson43/lesson43.cpp
 *
*/

class UScene3D: public QGLWidget
{
    Q_OBJECT

public:
    UScene3D(QWidget* parent = 0);
    void addObject( const QPointF & pos, float size,
                    const QColor & color, const QPointF & moveTo );

private:
    void drawObject( const UGLObject & object );

private:
    QVector < UGLObject > objects;
    QTimer timer;
    bool down;
    QPoint cursorPos;

private slots:
    void tick();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
};

#endif // USCENE3D_H
