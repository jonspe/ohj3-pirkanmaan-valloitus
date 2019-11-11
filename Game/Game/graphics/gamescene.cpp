#include "gamescene.h"
#include "sprite.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>


GameScene::GameScene(QWidget* parent):
    QGraphicsScene(parent)
{
    m_spriteSheet = new QPixmap(":/images/sprites.png");
}

GameScene::~GameScene()
{
    delete m_spriteSheet;
    m_spriteSheet = nullptr;
}


void GameScene::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    Sprite* nItem = new Sprite(obj, m_spriteSheet);
    addItem(nItem);
}

void GameScene::drawMultipleItems(std::vector<std::shared_ptr<Course::GameObject>> objs)
{
    for ( auto obj: objs)
    {
        drawItem(obj);
    }
}
