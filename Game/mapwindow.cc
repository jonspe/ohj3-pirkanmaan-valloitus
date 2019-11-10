#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "core/worldgenerator.h"
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
#include "Game/graphics/gamescene.h"
#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_gamescene(new GameScene(this)),
    m_gameview(new GameView())
{
    m_ui->setupUi(this);

    GameView* gv_rawptr = m_gameview.get();
    GameScene* gs_rawptr = m_gamescene.get();

    m_ui->horizontalLayout_2->insertWidget(0, gv_rawptr);
    m_gameview->setScene(gs_rawptr);

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
    map_generator.addConstructor<Stone>(30);

    map_generator.generateMap(100,100,1337, object_manager, event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = object_manager->getAllTiles();
    std::vector<std::shared_ptr<Course::GameObject>> objs(tiles.begin(), tiles.end());

    gs_rawptr->drawMultipleItems(objs);
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

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->updateItem(obj);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->drawItem(obj);
}
