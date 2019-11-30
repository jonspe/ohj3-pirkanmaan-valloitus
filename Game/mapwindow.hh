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

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr,
                       std::shared_ptr<Course::iGameEventHandler> GEHandler = {}
                       );
    ~MapWindow();

    void setGEHandler(std::shared_ptr<Course::iGameEventHandler> nHandler);
    void setSize(int width, int height);
    void setScale(int scale);

    /** @brief updates UI widgets such as resource values and icons
     */
    void updateStatusBar();


private slots:
    void passTurn();

    void on_selectFoodButton_clicked();
    void on_selectWoodButton_clicked();
    void on_selectStoneButton_clicked();
    void on_selectOreButton_clicked();
    void on_buyButton_clicked();
    void on_sellButton_clicked();

    void tilePressed(std::shared_ptr<Course::TileBase> tile);

    void on_buildButton_clicked();

    void on_buildingSelectionBox_currentTextChanged(const QString &arg1);

    void on_demolishButton_clicked();

    void on_trainButton_clicked();

private:
    /**
     * @brief highlightPlayerTiles
     * @param player
     * @param highlight
     */
    void highlightPlayerTiles(std::shared_ptr<Player> player, bool highlight);

    Ui::MapWindow* m_ui;

    std::shared_ptr<Course::iGameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<GameView> m_gameview = nullptr;
    std::shared_ptr<ObjectManager> object_manager;
    std::shared_ptr<GameEventHandler> event_handler;
    std::map<std::string, std::shared_ptr<Player>> players;

    unsigned int map_size;
    unsigned int player_amount;
    unsigned int current_player;
    unsigned int turn;

    Course::BasicResource traded_resource = Course::BasicResource::FOOD;

    std::map<std::string, std::vector<std::string>> allowed_buildings_on_tile;
    std::map<std::string, Course::ResourceMap> build_costs;

    std::shared_ptr<Course::TileBase> selected_tile = nullptr;

    std::string current_worker_selection = "Citizen";

    bool placing_worker = false;


    QSound tile_select_sound;
    QSound ui_click_sound;
    QSound end_turn_sound;
    QSound trade_sound;

};

#endif // MapWINDOW_HH

