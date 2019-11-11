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
#include "Game/core/player.h"
#include "Game/core/resources.h"
#include "Game/core/mapgenerator.h"
#include "setupdialog.h"
#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_gameview(new GameView())
{
    m_ui->setupUi(this);
    GameView* gv_rawptr = m_gameview.get();
    m_ui->horizontalLayout_2->insertWidget(0, gv_rawptr);

    SetupDialog* setup_dialog = new SetupDialog();
    setup_dialog->exec();

    unsigned int map_size = setup_dialog->map_size;
    unsigned int player_amount = setup_dialog->player_amount;
    unsigned int seed = setup_dialog->seed;


    std::shared_ptr<ObjectManager> object_manager(new ObjectManager);
    std::shared_ptr<Course::iGameEventHandler> event_handler = nullptr;

    std::map<std::string, std::shared_ptr<Player>> players;

    unsigned int i = 1;
    while (i <= player_amount){
        std::string player_id = std::to_string(i);
        std::shared_ptr<Player> new_player(new Player(player_id));
        players[player_id] = new_player;
        i++;
    }

    MapGenerator& map_generator = MapGenerator::getInstance();

    map_generator.generateMap(map_size,map_size,seed, object_manager, event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = object_manager->getAllTiles();
    std::vector<std::shared_ptr<Course::GameObject>> objs(tiles.begin(), tiles.end());

    gv_rawptr->drawMultipleItems(objs);

    Course::ResourceMap resource_stockpile = players["1"]->getResources();
    int gold_count = resource_stockpile.at(Course::BasicResource::MONEY);
    int gold_change = 15;
    int food_count = resource_stockpile.at(Course::BasicResource::FOOD);
    int food_change = 12;
    int wood_count = resource_stockpile.at(Course::BasicResource::WOOD);
    int wood_change = 6;
    int stone_count = resource_stockpile.at(Course::BasicResource::STONE);
    int stone_change = 3;
    int ore_count = resource_stockpile.at(Course::BasicResource::ORE);
    int ore_change = 1;

    QString gold_qstring = QString::number(gold_count);
    QString gold_change_qstring =  QString::number(gold_change);
    QString gold_text = QString("%1 + %2").arg(gold_qstring, gold_change_qstring);
    m_ui->gold_label->setText(gold_text);

    QString food_qstring = QString::number(food_count);
    QString food_change_qstring =  QString::number(food_change);
    QString food_text = QString("%1 + %2").arg(food_qstring, food_change_qstring);
    m_ui->food_label->setText(food_text);

    QString wood_qstring = QString::number(wood_count);
    QString wood_change_qstring =  QString::number(wood_change);
    QString wood_text = QString("%1 + %2").arg(wood_qstring, wood_change_qstring);
    m_ui->wood_label->setText(wood_text);

    QString stone_qstring = QString::number(stone_count);
    QString stone_change_qstring =  QString::number(stone_change);
    QString stone_text = QString("%1 + %2").arg(stone_qstring, stone_change_qstring);
    m_ui->stone_label->setText(stone_text);

    QString ore_qstring = QString::number(ore_count);
    QString ore_change_qstring =  QString::number(ore_change);
    QString ore_text = QString("%1 + %2").arg(ore_qstring, ore_change_qstring);
    m_ui->ore_label->setText(ore_text);



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

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_gameview->drawItem(obj);
}
