#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "core/coordinate.h"
#include "core/gameobject.h"
#include "Game/graphics/sprite.h"
#include "Game/graphics/gamescene.h"
#include "Game/core/gameeventhandler.h"
#include "Game/core/objectmanager.h"

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
    GameView(QWidget* qt_parent = nullptr,
             const std::shared_ptr<GameEventHandler>& eventhandler = nullptr,
             const std::shared_ptr<ObjectManager>& objectmanager = nullptr);

    /**
     * @brief Draws a TileBase on the screen as Sprite
     * @param obj shared_ptr<GameObject>
     */
    void addTile(std::shared_ptr<Course::TileBase> obj);

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

signals:
    /**
     * @brief tilePressed is emitted when the user has clicked on a tile
     * @param tile
     */
    void tilePressed(std::shared_ptr<Course::TileBase> tile);

private:
    /**
     * @brief Sets properties for graphicsview, like sizing and mouse tracking
     */
    void setupFrameProperties();

    const std::shared_ptr<GameEventHandler> EVENTHANDLER;
    const std::shared_ptr<ObjectManager> OBJECTMANAGER;

    GameScene* m_gs_ptr;

    QPoint m_lastMousePos;
    QTransform m_viewTransform;

    QPixmap* m_spriteSheet;

    /**
     * @brief Highlight effect for hovered over tile
     */
    QGraphicsColorizeEffect m_highlight_effect;
};

#endif // GAMEVIEW_H
