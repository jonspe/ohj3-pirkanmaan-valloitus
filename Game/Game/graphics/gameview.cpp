#include "gameview.h"
#include "sprite.h"

#include <QtMath>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


GameView::GameView(QWidget* qt_parent) :
    QGraphicsView(qt_parent)
{
    setMinimumSize(QSize(640, 480));

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Expanding);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setSizePolicy(policy);
    setMouseTracking(true);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    QPointF point = mapToScene(event->pos());

    point.rx() = floor(point.rx());
    point.ry() = floor(point.ry());

    qDebug() << point;

    // graphicsitem detection in graphicsscene, should do math to check tile instead
    // TODO: use math to detect tile
    // TODO: add function to translate pixel pos to tile coordinate

    // QGraphicsItem* pressed = itemAt(point, QTransform());
    // qDebug() << "ObjID: " <<
    //   static_cast<Sprite*>(pressed)
    //   ->getBoundObject()->ID  << " pressed.";

}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();

    if (event->buttons().testFlag(Qt::LeftButton))
    {
        QPointF delta = pos - m_lastMousePos;
        qreal zoom = viewportTransform().determinant();

        setTransformationAnchor(ViewportAnchor::NoAnchor);
        translate(delta.x()/(qSqrt(zoom)), delta.y()/(qSqrt(zoom)));
    }

    m_lastMousePos = pos;
}

void GameView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(ViewportAnchor::NoAnchor);

    // determine scroll direction
    if (event->delta() < 0)
    {
        scale(.5, .5);
    }
    else
    {
        scale(2, 2);
    }
}



