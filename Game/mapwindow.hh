#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QSound>

#include <map>

#include "interfaces/igameeventhandler.h"
#include "Game/graphics/gameview.h"
#include "Game/core/gameeventhandler.h"


namespace Ui {
class MapWindow;
}

/**
 * @brief The class that does most of the heavy lifting in the game,
 * handling game logic and UI manipulation.
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow();

    /**
     * @brief updates UI widgets such as resource values and icons
     */
    void updateStatusBar();

private slots:
    /**
     * @brief gives the turn to next player, generates resources etc.
     * if all players did their turn, increase turn counter and return to player1.
     */
    void passTurn();

    void on_selectFoodButton_clicked();
    void on_selectWoodButton_clicked();
    void on_selectStoneButton_clicked();
    void on_selectOreButton_clicked();
    void on_buyButton_clicked();
    void on_sellButton_clicked();

    /**
     * @brief handler for when a tile is pressed
     * @param tile
     */
    void tilePressed(std::shared_ptr<Course::TileBase> tile);

    void on_buildButton_clicked();
    void on_buildingSelectionBox_currentTextChanged(const QString &arg1);
    void on_demolishButton_clicked();
    void on_trainButton_clicked();

private:
    /**
     * @brief highlights all the tiles that a player has claimed
     * @param player
     * @param highlight
     */
    void highlightPlayerTiles(std::shared_ptr<Player> player, bool highlight);

    Ui::MapWindow* m_ui;

    std::shared_ptr<GameView> m_gameview = nullptr;
    std::shared_ptr<ObjectManager> m_object_manager;
    std::shared_ptr<GameEventHandler> m_event_handler;
    std::map<std::string, std::shared_ptr<Player>> m_players;

    unsigned int m_map_size;
    unsigned int m_player_amount;
    unsigned int m_current_player;
    unsigned int m_turn;

    Course::BasicResource m_traded_resource = Course::BasicResource::FOOD;

    std::map<std::string, std::vector<std::string>> m_allowed_buildings_on_tile;
    std::map<std::string, Course::ResourceMap> m_build_costs;

    std::shared_ptr<Course::TileBase> m_selected_tile = nullptr;

    std::string m_current_worker_selection = "Citizen";

    bool m_placing_worker = false;

    QSound m_tile_select_sound;
    QSound m_ui_click_sound;
    QSound m_end_turn_sound;
    QSound m_trade_sound;
};

#endif // MapWINDOW_HH

