#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "core/coordinate.h"
#include "gamescene.h"
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
    GameView(QWidget* qt_parent = nullptr, GameScene* gs_ptr = nullptr);

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
    GameScene* m_gs_ptr;

    QPointF m_lastMousePos;
    QTransform m_viewTransform;
};

#endif // GAMEVIEW_H
