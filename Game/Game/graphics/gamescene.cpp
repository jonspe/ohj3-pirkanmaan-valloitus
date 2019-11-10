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

void GameScene::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items();
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : items_list ){
            Sprite* mapItem = static_cast<Sprite*>(item);
            if (mapItem->isSameObj(obj)){
                mapItem->updateLoc();
            }
        }
    }
}

void GameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            Sprite* mapitem = static_cast<Sprite*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }
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
