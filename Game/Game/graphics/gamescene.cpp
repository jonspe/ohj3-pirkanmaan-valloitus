#include "gamescene.h"

GameScene::GameScene(QObject *parent): QGraphicsScene(parent) {}

void GameScene::addSprite(Sprite *sprite)
{
    addItem(sprite);
    m_coord_sprite_map[sprite->getBoundTile()->getCoordinate()] = sprite;
    m_tile_sprite_map[sprite->getBoundTile()] = sprite;
}

Sprite *GameScene::getSprite(const Course::Coordinate &coord) const
{
    try
    {
        return m_coord_sprite_map.at(coord);
    }
    catch (std::out_of_range)
    {
        return nullptr;
    }
}

Sprite *GameScene::getSprite(const std::shared_ptr<ElevatedTileBase> &tile) const
{
    try
    {
        return m_tile_sprite_map.at(tile);
    }
    catch (std::out_of_range)
    {
        return nullptr;
    }
}
