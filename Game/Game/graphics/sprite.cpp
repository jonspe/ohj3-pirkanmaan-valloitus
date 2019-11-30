#include "sprite.h"
#include <QDebug>
#include <QtMath>


namespace {
    using SpriteMap = std::map<std::string, QRect>;

    const QRect spriteRect(int x, int y)
    {
        return QRect(x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
    }

    const SpriteMap SPRITE_MAP = {
        {"NULL",                spriteRect(7, 7)},

        {"Grass",               spriteRect(0, 0)},
        {"Evergreen",           spriteRect(1, 0)},
        {"Birch",               spriteRect(2, 0)},
        {"Animals",             spriteRect(3, 0)},
        {"Stone",               spriteRect(4, 0)},
        {"Ore",                 spriteRect(5, 0)},
        {"Diamond",             spriteRect(6, 0)},
        {"Lake",                spriteRect(7, 0)},

        {"Colony",              spriteRect(0, 1)},
        {"Factory",             spriteRect(1, 1)},
        {"Lumber Camp",         spriteRect(2, 1)},
        {"Advanced Lumber Camp",spriteRect(3, 1)},
        {"University",          spriteRect(4, 1)},
        {"Marketplace",         spriteRect(5, 1)},
        {"Victory Monument",    spriteRect(6, 1)},
        {"City",                spriteRect(7, 1)},

        {"Mine",                spriteRect(0, 2)},
        {"Ore Mine",            spriteRect(1, 2)},
        {"Diamond Mine",        spriteRect(2, 2)},
        {"Advanced Mine",       spriteRect(3, 2)},
        {"Farm",                spriteRect(4, 2)},
        {"Advanced Farm",       spriteRect(5, 2)},
        {"Citizen",             spriteRect(6, 2)},
        {"Educated Citizen",    spriteRect(7, 2)},
    };
}

Sprite::Sprite(const std::shared_ptr<ElevatedTileBase> &tile, QPixmap *spriteSheet):
    m_tile(tile),
    m_scenelocation(m_tile->getCoordinatePtr()->asQpoint()),
    m_spriteSheet(spriteSheet),
    m_selected(false),
    m_height_offset(m_tile->getHeight())
{
    m_highlight.setStrength(0);
    m_highlight.setColor(QColor(255, 255, 255));
    setGraphicsEffect(&m_highlight);
}

void Sprite::setSelected(bool selected)
{
    m_selected = selected;
    updateEffect();
}

void Sprite::setHighlighted(bool highlighted)
{
    m_highlighted = highlighted;
    updateEffect();
}

void Sprite::updateEffect()
{
    //This is some ugly stuff because Qt can't stack effects smh

    if (!m_selected && !m_highlighted)
        m_highlight.setStrength(0);
    else if (m_selected && !m_highlighted)
        m_highlight.setStrength(0.15);
    else if (!m_selected && m_highlighted)
        m_highlight.setStrength(0.25);
    else
        m_highlight.setStrength(0.3);

    update();
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
        // maybe optimize with if statements so it doesnt always draw three times ?

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


