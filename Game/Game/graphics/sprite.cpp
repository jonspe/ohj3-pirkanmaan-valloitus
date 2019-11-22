#include "sprite.h"
#include <QDebug>
#include <QtMath>


namespace {
    using SpriteMap = std::map<std::string, QRect>;

    const SpriteMap SPRITE_MAP = {
        {"NULL",        QRect(7 * SPRITE_SIZE, 7 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},

        {"Grass",       QRect(0 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Evergreen",   QRect(1 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Birch",       QRect(2 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Animals",     QRect(3 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Stone",       QRect(4 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Ore",         QRect(5 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Diamond",     QRect(6 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Lake",        QRect(7 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},

        {"Lumber Camp", QRect(0 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Windmill",    QRect(1 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Factory",     QRect(2 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Solar Farm",  QRect(3 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Mine",        QRect(4 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"University",  QRect(5 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"City",        QRect(6 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},

        {"Advanced Lumber Camp",    QRect(0 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Farm",                    QRect(1 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Advanced Farm",           QRect(1 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Victory Monument",        QRect(2 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Colony",                  QRect(3 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},

        {"Advanced Mine",           QRect(4 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Diamond Mine",            QRect(4 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Ore Mine",                QRect(4 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},

        {"University",              QRect(5 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"City",                    QRect(6 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},

        {"Citizen",             QRect(0 * SPRITE_SIZE, 3 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
        {"Educated Citizen",    QRect(1 * SPRITE_SIZE, 3 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE)},
    };
}

Sprite::Sprite(const std::shared_ptr<ElevatedTileBase> &tile, QPixmap *spriteSheet):
    m_tile(tile),
    m_scenelocation(m_tile->getCoordinatePtr()->asQpoint()),
    m_spriteSheet(spriteSheet),
    m_height_offset(m_tile->getHeight())
{

}

void Sprite::setHighlight(qreal strength, const QColor &color)
{
    if (strength < .001)
    {
        m_highlight.setEnabled(false);
    }
    else
    {
        m_highlight.setColor(color);
        m_highlight.setStrength(strength);
        m_highlight.setEnabled(true);
    }
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ) Q_UNUSED( widget )

    std::string tileType = m_tile->getType();
    std::string buildingType = "NULL";
    std::string workerType = "NULL";

    if (m_tile->getBuildings().size() == 1)
        buildingType = m_tile->getBuildings().front()->getType();

    if (m_tile->getWorkers().size() == 1)
        workerType = m_tile->getWorkers().front()->getType();

    // if object has corresponding type -> spritepos mapping
    if ( SPRITE_MAP.find(tileType) != SPRITE_MAP.end() )
    {
        // draw elements in correct drawing order: tile, building, worker
        // TODO: maybe optimize with if statements so it doesnt always draw three times ?

        painter->drawPixmap(tileRect(), *m_spriteSheet, SPRITE_MAP.at(tileType));
        painter->drawPixmap(topRect(), *m_spriteSheet, SPRITE_MAP.at(buildingType));
        painter->drawPixmap(topRect(), *m_spriteSheet, SPRITE_MAP.at(workerType));
    }
}

const std::shared_ptr<ElevatedTileBase> &Sprite::getBoundTile()
{
    return m_tile;
}

QRectF Sprite::boundingRect() const
{
    QPoint pos = calculateIsometricPos();
    return QRectF(pos.x() - SPRITE_SIZE/2, pos.y() - m_height_offset - 110, SPRITE_SIZE, SPRITE_SIZE + 110);
}

QRectF Sprite::tileRect() const
{
    QPoint pos = calculateIsometricPos();
    return QRectF(pos.x() - SPRITE_SIZE/2, pos.y() - m_height_offset, SPRITE_SIZE, SPRITE_SIZE);
}

QRectF Sprite::topRect() const
{
    return tileRect().translated(0, -110);
}

QPoint Sprite::calculateIsometricPos() const
{
    qreal x = static_cast<qreal>(m_scenelocation.x());
    qreal y = static_cast<qreal>(m_scenelocation.y());

    qreal newX = (x - y) * (SPRITE_SIZE/2);
    qreal newY = (x + y) * (SPRITE_SIZE*SPRITE_SQUASH/2);

    return QPoint(qRound(newX), qRound(newY));
}


