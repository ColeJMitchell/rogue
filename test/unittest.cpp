//
// Created by cojmi on 3/13/2024.
//

#include <iostream>
#include "gtest/gtest.h"
#include "Configuration.h"
#include "Log.h"
#include "Update.h"
#include "Select.h"
#include "Delete.h"
#include "Insert.h"
#include "Room.h"
#include "Hallway.h"
#include "Model.h"

class ConfigurationTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        c1 = new Configuration("../", "config.txt");
        c2 = new Configuration("../", "config.txt");
        c3 = new Configuration("../", "config2.txt");
        c4 = new Configuration("../", "config.txt");
        c1->setValue("in","out");
        c2->setValue("in","out");
        c4->setFilename("config2.txt");
        c4->setFilepath("../");
    }
    virtual void TearDown() {
        delete c1;
        delete c2;
        delete c3;
        delete c4;
    }
    Configuration *c1;
    Configuration *c2;
    Configuration *c3;
    Configuration *c4;
};
TEST_F(ConfigurationTest, TESTFIXTURE) {
    //checks to see if configuration file paths are working properly
    ASSERT_EQ(c1->file_name(), c2->file_name()) << "These should match!";
    ASSERT_EQ(c3->file_name(), c4->file_name()) << "These should match!";
    ASSERT_EQ(c1->getValue("in"), c2->getValue("in")) << "These should match!";
}

class LogTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        l1 = new Log("config.txt");
        l2 = new Log();
        l2->open_file("config.txt");
        l2->flush();
        l3 = new Log("config.txt");
        l3->close();
    }
    virtual void TearDown() {
        delete l1;
        delete l2;
        delete l3;
    }
    Log *l1;
    Log *l2;
    Log *l3;
};
TEST_F(LogTest, TESTFIXTURE) {
    //tests that all three logger states work
    ASSERT_EQ(l1->return_state(), "open") << "These should match!";
    ASSERT_EQ(l2->return_state(), "flushed") << "These should match!";
    ASSERT_EQ(l3->return_state(), "closed") << "These should match!";
}

class UpdateTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        u1 = new Update;
        i1 = new Insert;
        s1 = new Select;
        d1 = new Delete;
        i1->set_path("../database/rogue.sqlite");
        u1->set_path("../database/rogue.sqlite");
        s1->set_path("../database/rogue.sqlite");
        s1->set_path("../database/rogue.sqlite");
        d1->set_path("../database/rogue.sqlite");
        i1->add_enemy(1000,"Test_enemy",100,100,0,0);
        u1->damage_player_or_enemy("game_enemies",5,1000);
        i1->add_Player(1000);
        u1->add_health(1000,10);
        u1->change_pos(1000,1,"row","game_enemies");
    }
    virtual void TearDown() {
        delete u1;
        delete i1;
        delete s1;
        d1->delete_row(1000, "players");
        d1->delete_row(1000, "game_enemies");
        delete d1;
    }
    Update *u1;
    Insert *i1;
    Select *s1;
    Delete *d1;
};
TEST_F(UpdateTest, TESTFIXTURE) {
    //tests if damage to enemy is working properly
    ASSERT_EQ(s1->get_one_entry("game_enemies", "health", 1000), 95) << "These should match!";
    //tests if movement of player is working properly
    ASSERT_EQ(s1->get_one_entry("game_enemies", "row", 1000), 1) << "These should match!";
    //tests if adding health with health potions works properly
    ASSERT_EQ(s1->get_one_entry("players", "health", 1000), 30) << "These should match!";
}

class DeleteTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        u1 = new Update;
        i1 = new Insert;
        s1 = new Select;
        d1 = new Delete;
        i1->set_path("../database/rogue.sqlite");
        u1->set_path("../database/rogue.sqlite");
        s1->set_path("../database/rogue.sqlite");
        d1->set_path("../database/rogue.sqlite");
        i1->add_enemy(100,"Test_enemy",100,100,0,0);
        d1->delete_row(100, "game_enemies");
        i1->add_enemy(100,"Test_enemy",100,100,0,0);
        i1->add_Player(100);
        d1->delete_row(100, "players");
        i1->add_Player(100);
    }

    virtual void TearDown() {
        delete u1;
        delete i1;
        delete s1;
        d1->delete_row(100, "players");
        d1->delete_row(100, "game_enemies");
        delete d1;
    }

    Update *u1;
    Insert *i1;
    Select *s1;
    Delete *d1;
};

TEST_F(DeleteTest, TESTFIXTURE) {
    //tests to see if player and enemy were deleted because if they were not the unique constraint would cause a SQL error
    ASSERT_EQ(s1->get_one_entry("game_enemies", "health", 100), 100) << "These should match!";
    ASSERT_EQ(s1->get_one_entry("players", "experience", 100), 0) << "These should match!";
}

class InsertTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        u1 = new Update;
        i1 = new Insert;
        s1 = new Select;
        d1 = new Delete;
        i1->set_path("../database/rogue.sqlite");
        u1->set_path("../database/rogue.sqlite");
        s1->set_path("../database/rogue.sqlite");
        d1->set_path("../database/rogue.sqlite");
        i1->add_enemy(500,"Test_enemy",100,100,0,0);
        i1->add_Player(2000);
        i1->add_Item(300,"Greatsword",1000,NULL,0,0);
    }
    virtual void TearDown() {
        delete u1;
        delete i1;
        delete s1;
        d1->delete_row(500,"game_enemies");
        d1->delete_row(2000,"players");
        d1->delete_row(300,"game_items");
        delete d1;
    }
    Update *u1;
    Insert *i1;
    Select *s1;
    Delete *d1;
};
TEST_F(InsertTest, TESTFIXTURE) {
    //checks that the item, enemy and player were properly inserted
    ASSERT_EQ(s1->get_one_entry("game_enemies", "health", 500), 100) << "These should match!";
    ASSERT_EQ(s1->get_one_entry("players","experience",2000), 0) << "These should match";
    ASSERT_EQ(s1->get_one_entry("game_items","damage",300),1000) << "These should match";
}

class SelectTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        u1 = new Update;
        i1 = new Insert;
        s1 = new Select;
        d1 = new Delete;
        i1->set_path("../database/rogue.sqlite");
        u1->set_path("../database/rogue.sqlite");
        s1->set_path("../database/rogue.sqlite");
        d1->set_path("../database/rogue.sqlite");
        i1->add_enemy(500,"Test_enemy",100,100,0,0);
        i1->add_Player(2000);
        i1->add_Item(300,"Greatsword",1000,NULL,0,0);
    }
    virtual void TearDown() {
        delete u1;
        delete i1;
        delete s1;
        d1->delete_row(500,"game_enemies");
        d1->delete_row(2000,"players");
        d1->delete_row(20,"inventory");
        d1->delete_row(300,"game_items");
        delete d1;
    }
    Update *u1;
    Insert *i1;
    Select *s1;
    Delete *d1;
};

TEST_F(SelectTest, TESTFIXTURE) {
    //answer arrays that select statements are checked against
    std::vector<std::string> enemy = {"500", "Test_enemy", "100", "100"};
    std::vector<std::string> player = {"2000", "20", "0", "0"};
    std::vector<std::string> item = {"300", "Greatsword", "1000"};
    //checks that getting row from name works
    for (int i=0; i<4; i++) {
    ASSERT_EQ(s1->get_one_row_string("game_enemies","Test_enemy")[i], enemy[i]) << "These should match!";
    }
    //checks that getting row from id works
    for (int i=0; i<4; i++) {
        ASSERT_EQ(s1->get_one_row_id("players",2000)[i], player[i]) << "These should match!";
    }
    for (int i=0; i<3; i++) {
        ASSERT_EQ(s1->get_one_row_id("game_items",300)[i], item[i]) << "These should match!";
    }
    //checks that select statment for number of rows is working properly
    ASSERT_EQ(s1->get_row_count("game_items"),1);
    //makes sure that you can get one entry for this example damage works properly
    ASSERT_EQ(s1->get_one_entry("game_items","damage",300),1000);
}

class RoomTest : public ::testing ::Test{
protected:
    virtual void SetUp(){
     std::vector<Coordinate> lists;
     Coordinate *c1=new Coordinate(0,7);
     Coordinate *c2=new Coordinate(9,13);
     lists.push_back(*c1);
     lists.push_back(*c2);
     r1=new Room(lists, 10,15,0,0);

    }
    virtual void TearDown() {
        delete r1;
    }
    Room *r1;
};
TEST_F(RoomTest, TEXTFIXTURE){
    ASSERT_EQ(r1->if_at_entrance_exit(0,7),true)<<"this houdl math";
    r1->appear_or_not(0,7);
    ASSERT_EQ(r1->get_appear(),true);
    ASSERT_EQ(r1->if_at_this_room(5,5),true);
    ASSERT_EQ(r1->if_at_this_room(10,5),false);


}

class HallwayTest : public ::testing::Test{
protected:
    void SetUp() override{
        std::vector<HallwayCoor> input;
        input.reserve(11);
         for(int i=2;i<7;i++){
            input.push_back(HallwayCoor(i,0));
        }
         for(int i=1;i<4;i++){
             input.push_back(HallwayCoor(6,i));
         }
     h=new Hallway(input, 7,4,2,0);
    }
    void TearDown() override{
        delete h;
    }
   Hallway *h;
};
TEST_F(HallwayTest, TESTFIXTURE){
    /*
     *
    void appear_or_not(int col, int row);
    void reload_hallway();
    void firstCoord();//not implement, not sure if needed
     */
//set the player at (2,0)
h->appear_or_not(2,0);
h->reload_hallway();
ASSERT_EQ(h->get_lists()[1].get_appear(),true);
ASSERT_EQ(h->buffer_value(0,1),'#');
h->appear_or_not(3,0);
    h->reload_hallway();
    ASSERT_EQ(h->get_lists()[2].get_appear(),true);
    ASSERT_EQ(h->buffer_value(0,2),'#');
}

/*class ModelTest:public::testing::Test{
protected:
        void SetUp() override{
            m1=new Model();
            m1->reload_dungeon();
            std::cout<<m1->buffer_value(25,30)<<std::endl;
        }
        void TearDown() override{

        }
     Model *m1;
};
TEST_F(ModelTest, TestVertical){//error here
    ASSERT_EQ(m1->is_vertical(25,30),true);
    ASSERT_EQ(m1->is_vertical(30,35),false);
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



