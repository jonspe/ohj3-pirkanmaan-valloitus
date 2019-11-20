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

    connect(m_gameview.get(), &GameView::tilePressed, this, &MapWindow::tilePressed);

    std::map<std::string, std::shared_ptr<Player>> new_players;

    unsigned int i = 1;
    while (i <= player_amount){
        std::string player_id = std::to_string(i);
        std::shared_ptr<Player> new_player(new Player(player_id));
        new_players[player_id] = new_player;
        i++;
    }

    players = new_players;
    event_handler->setPlayers(players);

    std::vector<std::string> grass_buildings;
    grass_buildings.push_back("Colony");
    grass_buildings.push_back("Farm");
    grass_buildings.push_back("Marketplace");
    grass_buildings.push_back("University");
    grass_buildings.push_back("Victory Monument");
    std::vector<std::string> animals_buildings;
    animals_buildings.push_back("Farm");
    std::vector<std::string> forest_buildings;
    forest_buildings.push_back("Colony");
    forest_buildings.push_back("Lumber Camp");
    std::vector<std::string> stone_buildings;
    stone_buildings.push_back("Mine");
    std::vector<std::string> lake_buildings;

    allowed_buildings_on_tile["Grass"] = grass_buildings;
    allowed_buildings_on_tile["Animals"] = animals_buildings;
    allowed_buildings_on_tile["Birch"] = forest_buildings;
    allowed_buildings_on_tile["Evergreen"] = forest_buildings;
    allowed_buildings_on_tile["Stone"] = stone_buildings;
    allowed_buildings_on_tile["Diamond"] = stone_buildings;
    allowed_buildings_on_tile["Ore"] = stone_buildings;
    allowed_buildings_on_tile["Lake"] = lake_buildings;

    m_ui->buildMenu->setVisible(false);
    m_ui->buildingMenu->setVisible(false);
    m_ui->buildmenuLabel->setVisible(false);
    m_ui->buildingDescription->setVisible(false);
    m_ui->buildingSelectionBox->setVisible(false);
    m_ui->workerMenu->setVisible(false);
    m_ui->workermenuLabel->setVisible(false);

    MapGenerator& map_generator = MapGenerator::getInstance();

    map_generator.generateMap(map_size,map_size,seed, object_manager, event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = object_manager->getAllTiles();
    std::vector<std::shared_ptr<Course::GameObject>> objs(tiles.begin(), tiles.end());

    m_gameview->drawMultipleItems(objs);
    connect(m_ui->endTurnButton, SIGNAL(pressed()), this, SLOT(passTurn()));

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

    m_ui->gold_label->setText(QString::number(gold_count));
    m_ui->food_label->setText(QString::number(food_count));
    m_ui->wood_label->setText(QString::number(wood_count));
    m_ui->stone_label->setText(QString::number(stone_count));
    m_ui->ore_label->setText(QString::number(ore_count));

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
        event_handler->firstTurn(map_size,object_manager, new_city);
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

void MapWindow::tilePressed(std::shared_ptr<Course::TileBase> tile)
{
    qDebug() << QString::fromStdString(tile->getType())
             << "pressed at"
             << tile->getCoordinatePtr()->asQpoint();

    if(tile->getOwner() == players[std::to_string(current_player)])
       {
           m_ui->buildingSelectionBox->clear();
           m_ui->buildMenu->setVisible(true);
           m_ui->buildingMenu->setVisible(true);
           m_ui->buildmenuLabel->setVisible(true);
           m_ui->buildingDescription->setVisible(true);
           m_ui->buildingSelectionBox->setVisible(true);
           for (auto building_name : allowed_buildings_on_tile[tile->getType()])
           {
               m_ui->buildingSelectionBox->addItem(QString::fromStdString(building_name));
           }

       }else{
           m_ui->buildMenu->setVisible(false);
           m_ui->buildingMenu->setVisible(false);
           m_ui->buildmenuLabel->setVisible(false);
           m_ui->buildingDescription->setVisible(false);
           m_ui->buildingSelectionBox->setVisible(false);
       }

}
