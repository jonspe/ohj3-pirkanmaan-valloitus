#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsColorizeEffect>

#include <memory>
#include <map>

#include "core/gameobject.h"
#include "Game/tiles/elevatedtilebase.h"

int const SPRITE_SIZE = 256;
qreal const SPRITE_SQUASH = 0.5771;


class Sprite : public QGraphicsItem
{
public:
    /**
     * @brief Constructor
     * @param obj shared_ptr to the obj.
     * @param size of the created item in pixels.
     * @pre obj must have a valid Coordinate.
     */
    Sprite(const std::shared_ptr<ElevatedTileBase> &tile, QPixmap* spriteSheet);

    /**
     * @brief sets highlight effect according to color and strength
     * @param color
     * @param strength
     */
    void setHighlight(qreal strength, const QColor &color = QColor(255, 255, 255));

    /**
     * @brief boundingRect
     * @return the bounding rectangle of this item.
     */
    QRectF boundingRect() const override;

    /**
     * @brief tileRect
     * @return the bounding rectangle for tile sprite
     */
    QRectF tileRect() const;

    /**
     * @brief topRect
     * @return the bounding rectangle for top item sprites (building, worker)
     */
    QRectF topRect() const;

    /**
     * @brief paints the item
     * @param painter
     * @param option
     * @param widget
     * @note The GraphicsView containing the scene this belongs to
     * usually calls this function.
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    const std::shared_ptr<ElevatedTileBase> &getBoundTile();

private:
    QPoint calculateIsometricPos() const;

    const std::shared_ptr<ElevatedTileBase> m_tile;

    QPoint m_scenelocation;
    QPixmap* m_spriteSheet;

    QGraphicsColorizeEffect m_highlight;

    int m_height_offset;
};

#endif // SPRITE_H
