#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Game/graphics/sprite.h"

#include <QGraphicsScene>
#include <memory>

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = nullptr);

    /**
     * @brief Adds a Sprite to the game scene and maps it to its coordinate for indexing
     * @param sprite
     */
    void addSprite(Sprite* sprite);

    /**
     * @brief Gets the one Sprite at specified coordinate
     * @param coord
     * @return Sprite, if no sprite at coord, return nullptr
     */
    Sprite* getSprite(const Course::Coordinate& coord) const;

    /**
     * @brief Gets the first Sprite that is bound by given Tile
     * @param tile
     * @return Sprite, if no sprite with tile, return nullptr
     */
    Sprite* getSprite(const std::shared_ptr<ElevatedTileBase> &tile) const;

private:
    /**
     * @brief for mapping sprites to their coordinates
     */
    std::map<Course::Coordinate, Sprite*> m_coord_sprite_map;

    /**
     * @brief for mapping sprites to their bound tiles
     */
    std::map<std::shared_ptr<ElevatedTileBase>, Sprite*> m_tile_sprite_map;
};

#endif // GAMESCENE_H
