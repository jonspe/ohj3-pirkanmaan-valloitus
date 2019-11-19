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

    map_size = setup_dialog->getSize();
    player_amount = setup_dialog->getPlayers();
    unsigned int seed = setup_dialog->getSeed();

    std::shared_ptr<ObjectManager> new_manager(new ObjectManager);
    std::shared_ptr<GameEventHandler> new_handler(new GameEventHandler);
    object_manager = new_manager;
    event_handler = new_handler;

    m_ui->setupUi(this);
    m_gameview = std::shared_ptr<GameView>(new GameView(nullptr, event_handler, object_manager));
    m_ui->horizontalLayout_2->insertWidget(0, m_gameview.get());


    std::map<std::string, std::shared_ptr<Player>> new_players;

    unsigned int i = 1;
    while (i <= player_amount){
        std::string player_id = std::to_string(i);
        std::shared_ptr<Player> new_player(new Player(player_id));
        new_players[player_id] = new_player;
        i++;
    }

    players = new_players;

    MapGenerator& map_generator = MapGenerator::getInstance();

    map_generator.generateMap(map_size,map_size,seed, object_manager, event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = object_manager->getAllTiles();
    std::vector<std::shared_ptr<Course::GameObject>> objs(tiles.begin(), tiles.end());

    m_gameview->drawMultipleItems(objs);
    connect(m_ui->endTurnButton,SIGNAL(pressed()),this,SLOT(passTurn()));

    passTurn();

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

void MapWindow::updateStatusBar(std::shared_ptr<GameEventHandler> event_handler, std::map<std::string, std::shared_ptr<Player>> players, unsigned int current_player, unsigned int turn)
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

    QString buy_price_qstring = QString::number(-event_handler->getTrader().getBuyPrice(traded_resource));
    QString buy_text = QString("Buy 100 for %1 gold").arg(buy_price_qstring);
    m_ui->buyButton->setText(buy_text);

    QString sell_price_qstring = QString::number(event_handler->getTrader().getSellPrice(traded_resource));
    QString sell_text = QString("Sell 100 for %1 gold").arg(sell_price_qstring);
    m_ui->sellButton->setText(sell_text);

}

void MapWindow::passTurn()
{
    std::tuple<unsigned int, unsigned int> turn_data = event_handler->passTurn(player_amount);
    turn = std::get<0>(turn_data);
    current_player = std::get<1>(turn_data);

    if (turn == 1) // randomly place city for player
    {
        event_handler->setPresetResources(players[std::to_string(current_player)]);
        std::shared_ptr<City> new_city(new City(event_handler, object_manager,players[std::to_string(current_player)]));
        event_handler->firstTurn(map_size,object_manager,players, new_city);
    }

    players[std::to_string(current_player)]->generateResources(object_manager);
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_selectFoodButton_clicked()
{
    traded_resource = Course::BasicResource::FOOD;
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_selectWoodButton_clicked()
{
    traded_resource = Course::BasicResource::WOOD;
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_selectStoneButton_clicked()
{
    traded_resource = Course::BasicResource::STONE;
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_selectOreButton_clicked()
{
    traded_resource = Course::BasicResource::ORE;
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_buyButton_clicked()
{
    event_handler->resourceBought(players[std::to_string(current_player)], traded_resource);
    updateStatusBar(event_handler, players, current_player, turn);
}

void MapWindow::on_sellButton_clicked()
{
    event_handler->resourceSold(players[std::to_string(current_player)], traded_resource);
    updateStatusBar(event_handler, players, current_player, turn);
}
