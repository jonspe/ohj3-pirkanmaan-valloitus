#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"


const std::pair<int, int> SCENE_WIDTH_LIMITS = {1, 100};
const std::pair<int, int> SCENE_HEIGHT_LIMITS = {1, 100};
const std::pair<int, int> SCENE_SCALE_LIMITS = {1, 500};

/**
 * @brief The SimpleGameScene is a custom QGraphicsScene that shows
 * a simple rendering of the game map.
 */
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the class.
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     */
    GameScene(QWidget* qt_parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~GameScene() override;

    /**
     * @brief draw a new item to the map.
     * @param obj shared ptr to the object
     * @pre obj must have a valid coordinate property.
     * @post Exception guarantee: None
     */
    void drawItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief draws multiple items into the map
     * @param vector of obj shared ptrs to the object
     * @pre objs must have a valid coordinate property.
     * @post Exception guarantee: None
     */
    void drawMultipleItems( std::vector<std::shared_ptr<Course::GameObject>> objs);

private:
    QPixmap* m_spriteSheet;
};

#endif // GAMESCENE_H

