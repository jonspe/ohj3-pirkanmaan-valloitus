#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsColorizeEffect>

#include <memory>
#include <map>

#include "core/gameobject.h"


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
    Sprite(const std::shared_ptr<Course::GameObject> &obj, QPixmap* spriteSheet, int height_offset = 0);

    /**
     * @brief boundingRect
     * @return the bounding rectangle of this item.
     */
    QRectF boundingRect() const override;

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
     * @brief getBoundObject
     * @return the object this item is bound to.
     */
    const std::shared_ptr<Course::GameObject> &getBoundObject();

    /**
     * @brief updateLoc moves the item if the position has changed.
     */
    void updateLoc();

    /**
     * @brief checks if this instance has obj as bound obj.
     * @param obj to compare to.
     * @return True: if obj is pointing to the same object as this item.
     * False otherwise.
     */
    bool isSameObj(std::shared_ptr<Course::GameObject> obj);

private:
    QPoint calculateIsometricPos() const;

    const std::shared_ptr<Course::GameObject> m_gameobject;
    QPoint m_scenelocation;
    QPixmap* m_spriteSheet;

    int m_height_offset;
};

#endif // SPRITE_H
