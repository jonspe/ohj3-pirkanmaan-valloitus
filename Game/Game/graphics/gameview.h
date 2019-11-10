#ifndef GAMEVIEW_H
#define GAMEVIEW_H

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
    GameView(QWidget* qt_parent = nullptr);

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
    QPointF m_lastMousePos;
};

#endif // GAMEVIEW_H
