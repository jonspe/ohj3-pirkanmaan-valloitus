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
#include "setupdialog.h"
#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    SetupDialog* setup_dialog = new SetupDialog();
    setup_dialog->exec();

    unsigned int map_size = setup_dialog->map_size;
    unsigned int player_amount = setup_dialog->player_amount;
    unsigned int seed = setup_dialog->seed;

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

   std::shared_ptr<ObjectManager> object_manager(new ObjectManager);
   std::shared_ptr<Course::iGameEventHandler> event_handler = nullptr;

   Course::WorldGenerator& map_generator = Course::WorldGenerator::getInstance();

   map_generator.addConstructor<Animals>(20);
   map_generator.addConstructor<Birch>(60);
   map_generator.addConstructor<Diamond>(5);
   map_generator.addConstructor<Evergreen>(60);
   map_generator.addConstructor<Grass>(100);
   map_generator.addConstructor<Lake>(30);
   map_generator.addConstructor<Ore>(15);
   map_generator.addConstructor<Sand>(15);
   map_generator.addConstructor<Stone>(30);

   map_generator.generateMap(map_size,map_size,seed, object_manager, event_handler);

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
