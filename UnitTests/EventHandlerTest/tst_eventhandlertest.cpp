#include <QtTest>
#include "Game/core/gameeventhandler.h"

class EventHandlerTest : public QObject
{
    Q_OBJECT

public:
    EventHandlerTest();
    ~EventHandlerTest();

private slots:
    void modifyResources_test();
    void modifyResource_test();

};

EventHandlerTest::EventHandlerTest()
{

}

EventHandlerTest::~EventHandlerTest()
{

}

void EventHandlerTest::modifyResources_test()
{
   std::shared_ptr<GameEventHandler> event_handler(new GameEventHandler);

   std::shared_ptr<Player> new_player(new Player("1"));

   event_handler->setPresetResources(new_player);

   Course::ResourceMap resource_plus = {
       {Course::BasicResource::MONEY, 100},
       {Course::BasicResource::FOOD, 100},
       {Course::BasicResource::WOOD, 100},
       {Course::BasicResource::STONE, 100},
       {Course::BasicResource::ORE, 1000}

   };


   Course::ResourceMap resource_minus = {
       {Course::BasicResource::MONEY, -50},
       {Course::BasicResource::FOOD, -50},
       {Course::BasicResource::WOOD, -50},
       {Course::BasicResource::STONE, -50}

   };

   Course::ResourceMap resource_minus_big = {
       {Course::BasicResource::MONEY, -5000},
       {Course::BasicResource::FOOD, -5000},
       {Course::BasicResource::WOOD, -5000},
       {Course::BasicResource::STONE, -5000},
       {Course::BasicResource::ORE, -5000}

   };


   QVERIFY2(event_handler->modifyResources(new_player, resource_plus) == true, "Resource addition unsuccessful in modifyResources");
   QVERIFY2(event_handler->modifyResources(new_player, resource_minus) == true, "Resource subtraction unsuccessful in modifyResources");
   QVERIFY2(event_handler->modifyResources(new_player, resource_minus_big) == false, "Negative player resources detected in modifyResources");
}

void EventHandlerTest::modifyResource_test()
{
   std::shared_ptr<GameEventHandler> event_handler(new GameEventHandler);
   std::shared_ptr<Player> new_player(new Player("1"));
   event_handler->setPresetResources(new_player);

   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::FOOD, 100) == true, "Food addition unsuccessful in modifyResource");
   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::WOOD, 100) == true, "Wood addition unsuccessful in modifyResource");
   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::STONE, 100) == true, "Stone addition unsuccessful in modifyResource");
   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::MONEY, 100) == true, "Money addition unsuccessful in modifyResource");
   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::ORE, 100) == true, "Ore addition unsuccessful in modifyResource");

   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::MONEY, -100) == true, "Money subtraction unsuccessful in modifyResource");

   QVERIFY2(event_handler->modifyResource(new_player, Course::BasicResource::MONEY, -10000) == false, "Negative resources in modifyResource");

}


QTEST_APPLESS_MAIN(EventHandlerTest)


#include "tst_eventhandlertest.moc"
