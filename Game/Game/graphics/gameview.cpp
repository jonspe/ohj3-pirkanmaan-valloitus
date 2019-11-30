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
    QGraphicsView(qt_parent), EVENTHANDLER(eventhandler), OBJECTMANAGER(objectmanager),
    m_last_sprite(nullptr)
{
    setupFrameProperties();

    m_gs_ptr = new GameScene(this);
    setScene(m_gs_ptr);

    m_spriteSheet = new QPixmap(":/images/sprites.png");
}


void GameView::addTile(std::shared_ptr<Course::TileBase> tile)
{
    std::shared_ptr<ElevatedTileBase> elevatedTile = std::dynamic_pointer_cast<ElevatedTileBase>(tile);

    if (elevatedTile == nullptr)
    {
        throw std::bad_cast();
    }

    Sprite* sprite = new Sprite(elevatedTile, m_spriteSheet);
    m_gs_ptr->addSprite(sprite);
}

void GameView::selectTile(std::shared_ptr<Course::TileBase> tile, bool select)
{
    auto elevatedTile = std::dynamic_pointer_cast<ElevatedTileBase>(tile);
    if (elevatedTile == nullptr)
    {
        throw std::bad_cast();
    }

    Sprite* sprite = m_gs_ptr->getSprite(elevatedTile);

    // not important if can't highlight
    if (sprite != nullptr)
    {
        sprite->setSelected(select);
    }
}

void GameView::refresh()
{
    updateSceneRect(QRectF(0, 0, width(), height()));
    update();
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

    // Pan the view
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        QPoint delta = pos - m_last_mousepos;
        qreal zoom = m_view_transform.m22();

        m_view_transform.translate(delta.x()/zoom, delta.y()/zoom);
        setTransform(m_view_transform);
    }

    Sprite* sprite = m_gs_ptr->getSprite(screenToCoordinate(pos));

    // Highlight sprite on hover
    if (sprite != nullptr && sprite != m_last_sprite)
    {
        sprite->setHighlighted(true);
    }

    // Unhighlight when mouse leaves sprite
    if (m_last_sprite != nullptr && m_last_sprite != sprite)
    {
        m_last_sprite->setHighlighted(false);
    }

    m_last_sprite = sprite;
    m_last_mousepos = pos;
}

void GameView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = 1.2;

    // determine scroll direction and scale direction
    if (event->delta() < 0)
        scaleFactor = 1/scaleFactor;

    m_view_transform.scale(scaleFactor, scaleFactor);
    setTransform(m_view_transform);
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



