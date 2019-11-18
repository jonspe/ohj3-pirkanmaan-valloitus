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
#include "Game/buildings/city.h"
#include "Game/buildings/university.h"
#include "Game/core/objectmanager.h"
#include "Game/core/player.h"
#include "Game/core/resources.h"
#include "Game/core/mapgenerator.h"
#include "Game/core/gameeventhandler.h"
#include "setupdialog.h"
#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler)
{
    SetupDialog* setup_dialog = new SetupDialog();
    setup_dialog->exec();

    unsigned int map_size = setup_dialog->map_size;
    unsigned int player_amount = setup_dialog->player_amount;
    unsigned int seed = setup_dialog->seed;


    std::shared_ptr<ObjectManager> object_manager(new ObjectManager);
    std::shared_ptr<GameEventHandler> event_handler(new GameEventHandler);


    m_ui->setupUi(this);
    m_gameview = std::shared_ptr<GameView>(new GameView(nullptr, event_handler, object_manager));
    m_ui->horizontalLayout_2->insertWidget(0, m_gameview.get());


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

    m_gameview->drawMultipleItems(objs);


    i = 1; // set player resources to default at start of game
    while (i <= player_amount){
        event_handler->setPresetResources(players[std::to_string(i)]);
        i++;
    }

    int current_player = 0;
    int turn = 0;

    while(turn < 1){ // something to end the loop, replace later

        current_player++;
        if (current_player == player_amount + 1)
        {
            turn++;
            current_player = 1;
        }       

        if (turn == 1) // randomly place city for player
        {
            std::shared_ptr<City> new_city(new City(event_handler, object_manager,players[std::to_string(current_player)]));
            event_handler->firstTurn(map_size,current_player,object_manager,players, new_city);
        }
        players[std::to_string(current_player)]->generateResources(object_manager);
        updateStatusBar(event_handler,players,current_player, turn);


    }



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

void MapWindow::updateStatusBar(std::shared_ptr<GameEventHandler> event_handler, std::map<std::string, std::shared_ptr<Player>> players, int current_player, int turn)
{

    QString player_number_qstring =  QString::number(current_player);
    QString player_text = QString("Player %1").arg(player_number_qstring);
    m_ui->player_label->setText(player_text);

    QString turn_number_qstring =  QString::number(turn);
    QString turn_text = QString("Turn %1").arg(turn_number_qstring);
    m_ui->turn_label->setText(turn_text);

    Course::ResourceMap resource_stockpile = event_handler->getResources(players[std::to_string(current_player)]);

    int gold_count = resource_stockpile.at(Course::BasicResource::MONEY);
    int food_count = resource_stockpile.at(Course::BasicResource::FOOD);
    int wood_count = resource_stockpile.at(Course::BasicResource::WOOD);
    int stone_count = resource_stockpile.at(Course::BasicResource::STONE);
    int ore_count = resource_stockpile.at(Course::BasicResource::ORE);

    QString gold_qstring = QString::number(gold_count);
    QString gold_text = QString("%1").arg(gold_qstring);
    m_ui->gold_label->setText(gold_text);

    QString food_qstring = QString::number(food_count);
    QString food_text = QString("%1").arg(food_qstring);
    m_ui->food_label->setText(food_text);

    QString wood_qstring = QString::number(wood_count);
    QString wood_text = QString("%1").arg(wood_qstring);
    m_ui->wood_label->setText(wood_text);

    QString stone_qstring = QString::number(stone_count);
    QString stone_text = QString("%1").arg(stone_qstring);
    m_ui->stone_label->setText(stone_text);

    QString ore_qstring = QString::number(ore_count);
    QString ore_text = QString("%1").arg(ore_qstring);
    m_ui->ore_label->setText(ore_text);
}
