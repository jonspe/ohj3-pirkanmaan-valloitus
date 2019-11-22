#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Game/graphics/sprite.h"

#include <QGraphicsScene>
#include <memory>

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = nullptr);

    void addSprite(Sprite* sprite);
    Sprite* getSprite(const Course::Coordinate& coord) const;

private:
    std::map<Course::Coordinate, Sprite*> m_coord_sprite_map;
};

#endif // GAMESCENE_H
