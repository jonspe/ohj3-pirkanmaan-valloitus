#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsColorizeEffect>

#include <memory>
#include <map>

#include "core/gameobject.h"
#include "Game/tiles/elevatedtilebase.h"

/**
 * @brief SPRITE_SIZE: Size in pixels of
 * individual sprite in spritesheet
 */
int const SPRITE_SIZE = 256;

/**
 * @brief SPRITE_SQUASH: Ratio of top surface vs sides
 * for tile placement on the y-axis.
 */
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
    /**
     * @brief Calculates the position in the graphics view based on
     * the sprite's game coordinates.
     * @return QPoint screen position
     */
    QPoint calculateIsometricPos() const;

    /**
     * @brief The tile the sprite is bound to
     */
    const std::shared_ptr<ElevatedTileBase> m_tile;

    /**
     * @brief The position of the tile in game coordinates, stored
     * for efficiency purposes
     */
    QPoint m_scenelocation;

    /**
     * @brief Spritesheet for drawing the sprite from
     */
    QPixmap* m_spriteSheet;

    /**
     * @brief Highlight effect for displaying claimed tiles
     */
    QGraphicsColorizeEffect m_highlight;

    /**
     * @brief Defines how
     */
    int m_height_offset;
};

#endif // SPRITE_H
