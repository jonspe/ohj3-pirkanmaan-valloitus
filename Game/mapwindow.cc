#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "core/worldgenerator.h"
#include "graphics/simplemapitem.h"
#include "Game/tiles/animals.h"
#include "Game/tiles/birch.h"
#include "Game/tiles/diamond.h"
#include "Game/tiles/evergreen.h"
#include "Game/tiles/grass.h"
#include "Game/tiles/lake.h"
#include "Game/tiles/ores.h"
#include "Game/tiles/sand.h"
#include "Game/tiles/stone.h"
#include "Game/core/objectmanager.h"
#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

   std::shared_ptr<Course::ObjectManager> object_manager(new Course::ObjectManager);
   std::shared_ptr<Course::iGameEventHandler> event_handler = nullptr;

   Course::WorldGenerator& map_generator = Course::WorldGenerator::getInstance();

   map_generator.addConstructor<Course::Animals>(20);
   map_generator.addConstructor<Course::Birch>(60);
   map_generator.addConstructor<Course::Diamond>(5);
   map_generator.addConstructor<Course::Evergreen>(60);
   map_generator.addConstructor<Course::Grass>(100);
   map_generator.addConstructor<Course::Lake>(30);
   map_generator.addConstructor<Course::Ore>(15);
   map_generator.addConstructor<Course::Sand>(15);
   map_generator.addConstructor<Course::Stone>(30);

   map_generator.generateMap(100,100,1337, object_manager, event_handler);

}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::setSize(int width, int height)
{
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
