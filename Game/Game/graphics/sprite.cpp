#include "sprite.h"
#include <QDebug>
#include <QtMath>


namespace {
    using SpriteMap = std::map<std::string, QRect>;

    const SpriteMap SPRITE_MAP = {
        {"Grass",       QRect(0 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Evergreen",   QRect(1 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Birch",       QRect(2 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Animals",     QRect(3 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Stone",       QRect(4 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Ore",         QRect(5 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Diamond",     QRect(6 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
        {"Lake",        QRect(7 * SPRITE_SIZE, 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, 1 * SPRITE_SIZE)},
    };
}

Sprite::Sprite(const std::shared_ptr<Course::GameObject> &obj, QPixmap* spriteSheet):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()),
    m_spriteSheet(spriteSheet)
{}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ) Q_UNUSED( widget )

    std::string objType = m_gameobject->getType();
    auto it = SPRITE_MAP.find(objType);

    // if object has corresponding type -> spritepos mapping
    if ( it != SPRITE_MAP.end() )
    {
        painter->drawPixmap(
                    boundingRect(),
                    *m_spriteSheet,
                    SPRITE_MAP.at(objType));
    }
}

QRectF Sprite::boundingRect() const
{
    QPoint pos = calculateIsometricPos();

    return QRectF(pos.x() - SPRITE_SIZE/2, pos.y(), SPRITE_SIZE, SPRITE_SIZE);
}

const std::shared_ptr<Course::GameObject> &Sprite::getBoundObject()
{
    return m_gameobject;
}

void Sprite::updateLoc()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool Sprite::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

QPoint Sprite::calculateIsometricPos() const
{
    qreal x = static_cast<qreal>(m_scenelocation.x());
    qreal y = static_cast<qreal>(m_scenelocation.y());

    qreal newX = (x - y) * (SPRITE_SIZE/2);
    qreal newY = (x + y) * (SPRITE_SIZE*SPRITE_SQUASH/2);

    return QPoint(qRound(newX), qRound(newY));
}


