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
#include "Game.h"

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

/*class LogTest : public ::testing::Test {
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
}*/

class RoomTest : public ::testing ::Test{
protected:
    virtual void SetUp(){
     std::vector<Coordinate> lists;
     Coordinate *c1=new Coordinate(0,7);
     Coordinate *c2=new Coordinate(9,13);
     lists.push_back(*c1);
     lists.push_back(*c2);
     r1=new Room(lists, 10,15,0,0);
     r2=new Room(lists, 10,15,0,0);
    }
    virtual void TearDown() {
        delete r1;
        delete r2;
    }
    Room *r1;
    Room *r2;
};
TEST_F(RoomTest, TEXTFIXTURE){
    ASSERT_EQ(r1->if_at_entrance_exit(0,7),true)<<"this should math";
    //test reload before appear
    ASSERT_EQ(r1->get_appear(),false);
    for(int row=0; row<15;row++){
        for(int col=0;col<10;col++){
            ASSERT_EQ(r1->buffer_value(row,col),'\0');
        }
    }
    //test appear_or_not
    r1->appear_or_not(0,7);
    ASSERT_EQ(r1->get_appear(),true);
    ASSERT_EQ(r1->if_at_this_room(5,5),true);
    ASSERT_EQ(r1->if_at_this_room(10,5),false);
    r1->reload_room();
    //test reload after appear
    for(int row=0; row<15;row++){
        for(int col=0;col<10;col++) {
            if (r1->if_at_entrance_exit(col, row)) ASSERT_EQ(r1->buffer_value(row, col), '+');
            else if (row == 0) ASSERT_EQ(r1->buffer_value(row, col), '-');
            else if (row == 14) ASSERT_EQ(r1->buffer_value(row, col), '-');
            else if (col == 0) ASSERT_EQ(r1->buffer_value(row, col), '|');
            else if (col == 9) ASSERT_EQ(r1->buffer_value(row, col), '|');
            else
                ASSERT_EQ(r1->buffer_value(row, col), '.');
        }
    }
    //test first room
    r2->first_room();
    ASSERT_EQ(r2->get_appear(),true);
    //test if_entrance_around()
    ASSERT_EQ(r1->if_entrance_around(0,8),true);
    ASSERT_EQ(r1->if_entrance_around(1,8),false);
    ASSERT_EQ(r1->if_entrance_around(9,12),true);
    ASSERT_EQ(r1->if_entrance_around(8,13),true);
}

class HallwayTest : public ::testing::Test{
protected:
    void SetUp() override{
        std::vector<HallwayCoor> input;
        input.reserve(11);
         for(int i=2;i<7;i++){
            input.push_back(HallwayCoor(i,0));
        }
         for(int i=0;i<4;i++){
             input.push_back(HallwayCoor(6,i));
         }
     h=new Hallway(input, 5,4,2,0);
    }
    void TearDown() override{
        delete h;
    }
   Hallway *h;
};
TEST_F(HallwayTest, TESTFIXTURE){
    //test reload before
    for(int row=0; row<4;row++){
        for(int col=0;col<5;col++){
            ASSERT_EQ(h->buffer_value(row,col),'\0');
        }
    }
//set the player at (2,0)
//test reload after appear
   h->appear_or_not(2,0);
   h->reload_hallway();
   ASSERT_EQ(h->get_lists()[1].get_appear(),true);
   ASSERT_EQ(h->buffer_value(0,1),'#');
   h->appear_or_not(3,0);
   h->reload_hallway();
   ASSERT_EQ(h->get_lists()[2].get_appear(),true);
   ASSERT_EQ(h->buffer_value(0,2),'#');
   //test get_list()
   std::vector<HallwayCoor> s=h->get_lists();
   for(int i=0;i<s.size();i++){
       for(int j=0;j<5;j++){
           ASSERT_EQ(s[j].get_col(),j+2);
           ASSERT_EQ(s[j].get_row(),0);
       }
       for(int j=0;j<4;j++){
           ASSERT_EQ(s[j+5].get_col(),6);
           ASSERT_EQ(s[j+5].get_row(),j);
       }
   }
}

class ModelTest:public::testing::Test{
protected:
        void SetUp() override{
            m1=new Model("../database/rogue.sqlite");
            m1->all_appear();
            m1->reload_dungeon();
        }
        void TearDown() override{
            delete m1;
        }
     Model *m1{};
};
TEST_F(ModelTest, TEXTFIXTURE){

    //test roload
    for(int i=17;i<30;i++){
        ASSERT_EQ(m1->buffer_value(i,2),'|');
    }
    for(int i=17;i<30;i++){
        if(i!=23) {
            ASSERT_EQ(m1->buffer_value(i, 11), '|');
        }
        else{
            ASSERT_EQ(m1->buffer_value(i,11),'+');
        }
    }
    for(int i=2;i<12;i++){
        ASSERT_EQ(m1->buffer_value(16,i),'-');
    }
    for(int i=2;i<12;i++){
        ASSERT_EQ(m1->buffer_value(16,i),'-');
    }
    for(int i=22;i<32;i++){
        if(i!=25) {
            ASSERT_EQ(m1->buffer_value(27, i), '-');
        }
        else{
            ASSERT_EQ(m1->buffer_value(27,i),'+');
        }
    }
    for(int i=20;i<50;i++){
        if(i>=25 && i<=40) {
            ASSERT_EQ(m1->buffer_value(35, i), '#');
        }
        else{
            ASSERT_EQ(m1->buffer_value(35, i), ' ');
        }
    }

   //test is_vertical
   //on the vertical hallway
    ASSERT_EQ(m1->is_vertical(25,30),true);
    //on the horizontal hallway
    ASSERT_EQ(m1->is_vertical(30,35),false);
    //at the entrance point of vertical hallway
    ASSERT_EQ(m1->is_vertical(25,27),true);
    //in the room
    ASSERT_EQ(m1->is_vertical(25,25),false);
    //either in the room or on some hallway
    ASSERT_EQ(m1->is_vertical(15,16),false);

    //test if_at_turning_point
    std::pair<bool, Direction> expected=std::make_pair(true, Direction::UpAndRight);
    ASSERT_EQ(m1->if_at_turning_point(25,35),expected);
    std::pair<bool, Direction> expected1=std::make_pair(true, Direction::UpAndLeft);
    ASSERT_EQ(m1->if_at_turning_point(40,35),expected1);
    //a special turning point
    std::pair<bool, Direction> expected2=std::make_pair(true, Direction::DownAndRight);
    ASSERT_EQ(m1->if_at_turning_point(52,25),expected2);

    //test moving and constrain
    m1->move_left();
    m1->reload_dungeon();
    ASSERT_EQ(m1->buffer_value(20,4),'@');
    m1->set_constraint();
    ASSERT_EQ(m1->get_left(),3);
    ASSERT_EQ(m1->get_right(),10);
    ASSERT_EQ(m1->get_up(),17);
    ASSERT_EQ(m1->get_down(),29);
    //move the player near the exit point of the room/in the room
    m1->set_position(10,23);
    m1->set_constraint();
    ASSERT_EQ(m1->get_left(),0);
    ASSERT_EQ(m1->get_right(),100);
    ASSERT_EQ(m1->get_up(),0);
    ASSERT_EQ(m1->get_down(),80);
    //set the player to be on the hallway
    m1->set_position(15,23);
    m1->set_constraint();
    ASSERT_EQ(m1->get_left(),14);
    ASSERT_EQ(m1->get_right(),16);
    ASSERT_EQ(m1->get_up(),80);
    ASSERT_EQ(m1->get_down(),0);
    //move the player on the hallway but near exit point
    m1->set_position(25,28);
    m1->set_constraint();
    ASSERT_EQ(m1->get_left(),100);
    ASSERT_EQ(m1->get_right(),0);
    ASSERT_EQ(m1->get_up(),27);
    ASSERT_EQ(m1->get_down(),29);
    //move the player on the vertical hallway
    m1->set_position(25,30);
    m1->set_constraint();
    ASSERT_EQ(m1->get_left(),100);
    ASSERT_EQ(m1->get_right(),0);
    ASSERT_EQ(m1->get_up(),29);
    ASSERT_EQ(m1->get_down(),31);

    //test is in the room
    ASSERT_EQ(m1->is_in_the_room(10,20),0);
    ASSERT_EQ(m1->is_in_the_room(30,16),1);
    //on the hallway
    ASSERT_EQ(m1->is_in_the_room(15,23),-1);
    //either in the room or hallway
    ASSERT_EQ(m1->is_in_the_room(40,15),-1);

    //test wipe_screen()
    m1->wipe_screen();
    for(int i=0;i<80;i++){
        for(int j=0;j<100;j++){
            ASSERT_EQ(m1->buffer_value(i,j),' ');
        }
    }
}
class GameTest:public::testing::Test{
protected:
    void SetUp() override{
        g1=new Game("../database/rogue.sqlite");
        s=new Select();
        s->set_path("../database/rogue.sqlite");
    }
    void TearDown() override{
        delete g1;
    }
    Game *g1{};
    Select *s;
};
TEST_F(GameTest, TEXTFXITURE){
    /*
     * void spawn_enemy(int id, std::string name, int row, int col);
     * void spawn_item(int id, std::string name, int row, int col);

    std::vector<int> add_all_enemies(Log &logger);

    std::vector<int> add_all_items(Log &logger);
     */
    //test spawn_enemy
    g1->spawn_enemy(2003,"Emu",30,10);
    std::vector<std::string> expected;
    expected.push_back(std::to_string(2003));
    expected.push_back("Emu");
    expected.push_back(std::to_string(3));
    expected.push_back(std::to_string(8));
    expected.push_back(std::to_string(30));
    expected.push_back(std::to_string(10));
    ASSERT_EQ(s->get_one_row_id("game_enemies",2003),expected);
    //test spawn_item
    g1->spawn_item(2002,"Health_potion",20,60);
    std::vector<std::string> expected2;
    expected2.push_back(std::to_string(2002));
    expected2.push_back("Health_potion");
    expected2.push_back(std::to_string(0));
    expected2.push_back(std::to_string(5));
    expected2.push_back(std::to_string(20));
    expected2.push_back(std::to_string(60));
    ASSERT_EQ(s->get_one_row_id("game_items",2002),expected2);

    //test add_all_items
    Log l;
    g1->add_all_items(l);
    std::vector<std::string> expected3;
    expected3.push_back(std::to_string(0));
    expected3.push_back("Amulet");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(39));
    expected3.push_back(std::to_string(71));
    ASSERT_EQ(s->get_one_row_id("game_items",0),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(1));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(30));
    expected3.push_back(std::to_string(65));
    ASSERT_EQ(s->get_one_row_id("game_items",1),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(2));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(14));
    expected3.push_back(std::to_string(70));
    ASSERT_EQ(s->get_one_row_id("game_items",2),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(3));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(12));
    expected3.push_back(std::to_string(66));
    ASSERT_EQ(s->get_one_row_id("game_items",3),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(4));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(35));
    expected3.push_back(std::to_string(62));
    ASSERT_EQ(s->get_one_row_id("game_items",4),expected3);


    //test add_all_enemies
    g1->add_all_enemies(l);
    //another 17 enemies have been added to the game_enemies, so check from id=17;
    expected3.clear();
    expected3.push_back(std::to_string(17));
    expected3.push_back("Emu");
    expected3.push_back(std::to_string(3));
    expected3.push_back(std::to_string(8));
    expected3.push_back(std::to_string(25));
    expected3.push_back(std::to_string(25));
    ASSERT_EQ(s->get_one_row_id("game_enemies",17),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(18));
    expected3.push_back("Bat");
    expected3.push_back(std::to_string(2));
    expected3.push_back(std::to_string(4));
    expected3.push_back(std::to_string(15));
    expected3.push_back(std::to_string(25));
    ASSERT_EQ(s->get_one_row_id("game_enemies",18),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(19));
    expected3.push_back("Zombie");
    expected3.push_back(std::to_string(4));
    expected3.push_back(std::to_string(10));
    expected3.push_back(std::to_string(30));
    expected3.push_back(std::to_string(40));
    ASSERT_EQ(s->get_one_row_id("game_enemies",19),expected3);
   /*xpected3.clear();
    expected3.push_back(std::to_string(3));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(12));
    expected3.push_back(std::to_string(66));
    ASSERT_EQ(s->get_one_row_id("game_items",3),expected3);
    expected3.clear();
    expected3.push_back(std::to_string(4));
    expected3.push_back("Health_potion");
    expected3.push_back(std::to_string(0));
    expected3.push_back(std::to_string(5));
    expected3.push_back(std::to_string(35));
    expected3.push_back(std::to_string(62));
    ASSERT_EQ(s->get_one_row_id("game_items",4),expected3);*/
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



