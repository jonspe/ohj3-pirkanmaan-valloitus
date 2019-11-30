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
     * @brief sets the sprite in a 'selected' state, giving a highlight effect
     * @param selected
     */
    void setSelected(bool selected);

    /**
     * @brief sets the sprite in a 'highlighted' state, which occurs when
     * mouse is hovered over the sprite
     * @param highlighted
     */
    void setHighlighted(bool highlighted);

    /**
     * @brief isSelected
     * @return
     */
    bool isSelected();

    /**
     * @brief calculates final effect based on selected and highlighted state
     */
    void updateEffect();

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

    /**
     * @brief returns the tile this sprite is bound to
     * @return bound tile
     */
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

    bool m_highlighted;
    bool m_selected;

    // Is used to draw sprite in varying Y position
    int m_height_offset;
};

#endif // SPRITE_H
