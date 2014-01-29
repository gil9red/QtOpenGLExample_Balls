#include "UScene3D.h"

/// PUBLIC
UScene3D::UScene3D(QWidget* parent)
    : QGLWidget( parent ),
      down(false)
{
    setMouseTracking( true );

    timer.setInterval( 25 );

    connect( &timer, SIGNAL( timeout() ), SLOT( tick() ) );
    timer.start();
}
void UScene3D::addObject( const QPointF & pos, float size,
                          const QColor & color, const QPointF & moveTo )
{
    UGLObject object;
    object[ "pos" ] = pos;
    object[ "size" ] = size;
    object[ "color" ] = color.name();
    object[ "moveTo" ] = moveTo;

    objects << object;
}

/// PRIVATE
void UScene3D::drawObject( const UGLObject & object )
{
    QPointF pos = object[ "pos" ].toPointF();
    float size = object[ "size" ].toFloat();
    QColor color = QColor( object[ "color" ].toString() );

    glPointSize( size );
    qglColor( color );

    glBegin( GL_POINTS );
    glVertex2i( pos.x(), pos.y() );
    glEnd();
}

/// PRIVATE SLOTS
void UScene3D::tick()
{
    for ( int i = 0; i < objects.size(); i++ )
    {
        UGLObject & obj = objects[i];

        QPointF pos = obj[ "pos" ].toPointF();
        QPointF moveTo = obj[ "moveTo" ].toPointF();

        obj[ "pos" ] = pos + moveTo;

        if ( down )
        {
            float x1 = pos.x();
            float y1 = pos.y();

            float x2 = cursorPos.x() - width()/2;
            float y2 = -cursorPos.y() + height()/2;

            float d = sqrt( (x1 - x2) * (x1 - x2)
                            + (y1 - y2) * (y1 - y2) );
            x1 += 5 * (x2 - x1) / d;
            y1 += 5 * (y2 - y1) / d;

            obj[ "pos" ] = QPointF( x1, y1 );
        }
    }

    updateGL();
}

/// PROTECTED
void UScene3D::initializeGL()
{
    qglClearColor( Qt::black );
}
void UScene3D::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    gluOrtho2D(0, width, 0, height);
}
void UScene3D::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glPushMatrix();

    glTranslated( width() / 2, height() / 2, 0 );

    foreach ( const UGLObject & obj, objects )
        drawObject( obj );

    glPopMatrix();
}

void UScene3D::mousePressEvent( QMouseEvent * event )
{
    if ( event->button() == Qt::LeftButton )
        down = true;
}
void UScene3D::mouseReleaseEvent( QMouseEvent * event )
{
    down = false;

    if ( event->button() == Qt::MiddleButton )
    {
        for ( int i = 0; i < objects.size(); i++ )
        {
            UGLObject & obj = objects[i];
            obj[ "moveTo" ] = QPointF( qrand() % width() / 100.0 - 2.4,
                                      qrand() % height() / 100.0 - 2.4 );
        }

    }
}
void UScene3D::mouseMoveEvent( QMouseEvent * event )
{
    cursorPos = event->pos();
}
