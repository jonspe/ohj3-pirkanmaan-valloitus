#include "gameview.h"
#include "sprite.h"

#include <QtMath>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


GameView::GameView(QWidget* qt_parent, GameScene* gs_ptr) :
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

    m_gs_ptr = gs_ptr;
}

Course::Coordinate GameView::screenToCoordinate(QPoint screenPos)
{
    QPointF scenePos = mapToScene(screenPos);

    qreal tileX = (scenePos.x()/(SPRITE_SIZE/2) + scenePos.y()/(SPRITE_SIZE*SPRITE_SQUASH/2)) / 2;
    qreal tileY = (scenePos.y()/(SPRITE_SIZE*SPRITE_SQUASH/2) - scenePos.x()/(SPRITE_SIZE/2)) / 2;

    return Course::Coordinate(qFloor(tileX), qFloor(tileY));
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    Course::Coordinate point = screenToCoordinate(event->pos());

    qDebug() << point.asQpoint();
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



