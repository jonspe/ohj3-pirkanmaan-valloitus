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
#include "Game/core/objectmappings.h"
#include "setupdialog.h"
#include "enddialog.h"

#include <math.h>
#include <QSound>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_current_player(1),
    m_selected_tile(nullptr),
    m_tile_select_sound(":/sound/tile_select.wav", this),
    m_ui_click_sound(":/sound/ui_click.wav", this),
    m_end_turn_sound(":/sound/endturn.wav", this),
    m_trade_sound(":/sound/endturn.wav", this)
{
    SetupDialog* setup_dialog = new SetupDialog();
    setup_dialog->exec();

    m_map_size = setup_dialog->getSize();
    m_player_amount = setup_dialog->getPlayers();
    unsigned int seed = setup_dialog->getSeed();

    std::shared_ptr<ObjectManager> new_manager(new ObjectManager);
    std::shared_ptr<GameEventHandler> new_handler(new GameEventHandler);
    m_object_manager = new_manager;
    m_event_handler = new_handler;

    m_ui->setupUi(this);
    m_gameview = std::shared_ptr<GameView>(new GameView(m_object_manager, m_event_handler));
    m_ui->horizontalLayout_2->insertWidget(0, m_gameview.get());

    connect(m_gameview.get(), &GameView::tilePressed, this, &MapWindow::tilePressed);

    std::map<std::string, std::shared_ptr<Player>> new_players;

    unsigned int i = 1;
    while (i <= m_player_amount){
        std::string player_id = std::to_string(i);
        std::shared_ptr<Player> new_player(new Player(player_id));
        new_players[player_id] = new_player;
        i++;
    }

    m_players = new_players;
    m_event_handler->setPlayers(m_players);

    m_ui->buildMenu->setVisible(false);
    m_ui->buildingMenu->setVisible(false);
    m_ui->workerMenu->setVisible(false);
    m_ui->workermenuLabel->setVisible(false);
    m_ui->marketplaceMenu->setVisible(false);

    MapGenerator& map_generator = MapGenerator::getInstance();

    map_generator.generateMap(
                static_cast<int>(m_map_size),
                static_cast<int>(m_map_size),
                seed,
                m_object_manager,
                m_event_handler);

    std::vector<std::shared_ptr<Course::TileBase>> tiles = m_object_manager->getAllTiles();

    for (auto tile: tiles)
        m_gameview->addTile(tile);

    connect(m_ui->endTurnButton, SIGNAL(pressed()), this, SLOT(passTurn()));

    passTurn();
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::updateStatusBar()
{

    QString player_number_qstring =  QString::number(m_current_player);
    QString player_text = QString("Player %1").arg(player_number_qstring);
    m_ui->player_label->setText(player_text);

    QString turn_number_qstring =  QString::number(m_turn);
    QString turn_text = QString("Turn %1").arg(turn_number_qstring);
    m_ui->turn_label->setText(turn_text);

    Course::ResourceMap resource_stockpile = m_event_handler->getResources(m_players[std::to_string(m_current_player)]);

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

    QString buy_price_qstring = QString::number(-m_event_handler->getTrader().getBuyPrice(m_traded_resource));
    QString buy_text = QString("Buy 100 for %1 gold").arg(buy_price_qstring);
    m_ui->buyButton->setText(buy_text);

    QString sell_price_qstring = QString::number(m_event_handler->getTrader().getSellPrice(m_traded_resource));
    QString sell_text = QString("Sell 100 for %1 gold").arg(sell_price_qstring);
    m_ui->sellButton->setText(sell_text);

}


void MapWindow::passTurn()
{
    m_end_turn_sound.play();

    std::shared_ptr<Player> previous_player = m_players.at(std::to_string(m_current_player));
    highlightPlayerTiles(previous_player, false);

    std::tuple<unsigned int, unsigned int> turn_data = m_event_handler->passTurn(m_player_amount);
    m_turn = std::get<0>(turn_data);
    m_current_player = std::get<1>(turn_data);

    std::shared_ptr<Player> player = m_players.at(std::to_string(m_current_player));

    if (m_turn == 1) // randomly place city for player
    {
        m_event_handler->setPresetResources(player);
        std::shared_ptr<City> new_city(new City(m_event_handler, m_object_manager, player));
        m_event_handler->firstTurn(m_map_size,m_object_manager, new_city);
    }

    if (m_turn != 1)
    {
        player->generateResources(m_object_manager);
    }

    highlightPlayerTiles(player, true);

    m_ui->buildButton->setText(QString("Build"));
    updateStatusBar();

    if (m_selected_tile != nullptr)
    {
        tilePressed(m_selected_tile);
    }
}

void MapWindow::on_selectFoodButton_clicked()
{
    m_traded_resource = Course::BasicResource::FOOD;
    m_ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectWoodButton_clicked()
{
    m_traded_resource = Course::BasicResource::WOOD;
    m_ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectStoneButton_clicked()
{
    m_traded_resource = Course::BasicResource::STONE;
    m_ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_selectOreButton_clicked()
{
    m_traded_resource = Course::BasicResource::ORE;
    m_ui_click_sound.play();
    updateStatusBar();
}

void MapWindow::on_buyButton_clicked()
{
    m_event_handler->resourceBought(m_players[std::to_string(m_current_player)], m_traded_resource);
    m_trade_sound.play();
    updateStatusBar();
}

void MapWindow::on_sellButton_clicked()
{
    m_event_handler->resourceSold(m_players[std::to_string(m_current_player)], m_traded_resource);
    m_trade_sound.play();
    updateStatusBar();
}

void MapWindow::tilePressed(std::shared_ptr<Course::TileBase> tile)
{
    qDebug() << QString::fromStdString(tile->getType())
             << "pressed at"
             << tile->getCoordinatePtr()->asQpoint();

    m_selected_tile = tile;

    m_tile_select_sound.play();

    m_ui->tileName->setText(QString::fromStdString(tile->getDescription("Name")));
    m_ui->tileDescription->setText(QString::fromStdString(tile->getDescription("Description")));
    m_ui->marketplaceMenu->setVisible(false);
    m_ui->workerMenu->setVisible(false);
    m_ui->demolishButton->setVisible(false);
    m_ui->demolishButton->setText(QString::fromStdString("Demolish"));

    if(m_placing_worker && tile->getOwner() == m_players[std::to_string(m_current_player)] && tile->hasSpaceForWorkers(1))
    {
        m_event_handler->addWorker(tile->getCoordinate(), m_object_manager);
        m_placing_worker = false;
    }

    if(tile->getOwner() == m_players.at(std::to_string(m_current_player)) && tile->hasSpaceForBuildings(1))
    {
       m_ui->buildingSelectionBox->clear();
       m_ui->buildMenu->setVisible(true);

       for (auto building_name : TILE_BUILDING_MAP.at(tile->getType()))
       {
           m_ui->buildingSelectionBox->addItem(QString::fromStdString(building_name));
       }

   }else{
       m_ui->buildMenu->setVisible(false);
   }

    if(tile->getBuildings().size() == 1 )
    {
        for( auto building : tile->getBuildings())
        {
            m_ui->buildingMenu->setVisible(true);
            m_ui->buildingName->setText(QString::fromStdString(building->getDescription("Name")));
            m_ui->buildingDescription->setText(QString::fromStdString(building->getDescription("Description")));

            if (building->getType() == "Marketplace" && tile->getOwner() == m_players[std::to_string(m_current_player)])
            {
                m_ui->marketplaceMenu->setVisible(true);
            }
            else if (building->getType() == "Victory Monument")
            {
               m_ui->demolishButton->setText(QString::fromStdString("End the game"));
            }

            else if((building->getType() == "City" or building->getType() == "University")
                    && building->getOwner() == m_players[std::to_string(m_current_player)])
            {
                m_ui->workerMenu->setVisible(true);
                Course::ResourceMap worker_build_cost;

                if(building->getType() == "City"){
                    m_ui->trainButton->setText(QString::fromStdString("Train a Citizen"));
                    worker_build_cost = BUILD_COSTS.at("Citizen");
                    m_current_worker_selection = "Citizen";
                }
                else if (building->getType() == "University"){
                    m_ui->trainButton->setText(QString::fromStdString("Train an Educated Citizen"));
                    worker_build_cost = BUILD_COSTS.at("Educated Citizen");
                    m_current_worker_selection = "Educated Citizen";
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

            if (building->getOwner() == m_players[std::to_string(m_current_player)]
                    && building->getType() != "City" && building->getType() != "Colony")
            {
                m_ui->demolishButton->setVisible(true);
            }
        }
    }else{
        m_ui->buildingMenu->setVisible(false);
    }

    m_gameview->refresh();
}



void MapWindow::on_buildButton_clicked()
{
    m_ui_click_sound.play();

    if (m_selected_tile->hasSpaceForBuildings(1)) {

        std::string building_type = (m_ui->buildingSelectionBox->currentText()).toStdString();
        bool building_successful = false;

        std::shared_ptr<Player> player = m_players[std::to_string(m_current_player)];

        if (m_event_handler->modifyResources(player, BUILD_COSTS.at(building_type))){
            auto building = BUILDING_CTOR_MAP.at(building_type)(m_event_handler, m_object_manager, player);
            m_event_handler->addBuilding(m_selected_tile->getCoordinate(), m_object_manager, building);
            building_successful = true;
        }else{
            m_ui->buildButton->setText(QString("Not enough resources!"));
        }

        if(building_successful)
        {
            m_ui->buildMenu->setVisible(false);

            highlightPlayerTiles(player, true);

            tilePressed(m_selected_tile); // update tile status
            updateStatusBar();
        }

        m_gameview->refresh();
    }
}

void MapWindow::on_buildingSelectionBox_currentTextChanged(const QString &arg1)
{
    std::string building_type = (arg1).toStdString();

    m_ui->buildButton->setText(QString("Build"));

    if(BUILD_COSTS.count(building_type))
    {

        Course::ResourceMap build_cost = BUILD_COSTS.at(building_type);
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
    m_ui_click_sound.play();

    auto building_vector = m_selected_tile->getBuildings();
    for(auto building : building_vector)
    {
        if (building->getType() == "Victory Monument") // victory monument has a win button instead of demolish
        {
           std::tuple<unsigned int, unsigned int> winner_data = m_event_handler->getWinnerData();

           unsigned int winner = std::get<1>(winner_data);
           unsigned int winning_turn = std::get<0>(winner_data);

           EndDialog* end_dialog(new EndDialog(winner, winning_turn));
           end_dialog->exec();

           this->close();
        }
        else
        {
            m_selected_tile->removeBuilding(building);
            tilePressed(m_selected_tile);
        }
    }

    tilePressed(m_selected_tile);
    m_gameview->refresh();
}

void MapWindow::on_trainButton_clicked()
{
    m_ui_click_sound.play();

    if (m_placing_worker == false)
    {
        if(m_event_handler->modifyResources(m_players[std::to_string(m_current_player)], BUILD_COSTS.at(m_current_worker_selection))
                && m_selected_tile->getOwner() == m_players[std::to_string(m_current_player)])
        {
            auto building_vector = m_selected_tile->getBuildings();
            for(auto building : building_vector)
            {
                building->doSpecialAction();
                m_placing_worker = true;
                m_ui->trainButton->setText(QString("Select a tile to place the worker"));
            }

        }else{
            m_ui->trainButton->setText(QString("Not enough resources!"));
        }

        updateStatusBar();
    }
}

void MapWindow::highlightPlayerTiles(std::shared_ptr<Player> player, bool highlight)
{
    for (std::shared_ptr<Course::GameObject> obj: player->getObjects())
    {
        auto elevTile = std::dynamic_pointer_cast<ElevatedTileBase>(obj);
        if (elevTile != nullptr)
        {
            m_gameview->selectTile(elevTile, highlight);
        }
    }
}


