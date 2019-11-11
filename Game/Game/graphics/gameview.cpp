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

    setTransformationAnchor(ViewportAnchor::NoAnchor);
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
        qreal zoom = m_viewTransform.m22();

        m_viewTransform.translate(delta.x()/zoom, delta.y()/zoom);
        setTransform(m_viewTransform);
    }

    m_lastMousePos = pos;
}

void GameView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = 1.2;

    // determine scroll direction and scale direction
    if (event->delta() < 0)
        scaleFactor = 1/scaleFactor;

    m_viewTransform.scale(scaleFactor, scaleFactor);
    setTransform(m_viewTransform);
}



