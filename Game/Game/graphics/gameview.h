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
    GameView(std::shared_ptr<ObjectManager> object_manager,
             std::shared_ptr<GameEventHandler> event_handler,
             QWidget* qt_parent = nullptr);

    /**
     * @brief Adds a tile to the game scene
     * @param obj shared_ptr<Course::TileBase>
     */
    void addTile(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief sets a 'selected' state to the tile, giving it a slight highlight effect
     * @param tile
     * @param select
     */
    void selectTile(std::shared_ptr<Course::TileBase> tile, bool select);

    /**
     * @brief draw potential changes made to the scene
     */
    void refresh();

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

    std::shared_ptr<ObjectManager> m_object_manager;
    std::shared_ptr<GameEventHandler> m_event_handler;


    // Allows direct manipulation of game scene
    GameScene* m_gs_ptr;

    // Used to calculate mouse delta for panning
    QPoint m_last_mousepos;

    // Used to unhighlight previously hovered on tile
    Sprite* m_last_sprite;

    // Keeps track of view position and scale
    QTransform m_view_transform;

    // Spritesheet to draw sprites from
    QPixmap* m_spriteSheet;
};

#endif // GAMEVIEW_H
