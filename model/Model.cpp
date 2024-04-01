//
// Created by cojmi on 3/14/2024.
//
#include <iostream>
#include <random>
#include "Model.h"
#include "Select.h"
#include "Insert.h"
#include "Game.h"
#include "Player.h"
#include "Delete.h"
#include "ncurses.h"
#include "Log.h"
#include "Update.h"

Select s1;
Update u1;
Delete d1;
int current_player;

std::vector<int> enemy_ids;
std::vector<int> item_ids;
Log logger;
Model::Model(std::string filepath) {
    rowpos=20;
    colpos=5;
    screen_page = 0;
    enemies_slain = 0;
    logger.open_file("logger.txt");
    d1.set_path(filepath);
    s1.set_path(filepath);
    u1.set_path(filepath);
    Player p1(filepath);
    int player_id_counter = s1.get_row_count("players");
    logger<<"player spawned at row = 20 col = 5 id = "<<current_player<<"\n";
    p1.create_new_player(player_id_counter);
    p1.update_player_pos(player_id_counter,rowpos,colpos);
    current_player = player_id_counter;
    Game g(filepath);
    enemy_ids = g.add_all_enemies(logger);
    item_ids = g.add_all_items(logger);
  //creates rooms with entr_exit points, room size and room offsets
    std::vector<std::vector<Coordinate>> entrance_exit(4);
    entrance_exit[0].push_back(Coordinate(11,23));
    entrance_exit[1].push_back(Coordinate(22,23));
    entrance_exit[1].push_back(Coordinate(25,27));
    entrance_exit[2].push_back(Coordinate(40,33));
    entrance_exit[2].push_back(Coordinate(46,28));
    entrance_exit[3].push_back(Coordinate(53,25));
    std::vector<Coordinate> room_size;
    room_size.push_back(Coordinate(10,15));
    room_size.push_back(Coordinate(10,20));
    room_size.push_back(Coordinate(10,10));
    room_size.push_back(Coordinate(20,30));

    std::vector<Coordinate> offsets;
    offsets.push_back(Coordinate(2,16));
    offsets.push_back(Coordinate(22,8));
    offsets.push_back(Coordinate(37,24));
    offsets.push_back(Coordinate(53,11));

    for(int i=0;i<4;i++){
        rooms.push_back(Room(entrance_exit[i],room_size[i].get_col(),room_size[i].get_row(),offsets[i].get_col(),offsets[i].get_row()));
    }
    //set the first room to appear
    rooms[0].first_room();
//------------------------------------------------------------
    //set up hallways
    std::vector<std::vector<HallwayCoor>> coors(3);
    //each hallway starts at the entrance_or_exit point
    //the coordinates for the first hallway
    for(int i=11;i<23;i++) {
        coors[0].push_back(HallwayCoor( i, 23));
    }

    //the coordinates for the second hallway
   for(int i=27;i<36;i++){
        coors[1].push_back(HallwayCoor(25,i));
    }
    for(int i=26;i<41;i++){
        coors[1].push_back(HallwayCoor(i,35));
    }
    for(int i=34;i>32;i--){
        coors[1].push_back(HallwayCoor(40,i));
    }

    //the coordinates for the third hallway
    for(int i=46; i<53;i++){
        coors[2].push_back(HallwayCoor(i,28));
    }
    for(int i=27;i>24;i--){
        coors[2].push_back(HallwayCoor(52,i));
    }
      coors[2].push_back(HallwayCoor(53,25));

    std::vector<Coordinate> hallway_size;
    hallway_size.push_back(Coordinate(12,1));//on one more extension
    hallway_size.push_back(Coordinate(16,9));
    hallway_size.push_back(Coordinate(8,4));

    std::vector<Coordinate> offsets_h;
    offsets_h.push_back(Coordinate(11,23));
    offsets_h.push_back(Coordinate(25,27));
    offsets_h.push_back(Coordinate(46,25));

    for(int i=0;i<3;i++){
        hallways.push_back(Hallway(coors[i],hallway_size[i].get_col(),hallway_size[i].get_row(),offsets_h[i].get_col(),offsets_h[i].get_row()));
    }

    whole_buffer.resize(ROWMAX,std::vector<char>(COLMAX));
    //initialize constrain based on the first room
    left=rooms[0].get_offsetc()+1;
    right=rooms[0].get_colMax()+rooms[0].get_offsetc()-2;
    up=rooms[0].get_offsetr()+1;
    down=rooms[0].get_rowMax()+rooms[0].get_offsetr()-2;
}

//reload the whole buffer every time before drawing
//the function refreshes the buffer
//then, assigns the value of buffer of each hallway to the whole buffer with coordinates matched
//then, assigns the value of buffer of each room to the whole buffer with coordinates matched
//then, at the entrance or exit point, reassign the value of buffer of each hallway to the whole buffer, since when the room is shown in the map
//the entrance_exit of this room should be shown as "+"(entrance_exit point is also included in the hallway coordinate lists)
//finally, display "@"
void Model::reload_dungeon() {

//checks to see if player is dead and switches to death screen if it is
if(s1.get_one_entry("players","health",current_player)<=0){
    screen_page=1;
    logger<<"player died id = " << current_player << "\n";
    return;
}


//refresh the buffer before making any change
    for(int row = 0; row < ROWMAX; row++){
        for(int col = 0; col < COLMAX; col++){
            whole_buffer[row][col]=' ';
        }
    }

//add hallways to the whole_buffer
for(auto &hallway : hallways){
    hallway.appear_or_not(colpos,rowpos);
    hallway.reload_hallway();
    for (int row = 0; row < hallway.get_rowMax(); row++) {
        for (int col = 0; col < hallway.get_colMax(); col++) {
            if(whole_buffer[row+hallway.get_offsetr()][col+hallway.get_offsetc()]!='+'){//avoid one hallway buffer covering other hallways
            whole_buffer[row+hallway.get_offsetr()][col+hallway.get_offsetc()]=hallway.buffer_value(row, col);
            }
        }
    }
}
//add rooms to the whole_buffer
for(auto &room : rooms) {
    room.appear_or_not(colpos,rowpos);
    room.reload_room();
    for (int row = 0; row < room.get_rowMax(); row++) {
        for (int col = 0; col < room.get_colMax(); col++) {
            whole_buffer[row+room.get_offsetr()][col+room.get_offsetc()]=room.buffer_value(row, col);
        }
    }
}

//update the entrance point of each room
//go through all hallways, let the last coordinate in each hallway show the buffer of each hallway
//the room would cover the entrance point
for(int i=0;i<hallways.size();i++){
    std::vector<HallwayCoor>& s=hallways[i].get_lists();
   int j=s.size()-1;
            int row=s[j].get_row();
            int col=s[j].get_col();
            whole_buffer[row][col]=hallways[i].buffer_value(row-hallways[i].get_offsetr(), col-hallways[i].get_offsetc());
}

//displays the items and checks for player collision
int counter2 = 0;
for(int i :item_ids){
        int erow = s1.get_one_entry("game_items","row",i);
        int ecol = s1.get_one_entry("game_items","col",i);
        if(whole_buffer[erow][ecol+1]!='.'&&whole_buffer[erow][ecol-1]!='.'&&whole_buffer[erow+1][ecol]!='.'&&whole_buffer[erow-1][ecol]!='.'){
            continue;
        }
        std::vector<std::string> temp = s1.get_one_row_id("game_items",i);
        if(temp[1]=="Health_potion"){
            whole_buffer[erow][ecol] = '%';
            if(s1.get_one_entry("players","row",current_player)==erow&&s1.get_one_entry("players","col",current_player)==ecol){
                logger<<"player picked up health potion id = "<<i << "\n";
                u1.add_health(current_player,10);
                item_ids.erase(item_ids.begin()+counter2);
            }
        }
        else if(temp[1]=="Amulet") {
            whole_buffer[erow][ecol] = 'A';
            if(s1.get_one_entry("players","row",current_player)==erow&&s1.get_one_entry("players","col",current_player)==ecol){
                logger<<"player picked up amulet of yendor id = "<<i << "\n";
                screen_page=2;
                item_ids.erase(item_ids.begin()+counter2);
                return;
            }

        }
        counter2++;
    }
    //displays the character
    whole_buffer[rowpos][colpos] = '@';
    // place the game item
    //iterate over all enemy ids and place them on map, also have each enemy move randomly once per turn
    int counter=0;
    for(int i:enemy_ids){
        std::vector<std::string> temp = s1.get_one_row_id("game_enemies",i);
        int erow = s1.get_one_entry("game_enemies","row",i);
        int ecol = s1.get_one_entry("game_enemies","col",i);
        if(whole_buffer[erow][ecol+1]!='.'&&whole_buffer[erow][ecol-1]!='.'&&whole_buffer[erow+1][ecol]!='.'&&whole_buffer[erow-1][ecol]!='.'){
            continue;
        }
        int r = rand()%4;
        switch (r) {
            //'.' makes sure the move is valid and position is changed if it is
            case 0:
                if(whole_buffer[erow+1][ecol]=='.'){
                    u1.change_pos(i,erow+1,"row","game_enemies");
                    logger <<temp[1] << " moved to position row = "<<s1.get_one_entry("game_enemies","row",i)<<" col = "<<ecol << " id = "<<i<< "\n";
                }
                break;
            case 1:
                if(whole_buffer[erow-1][ecol]=='.') {
                    u1.change_pos(i, erow-1, "row", "game_enemies");
                    logger<<temp[1] << " moved to position row = "<<s1.get_one_entry("game_enemies","row",i)<<" col = "<<ecol << " id = "<<i <<"\n";
                }
                break;
            case 2:
                if(whole_buffer[erow][ecol+1]=='.') {
                    u1.change_pos(i, ecol+1, "col", "game_enemies");
                    logger<<temp[1] << " moved to position row = "<<erow<<" col = "<<s1.get_one_entry("game_enemies","col",i)<<" id = "<<i <<"\n";
                }
                break;
            case 3:
                if(whole_buffer[erow][ecol-1]=='.') {
                    u1.change_pos(i, ecol-1, "col", "game_enemies");
                    logger<<temp[1] << " moved to position row =  "<<erow<<" col = "<<s1.get_one_entry("game_enemies","col",i)<<" id = "<<i <<"\n";

                }
                break;
        }
        //do a collision check with player
        int new_erow = s1.get_one_entry("game_enemies","row",i);
        int new_ecol = s1.get_one_entry("game_enemies","col",i);
        //checking if player is on surrounding tile
        if(s1.get_one_entry("players","row",current_player)==new_erow+1&&s1.get_one_entry("players","col",current_player)==new_ecol){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger << temp[1] << " slain by player id = "<<i<<"\n";
        }
        else if(s1.get_one_entry("players","row",current_player)==new_erow-1&&s1.get_one_entry("players","col",current_player)==new_ecol){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger<< temp[1] << " slain by player id = "<<i<<"\n";
        }
        else if(s1.get_one_entry("players","row",current_player)==new_erow+1&&s1.get_one_entry("players","col",current_player)==new_ecol+1){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger << temp[1] << " slain by player id = "<<i<<"\n";
        }
        else if(s1.get_one_entry("players","row",current_player)==new_erow&&s1.get_one_entry("players","col",current_player)==new_ecol+1){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger<< temp[1] << " slain by player id = "<<i<<"\n";
        }
        else if(s1.get_one_entry("players","row",current_player)==new_erow&&s1.get_one_entry("players","col",current_player)==new_ecol-1){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger << temp[1] << " slain by player id = "<<i<<"\n";
        }
        else if(s1.get_one_entry("players","row",current_player)==new_erow-1&&s1.get_one_entry("players","col",current_player)==new_ecol-1){
            u1.damage_player_or_enemy("players",s1.get_one_entry("game_enemies","damage",i),current_player);
            enemy_ids.erase(enemy_ids.begin()+counter);
            enemies_slain++;
            logger << temp[1] << " slain by player id = "<<i<<"\n";
        }
        //check to see what charachter should be displayed for each enemy in the database
        if(temp[1]=="Emu"){
            whole_buffer[new_erow][new_ecol] = 'E';
        }
        else if(temp[1]=="Bat"){
            whole_buffer[new_erow][new_ecol] = 'B';
        }
        else if(temp[1]=="Snake"){
            whole_buffer[new_erow][new_ecol] = 'S';
        }
        else if(temp[1]=="Hobgoblin"){
            whole_buffer[new_erow][new_ecol] = 'H';
        }
        else if(temp[1]=="Zombie"){
            whole_buffer[new_erow][new_ecol] = 'Z';
        }
        else if(temp[1]=="Dragon"){
            whole_buffer[new_erow][new_ecol] = 'D';
        }
        counter++;
    }
}

//these four functions are moving controller, with four constrains(up,down, left, right) and updats player position in the database
void Model::move_up(void){
    if(rowpos > up) {
        rowpos--;
    }
   u1.change_pos(current_player,rowpos,"row","players");
    logger<<"player moved to row = "<< rowpos<< " col = "<<colpos<<" id = "<<current_player<<"\n";
}

void Model::move_down(void){
    if(rowpos < down ) {
        rowpos++;
    }
    u1.change_pos(current_player,rowpos,"row","players");
    logger<<"player moved to row = "<< rowpos<< " col = "<<colpos<<" id = "<<current_player<<"\n";
}

void Model::move_left(void){
    if(colpos > left) {
        colpos--;
    }
    u1.change_pos(current_player,colpos,"col","players");
    logger<<"player moved to row = "<< rowpos<< " col = "<<colpos<<" id = "<<current_player<<"\n";
}

void Model::move_right(void){
    if(colpos < right ) {
        colpos++;
    }
    u1.change_pos(current_player,colpos,"col","players");
    logger<<"player moved to row = "<< rowpos<< " col = "<<colpos<<" id = "<<current_player<<"\n";
}
//return the value of whole buffer at row and col
char Model::buffer_value(int row, int col){
    return whole_buffer[row][col];
}

//return the height of the whole buffer
int Model::max_rows(void) {
    return ROWMAX;
}

//return the length of the whole buffer
int Model::max_cols(void) {
    return COLMAX;
}

/*check if the input coordinate(player) is at the vertical hallway
*check after the whole_buffer has been reloaded for the last move, and before the next move
 * @param col the col coordinate of the point to be checked
 * @param row the row coordinate of the point to be checked
*/
bool Model::is_vertical(int col, int row) {
 if (row>0 && row < ROWMAX-1 && col>=0 && col<COLMAX) {
    if (whole_buffer[row - 1][col] == '.' && whole_buffer[row + 1][col] == '#') {
        return true;
    } else if (whole_buffer[row - 1][col] == '#' && whole_buffer[row + 1][col] == '.') {
        return true;
    } else if (whole_buffer[row - 1][col] == '#' && whole_buffer[row + 1][col] == '#') {
        return true;
    } else if (whole_buffer[row - 1][col] == '+' && whole_buffer[row + 1][col] == '#') {
        return true;
    } else if (whole_buffer[row - 1][col] == '#' && whole_buffer[row + 1][col] == '+') {
        return true;
    } else {
        return false;
    }
}
    std::cerr<<"Out of boundary"<<std::endl;
    return false;
}

//check if the input coordinate(player) is at the turning points of hallway
std::pair<bool, Direction> Model::if_at_turning_point(int col, int row){
    if((whole_buffer[row-1][col] == '#' || whole_buffer[row-1][col] == '+')&&
       (whole_buffer[row][col+1] == '#' || whole_buffer[row][col+1] == '+')){//up and right
        return {true,Direction::UpAndRight};
    }
    else if((whole_buffer[row-1][col]=='#' || whole_buffer[row-1][col]=='+') &&
            (whole_buffer[row][col-1]=='#' || whole_buffer[row][col-1]=='+')){//up and left
        return {true,Direction::UpAndLeft};
    }
    else if((whole_buffer[row+1][col]=='#' || whole_buffer[row+1][col]=='+') &&
            (whole_buffer[row][col+1]=='#' || whole_buffer[row][col+1]=='+')){//down and right
        return {true,Direction::DownAndRight};
    }
    else if((whole_buffer[row+1][col]=='#' || whole_buffer[row+1][col]=='+') &&
            (whole_buffer[row][col-1]=='#' || whole_buffer[row][col-1]=='+')){//down and left
        return {true,Direction::DownAndLeft};
    }
    else{return {false,Direction::NotTurningPoint};}
}

//return the room index where the player is
//return -1 if the player is not in any room
int Model::is_in_the_room(int col, int row){
    for(int i=0;i<rooms.size();i++){
        if(rooms[i].if_at_this_room(col, row)){
            return i;
        }
    }
    return -1;
}

//set constrain for moving so that
//when the player is in the room, it cannot go out of the room
//when the player is on the hallway, it was constrained in the hallway
void Model::set_constraint(){
    if(is_in_the_room(colpos, rowpos) != -1){//the player is in the room
        int i=is_in_the_room(colpos, rowpos);
        if(rooms[i].if_entrance_around(colpos,rowpos)){//check if there are entrance point around
            left=0;
            right=COLMAX;
            up=0;
            down=ROWMAX;
        }
        else {
            left = rooms[i].get_offsetc() + 1;
            right = rooms[i].get_colMax() + rooms[i].get_offsetc() - 2;
            up = rooms[i].get_offsetr() + 1;
            down = rooms[i].get_rowMax() + rooms[i].get_offsetr() - 2;
        }
    }
    else{//if the player is not in the room, which means it is on the hallway
        if(if_at_turning_point(colpos, rowpos).first){
            switch(if_at_turning_point(colpos,rowpos).second){
                case Direction::UpAndRight://only can move up and right
                  left=COLMAX;
                  right=colpos+1;
                  up=rowpos-1;
                  down=0;
                  break;
                case Direction:: UpAndLeft://only can move up and left
                  left=colpos-1;
                  right=0;
                  up=rowpos-1;
                  down=0;
                  break;
                case Direction::DownAndRight://only can move down and right
                    left=COLMAX;
                    right=colpos+1;
                    up=ROWMAX;
                    down=rowpos+1;
                    break;
                case Direction::DownAndLeft://only can move down and left
                    left=colpos-1;
                    right=0;
                    up=ROWMAX;
                    down=rowpos+1;
                    break;
                default:
                    break;
            }
        }
        else{//it is in the hallway, but not at the turning point
              if(is_vertical(colpos,rowpos)) {//if the player is on the vertical hallway
                   //only move up and down
                   left = COLMAX;
                   right = 0;
                   up = rowpos-1;
                   down = rowpos+1;
              }
              else{//if the player is on the horizontal hallway
                   //only move left and right
                   left= colpos-1;
                   right=colpos+1;
                   up=ROWMAX;
                   down=0;
              }
        }
    }
}
//wipes the entire screen
void Model::wipe_screen(){
    for(int row = 0; row < ROWMAX; row++){
        for(int col = 0; col < COLMAX; col++){
            whole_buffer[row][col]=' ';
        }
    }
}
//returns current health of player to be displayed
int Model::return_health(){
    return s1.get_one_entry("players","health",current_player);
}

//------------------------------------
//these are functions for unittest
void Model::all_appear(){
    for(Room &r: rooms){
        r.first_room();
    }
    for(Hallway &h:hallways){
        for(HallwayCoor &c:h.get_lists()){
            c.set_appear();
        }
    }
}
//return the left constraint
int Model::get_left() {
    return left;
}
//return the right constraint
int Model::get_right() {
    return right;
}
//return the up constraint
int Model::get_up() {
    return up;
}
//return the down constraint
int Model::get_down() {
    return down;
};
void Model::set_position(int col, int row){
    colpos=col;
    rowpos=row;
}