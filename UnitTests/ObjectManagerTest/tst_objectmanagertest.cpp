#include "core\coordinate.h"
#include "tiles\tilebase.h"
#include "Game\core\objectmanager.h"
#include "Game\core\gameeventhandler.h"

#include <QtTest>
#include <vector>

class ObjectManagerTest : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTest();
    ~ObjectManagerTest();

private slots:
    void TilesTest();
};

ObjectManagerTest::ObjectManagerTest() {}
ObjectManagerTest::~ObjectManagerTest() {}

void ObjectManagerTest::TilesTest()
{
    std::shared_ptr<ObjectManager> object_manager(new ObjectManager);
    std::shared_ptr<GameEventHandler> event_handler(new GameEventHandler);

    Course::Coordinate first_tile_coordinate(1, 1);
    Course::Coordinate second_tile_coordinate(1, 1);

    std::vector<Course::Coordinate> tile_coordinates;
    tile_coordinates.push_back(first_tile_coordinate);
    tile_coordinates.push_back(second_tile_coordinate);

    std::shared_ptr<Course::TileBase> first_tile(new Course::TileBase(first_tile_coordinate, event_handler, object_manager));
    std::shared_ptr<Course::TileBase> second_tile(new Course::TileBase(second_tile_coordinate, event_handler, object_manager));

    Course::ObjectId first_tile_id = first_tile->ID;

    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(first_tile);
    tiles.push_back(second_tile);

    QCOMPARE(object_manager->getTile(first_tile_coordinate), first_tile);
    QCOMPARE(object_manager->getTile(first_tile_id), first_tile);
    QCOMPARE(object_manager->getTiles(tile_coordinates), tiles);
}

QTEST_APPLESS_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
