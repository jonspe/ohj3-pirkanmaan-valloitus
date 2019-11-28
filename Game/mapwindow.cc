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
#include "Game/buildings/colony.h"
#include "Game/buildings/farm.h"
#include "Game/buildings/lumbercamp.h"
#include "Game/buildings/marketplace.h"
#include "Game/buildings/mine.h"
#include "Game/buildings/victorymonument.h"
#include "Game/buildings/university.h"
#include "Game/buildings/advancedfarm.h"
#include "Game/buildings/advancedmine.h"
#include "Game/buildings/advancedlumbercamp.h"
#include "Game/buildings/diamondmine.h"
#include "Game/buildings/oremine.h"
#include "Game/buildings/factory.h"
#include "Game/core/objectmanager.h"
#include "Game/core/player.h"
#include "Game/core/resources.h"
#include "Game/core/mapgenerator.h"
#include "Game/core/gameeventhandler.h"
#include "setupdialog.h"
#include "enddialog.h"
#include <math.h>
#include <QSound>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    tile_select_sound(":/sound/tile_select.wav", this),
    ui_click_sound(":/sound/ui_click.wav", this),
    end_turn_sound(":/sound/endturn.wav", this),
    trade_sound(":/sound/endturn.wav", this)
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
    grass_buildings.push_back("Advanced Farm");
    grass_buildings.push_back("Marketplace");
    grass_buildings.push_back("University");
    grass_buildings.push_back("Victory Monument");
    grass_buildings.push_back("Factory");
    std::vector<std::string> animals_buildings;
    animals_buildings.push_back("Farm");
    animals_buildings.push_back("Advanced Farm");
    std::vector<std::string> forest_buildings;
    forest_buildings.push_back("Colony");
    forest_buildings.push_back("Lumber Camp");
    forest_buildings.push_back("Advanced Lumber Camp");
    std::vector<std::string> stone_buildings;
    stone_buildings.push_back("Mine");
    stone_buildings.push_back("Advanced Mine");
    std::vector<std::string> diamond_buildings;
    diamond_buildings.push_back("Diamond Mine");
    std::vector<std::string> ore_buildings;
    ore_buildings.push_back("Ore Mine");
    std::vector<std::string> lake_buildings;

    allowed_buildings_on_tile["Grass"] = grass_buildings;
    allowed_buildings_on_tile["Animals"] = animals_buildings;
    allowed_buildings_on_tile["Birch"] = forest_buildings;
    allowed_buildings_on_tile["Evergreen"] = forest_buildings;
    allowed_buildings_on_tile["Stone"] = stone_buildings;
    allowed_buildings_on_tile["Diamond"] = diamond_buildings;
    allowed_buildings_on_tile["Ore"] = ore_buildings;
    allowed_buildings_on_tile["Lake"] = lake_buildings;

    build_costs["Colony"] = ConstResources::COLONY_BUILD_COST;
    build_costs["Farm"] = ConstResources::FARM_BUILD_COST;
    build_costs["Lumber Camp"] = ConstResources::LUMBERCAMP_BUILD_COST;
    build_costs["Marketplace"] = ConstResources::MARKETPLACE_BUILD_COST;
    build_costs["Mine"] = ConstResources::MINE_BUILD_COST;
    build_costs["University"] = ConstResources::UNIVERSITY_BUILD_COST;
    build_costs["Victory Monument"] = ConstResources::VICTORYMONUMENT_BUILD_COST;
    build_costs["Advanced Mine"] = ConstResources::A_MINE_BUILD_COST;
    build_costs["Advanced Farm"] = ConstResources::A_FARM_BUILD_COST;
    build_costs["Advanced Lumber Camp"] = ConstResources::A_LUMBERCAMP_BUILD_COST;
    build_costs["Diamond Mine"] = ConstResources::D_MINE_BUILD_COST;
    build_costs["Ore Mine"] = ConstResources::ORE_MINE_BUILD_COST;
    build_costs["Factory"] = ConstResources::FACTORY_BUILD_COST;
    build_costs["Citizen"] = ConstResources::CITIZEN_RECRUITMENT_COST;
    build_costs["Educated Citizen"] = ConstResources::EDUCATEDCITIZEN_RECRUITMENT_COST;

    m_ui->buildMenu->setVisible(false);
    m_ui->buildingMenu->setVisible(false);
    m_ui->buildmenuLabel->setVisible(false);
    m_ui->buildingDescription->setVisible(false);
    m_ui->buildingSelectionBox->setVisible(false);
    m_ui->workerMenu->setVisible(false);
    m_ui->workermenuLabel->setVisible(false);
    m_ui->tileName->setVisible(false);
    m_ui->marketplaceMenu->setVisible(false);
    m_ui->tileDescription->setVisible(false);

    MapGenerator& map_generator = MapGenerator::getInstance();

    map_generator.generateMap(map_size,map_size,seed, object_manager, event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = object_manager->getAllTiles();

    for (auto tile: tiles)
        m_gameview->addTile(tile);

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

void MapWindow::updateStatusBar()
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
    end_turn_sound.play();

    std::tuple<unsigned int, unsigned int> turn_data = event_handler->passTurn(player_amount);
    turn = std::get<0>(turn_data);
    current_player = std::get<1>(turn_data);

    if (turn == 1) // randomly place city for player
    {
        event_handler->setPresetResources(players[std::to_string(current_player)]);
        std::shared_ptr<City> new_city(new City(event_handler, object_manager,players[std::to_string(current_player)]));
        event_handler->firstTurn(map_size,object_manager, new_city);
    }

    if (turn != 1)
    {
        players[std::to_string(current_player)]->generateResources(object_manager);
    }

    m_ui->buildButton->setText(QString("Build"));
    updateStatusBar();
}

void MapWindow::on_selectFoodButton_clicked()
{
    traded_resource = Course::BasicResource::FOOD;
    ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectWoodButton_clicked()
{
    traded_resource = Course::BasicResource::WOOD;
    ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectStoneButton_clicked()
{
    traded_resource = Course::BasicResource::STONE;
    ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectOreButton_clicked()
{
    traded_resource = Course::BasicResource::ORE;
    ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_buyButton_clicked()
{
    event_handler->resourceBought(players[std::to_string(current_player)], traded_resource);
    trade_sound.play();
    updateStatusBar();
}

void MapWindow::on_sellButton_clicked()
{
    event_handler->resourceSold(players[std::to_string(current_player)], traded_resource);
    trade_sound.play();
    updateStatusBar();
}

void MapWindow::tilePressed(std::shared_ptr<Course::TileBase> tile)
{
    qDebug() << QString::fromStdString(tile->getType())
             << "pressed at"
             << tile->getCoordinatePtr()->asQpoint();

    selected_tile = tile;

    tile_select_sound.play();

    m_ui->tileName->setText(QString::fromStdString(tile->getType()));
    m_ui->tileName->setVisible(true);
    m_ui->tileDescription->setText(QString::fromStdString((tile->getDescription(tile->getType()))));
    m_ui->marketplaceMenu->setVisible(false);
    m_ui->workerMenu->setVisible(false);
    m_ui->workermenuLabel->setVisible(false);
    m_ui->tileDescription->setVisible(true);
    m_ui->demolishButton->setVisible(false);
    m_ui->demolishButton->setText(QString::fromStdString("Demolish"));

    if(placing_worker && tile->getOwner() == players[std::to_string(current_player)] && tile->hasSpaceForWorkers(1))
    {
        event_handler->addWorker(tile->getCoordinate(), object_manager);
        placing_worker = false;
    }

    if(tile->getOwner() == players[std::to_string(current_player)] && tile->hasSpaceForBuildings(1))
       {

           m_ui->buildingSelectionBox->clear();
           m_ui->buildMenu->setVisible(true);
           m_ui->buildmenuLabel->setVisible(true);
           m_ui->buildingDescription->setVisible(true);
           m_ui->buildingSelectionBox->setVisible(true);
           for (auto building_name : allowed_buildings_on_tile[tile->getType()])
           {
               m_ui->buildingSelectionBox->addItem(QString::fromStdString(building_name));
           }

       }else{
           m_ui->buildMenu->setVisible(false);
           m_ui->buildmenuLabel->setVisible(false);
           m_ui->buildingDescription->setVisible(false);
           m_ui->buildingSelectionBox->setVisible(false);
       }

    if(tile->getBuildings().size() == 1 )
    {
        for( auto building : tile->getBuildings())
        {
            m_ui->buildingMenu->setVisible(true);
            m_ui->buildingName->setText(QString::fromStdString(building->getType()));
            m_ui->buildingDescription->setVisible(true);
            m_ui->buildingDescription->setText(QString::fromStdString(building->getDescription(building->getType())));
            if (building->getType() == "Marketplace")
            {
                m_ui->marketplaceMenu->setVisible(true);
            }
            else if (building->getType() == "Victory Monument")
            {
               m_ui->demolishButton->setText(QString::fromStdString("End the game"));
            }

            else if((building->getType() == "City" or building->getType() == "University")
                    && building->getOwner() == players[std::to_string(current_player)])
            {
                m_ui->workerMenu->setVisible(true);
                m_ui->workerMenu->setVisible(true);
                Course::ResourceMap worker_build_cost;

                if(building->getType() == "City"){
                    m_ui->trainButton->setText(QString::fromStdString("Train a Citizen"));
                    worker_build_cost = build_costs["Citizen"];
                    current_worker_selection = "Citizen";


                }
                else if (building->getType() == "University"){
                    m_ui->trainButton->setText(QString::fromStdString("Train an Educated Citizen"));
                    worker_build_cost = build_costs["Educated Citizen"];
                    current_worker_selection = "Educated Citizen";

                }

                if(worker_build_cost.count(Course::BasicResource::MONEY))
                {
                     m_ui->goldValue_2->setText(QString::number(-worker_build_cost.at(Course::BasicResource::MONEY)));
                     m_ui->goldIcon_2->setVisible(true);
                     m_ui->goldValue_2->setVisible(true);
                }else
                {
                    m_ui->goldIcon_2->setVisible(false);
                    m_ui->goldValue_2->setVisible(false);
                }
                if(worker_build_cost.count(Course::BasicResource::FOOD))
                {
                     m_ui->foodValue_2->setText(QString::number(-worker_build_cost.at(Course::BasicResource::FOOD)));
                     m_ui->foodIcon_2->setVisible(true);
                     m_ui->foodValue_2->setVisible(true);
                }else
                {
                    m_ui->foodIcon_2->setVisible(false);
                    m_ui->foodValue_2->setVisible(false);
                }
                if(worker_build_cost.count(Course::BasicResource::WOOD))
                {
                    m_ui->woodValue_2->setText(QString::number(-worker_build_cost.at(Course::BasicResource::WOOD)));
                    m_ui->woodIcon_2->setVisible(true);
                    m_ui->woodValue_2->setVisible(true);
                }else
                {
                    m_ui->woodIcon_2->setVisible(false);
                    m_ui->woodValue_2->setVisible(false);
                }
                if(worker_build_cost.count(Course::BasicResource::STONE))
                {
                    m_ui->stoneValue_2->setText(QString::number(-worker_build_cost.at(Course::BasicResource::STONE)));
                    m_ui->stoneIcon_2->setVisible(true);
                    m_ui->stoneValue_2->setVisible(true);
                }else
                {
                    m_ui->stoneIcon_2->setVisible(false);
                    m_ui->stoneValue_2->setVisible(false);
                }
                if(worker_build_cost.count(Course::BasicResource::ORE))
                {
                    m_ui->oreValue_2->setText(QString::number(-worker_build_cost.at(Course::BasicResource::ORE)));
                    m_ui->oreIcon_2->setVisible(true);
                    m_ui->oreValue_2->setVisible(true);
                }else
                {
                    m_ui->oreIcon_2->setVisible(false);
                    m_ui->oreValue_2->setVisible(false);
                }
            }

            if (building->getOwner() == players[std::to_string(current_player)]
                    && building->getType() != "City" && building->getType() != "Colony")
            {
                m_ui->demolishButton->setVisible(true);
            }
        }
    }else{
        m_ui->buildingMenu->setVisible(false);
    }
}



void MapWindow::on_buildButton_clicked()
{
    ui_click_sound.play();

    if (selected_tile->hasSpaceForBuildings(1)) {

        std::string building_type = (m_ui->buildingSelectionBox->currentText()).toStdString();
        bool building_successful = false;

        // Could be optimized by mapping building type string to constructor
        // deadline near though so

        if (building_type == "Colony")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Colony"])){
                std::shared_ptr<Colony> building(new Colony(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                m_ui->buildButton->setText(QString("Not enough resources!"));
            }

        }
        else if (building_type == "Farm")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Farm"])){
                std::shared_ptr<Farm> building(new Farm(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }
        else if (building_type == "Lumber Camp")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Lumber Camp"])){
                std::shared_ptr<LumberCamp> building(new LumberCamp(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }
        else if (building_type == "Marketplace")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Marketplace"])){
                std::shared_ptr<Marketplace> building(new Marketplace(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }
        else if (building_type == "Mine")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Mine"])){
                std::shared_ptr<Mine> building(new Mine(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }
        else if (building_type == "University")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["University"])){
                std::shared_ptr<University> building(new University(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }
        else if (building_type == "Victory Monument")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Victory Monument"])){
                std::shared_ptr<VictoryMonument> building(new VictoryMonument(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Advanced Mine")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Advanced Mine"])){
                std::shared_ptr<AdvancedMine> building(new AdvancedMine(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Advanced Farm")
        {
            if(event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Advanced Farm"])){
                std::shared_ptr<AdvancedFarm> building(new AdvancedFarm(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Advanced Lumber Camp")
        {
            if(event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Advanced Lumber Camp"])){
                std::shared_ptr<AdvancedLumberCamp> building(new AdvancedLumberCamp(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Diamond Mine")
        {
            if(event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Diamond Mine"])){
                std::shared_ptr<DiamondMine> building(new DiamondMine(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Ore Mine")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Ore Mine"])){
                std::shared_ptr<OreMine> building(new OreMine(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        else if (building_type == "Factory")
        {
            if (event_handler->modifyResources(players[std::to_string(current_player)], build_costs["Factory"])){
                std::shared_ptr<Factory> building(new Factory(event_handler, object_manager,players[std::to_string(current_player)]));
                event_handler->addBuilding(selected_tile->getCoordinate(), object_manager, building);
                building_successful = true;
            }else{
                    m_ui->buildButton->setText(QString("Not enough resources!"));
            }
        }

        if(building_successful)
        {
            m_ui->buildMenu->setVisible(false);
            m_ui->buildmenuLabel->setVisible(false);
            m_ui->buildingDescription->setVisible(false);
            m_ui->buildingSelectionBox->setVisible(false);

            tilePressed(selected_tile); // update tile status
            updateStatusBar();
        }

        m_gameview->update();
    }
}

void MapWindow::on_buildingSelectionBox_currentTextChanged(const QString &arg1)
{
    std::string building_type = (arg1).toStdString();

    m_ui->buildButton->setText(QString("Build"));

    if(build_costs.count(building_type))
    {

        Course::ResourceMap build_cost = build_costs[building_type];
        if(build_cost.count(Course::BasicResource::MONEY))
        {
            m_ui->goldValue->setText(QString::number(-build_cost.at(Course::BasicResource::MONEY)));
            m_ui->goldIcon->setVisible(true);
            m_ui->goldValue->setVisible(true);
        }else
        {
            m_ui->oreIcon->setVisible(false);
            m_ui->oreValue->setVisible(false);
        }
        if(build_cost.count(Course::BasicResource::FOOD))
        {
             m_ui->foodValue->setText(QString::number(-build_cost.at(Course::BasicResource::FOOD)));
             m_ui->foodIcon->setVisible(true);
             m_ui->foodValue->setVisible(true);
        }else
        {
           m_ui->foodIcon->setVisible(false);
           m_ui->foodValue->setVisible(false);
        }
        if(build_cost.count(Course::BasicResource::WOOD))
        {
            m_ui->woodValue->setText(QString::number(-build_cost.at(Course::BasicResource::WOOD)));
            m_ui->woodIcon->setVisible(true);
            m_ui->woodValue->setVisible(true);
        }else
        {
            m_ui->woodIcon->setVisible(false);
            m_ui->woodValue->setVisible(false);
        }
        if(build_cost.count(Course::BasicResource::STONE))
        {
            m_ui->stoneValue->setText(QString::number(-build_cost.at(Course::BasicResource::STONE)));
            m_ui->stoneIcon->setVisible(true);
            m_ui->stoneValue->setVisible(true);
        }else
        {
            m_ui->stoneIcon->setVisible(false);
            m_ui->stoneValue->setVisible(false);
        }
        if(build_cost.count(Course::BasicResource::ORE))
        {
            m_ui->oreValue->setText(QString::number(-build_cost.at(Course::BasicResource::ORE)));
            m_ui->oreIcon->setVisible(true);
            m_ui->oreValue->setVisible(true);
        }else
        {
            m_ui->oreIcon->setVisible(false);
            m_ui->oreValue->setVisible(false);
        }

    }

}

void MapWindow::on_demolishButton_clicked()
{
    ui_click_sound.play();

    auto building_vector = selected_tile->getBuildings();
    for(auto building : building_vector)
    {
        if (building->getType() == "Victory Monument") // victory monument has a win button instead of demolish
        {
           std::tuple<unsigned int, unsigned int> winner_data = event_handler->getWinnerData();

           unsigned int winner = std::get<1>(winner_data);
           unsigned int winning_turn = std::get<0>(winner_data);

           EndDialog* end_dialog(new EndDialog(nullptr, winner, winning_turn));
           end_dialog->exec();

           this->close();

        }
        else
        {
            selected_tile->removeBuilding(building);
            tilePressed(selected_tile);
        }

    }

    tilePressed(selected_tile);
    m_gameview->update();
}

void MapWindow::on_trainButton_clicked()
{
    ui_click_sound.play();

    if (placing_worker == false)
    {
        if(event_handler->modifyResources(players[std::to_string(current_player)], build_costs[current_worker_selection])
                && selected_tile->getOwner() == players[std::to_string(current_player)])
        {
            auto building_vector = selected_tile->getBuildings();
            for(auto building : building_vector)
            {
                building->doSpecialAction();
                placing_worker = true;
                m_ui->trainButton->setText(QString("Select a tile to place the worker"));
            }

        }else{
            m_ui->trainButton->setText(QString("Not enough resources!"));
        }

        updateStatusBar();
    }

}


