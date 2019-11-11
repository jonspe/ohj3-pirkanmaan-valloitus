#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "core/coordinate.h"
#include "core/gameobject.h"
#include <memory>
#include <QGraphicsView>
#include <QTransform>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the class.
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     */
    GameView(QWidget* qt_parent = nullptr);

    /**
     * @brief Draws a GameObject on the screen as Sprite
     * @param obj shared_ptr<GameObject>
     */
    void drawItem(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Draws multiple GameObjects on the screen as Sprites
     * @param obj vector<shared_ptr<GameObject>>
     */
    void drawMultipleItems(std::vector<std::shared_ptr<Course::GameObject>> objs);

    /**
     * @brief Function for mapping view coordinates to tile coordinates
     * @param screenPos position on the map view
     * @return Course::Coordinate tile coordinate
     */
    Course::Coordinate screenToCoordinate(QPoint screenPos);

    /**
     * @brief event handler for mouse presses
     * @param mouse event that has happened.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief event handler for mouse movement
     * @param mouse event that has happened.
     */
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief event handler for mousewheel scrolling
     * @param wheel event that has happened.
     */
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene* m_gs_ptr;

    QPointF m_lastMousePos;
    QTransform m_viewTransform;

    QPixmap* m_spriteSheet;
};

#endif // GAMEVIEW_H
