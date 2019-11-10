#include "sprite.h"
#include <QDebug>
#include <QtMath>

namespace {
    int const SIZE = 256;
    qreal const SQUASH = 0.406;

    using SpriteMap = std::map<std::string, QRect>;

    const SpriteMap SPRITE_MAP = {
        {"Grass",       QRect(0 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Evergreen",   QRect(1 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Birch",       QRect(2 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Animals",     QRect(3 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Stone",       QRect(4 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Ore",         QRect(5 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Diamond",     QRect(6 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
        {"Lake",        QRect(7 * SIZE, 0 * SIZE, 1 * SIZE, 1 * SIZE)},
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
        QPoint pos = calculateRotatedPos();

        painter->drawPixmap(
                    QRect(pos.x(), pos.y(), SIZE, SIZE),
                    *m_spriteSheet,
                    SPRITE_MAP.at(objType));
    }
}

QRectF Sprite::boundingRect() const
{
    QPoint pos = calculateRotatedPos();

    return QRectF(pos.x(), pos.y(), SIZE, SIZE);
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

QPoint Sprite::calculateRotatedPos() const
{
    // optimization for 45 deg angles so don't have to sin/cos
    const qreal sqr2inv = 0.70710678;

    qreal x = static_cast<qreal>(m_scenelocation.x());
    qreal y = static_cast<qreal>(m_scenelocation.y());

    // rotate around origin by 45 deg
    qreal newX = x*sqr2inv*sqr2inv - y*sqr2inv*sqr2inv;
    qreal newY = y*sqr2inv + x*sqr2inv;

    return QPoint(qRound(SIZE * newX), qRound(SIZE * newY * SQUASH));
}


