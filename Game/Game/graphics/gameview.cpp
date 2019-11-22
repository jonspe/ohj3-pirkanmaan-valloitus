#include "gameview.h"
#include "Game/core/mapgenerator.h"
#include "Game/tiles/elevatedtilebase.h"
#include "core/gameobject.h"

#include <QtMath>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


GameView::GameView(QWidget* qt_parent,
                   const std::shared_ptr<GameEventHandler>& eventhandler,
                   const std::shared_ptr<ObjectManager>& objectmanager) :
    QGraphicsView(qt_parent), EVENTHANDLER(eventhandler), OBJECTMANAGER(objectmanager)
{
    setupFrameProperties();

    m_gs_ptr = new GameScene(this);
    setScene(m_gs_ptr);

    m_spriteSheet = new QPixmap(":/images/sprites.png");
    m_highlight_effect.setColor(QColor(255, 255, 255));
    m_highlight_effect.setStrength(0.3);
}


void GameView::addTile(std::shared_ptr<Course::TileBase> obj)
{
    std::shared_ptr<ElevatedTileBase> tile = std::dynamic_pointer_cast<ElevatedTileBase>(obj);

    if (tile == nullptr)
    {
        throw std::bad_cast();
    }

    Sprite* sprite = new Sprite(tile, m_spriteSheet);
    m_gs_ptr->addSprite(sprite);
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
    std::shared_ptr<Course::TileBase> tile = OBJECTMANAGER->getTile(point);

    if (tile != nullptr)
    {
        emit tilePressed(tile);
    }
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    if (event->buttons().testFlag(Qt::LeftButton))
    {
        QPoint delta = pos - m_lastMousePos;
        qreal zoom = m_viewTransform.m22();

        m_viewTransform.translate(delta.x()/zoom, delta.y()/zoom);
        setTransform(m_viewTransform);
    }

    Sprite* sprite = m_gs_ptr->getSprite(screenToCoordinate(pos));

    if (sprite != nullptr)
    {
        m_highlight_effect.setEnabled(true);
        sprite->setGraphicsEffect(&m_highlight_effect);
    }
    else
    {
        m_highlight_effect.setEnabled(false);
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

void GameView::setupFrameProperties()
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



