#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

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

    void updateStatusBar(std::shared_ptr<GameEventHandler> event_handler, std::map<std::string, std::shared_ptr<Player>> players, unsigned int current_player, unsigned int turn);

    void playSelectionSound();


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
    Ui::MapWindow* m_ui;
    std::shared_ptr<Course::iGameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<GameView> m_gameview = nullptr;
    std::shared_ptr<ObjectManager> object_manager;
    std::shared_ptr<GameEventHandler> event_handler;
    unsigned int map_size;
    unsigned int player_amount;
    std::map<std::string, std::shared_ptr<Player>> players;
    unsigned int current_player;
    unsigned int turn;
    Course::BasicResource traded_resource = Course::BasicResource::FOOD;

    std::map<std::string, std::vector<std::string>> allowed_buildings_on_tile;
    std::shared_ptr<Course::TileBase> selected_tile = nullptr;

    std::map<std::string, Course::ResourceMap> build_costs;
    std::string current_worker_selection = "Citizen";
    std::map<std::string, std::string> selection_sounds;

    bool placing_worker = false;
};

#endif // MapWINDOW_HH

