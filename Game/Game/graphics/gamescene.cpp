#include "gamescene.h"

GameScene::GameScene(QObject *parent): QGraphicsScene(parent) {}

void GameScene::addSprite(Sprite *sprite)
{
    addItem(sprite);
    m_sprite_map[sprite->getBoundObject()->getCoordinate()] = sprite;
}

Sprite *GameScene::getSprite(const Course::Coordinate &coord) const
{
    try
    {
        return m_sprite_map.at(coord);
    }
    catch ( std::out_of_range ex )
    {
        return nullptr;
    }
}
