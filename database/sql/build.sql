create table players (
    	id int unique not null ,
    	health int not null,
    	gold int not null,
    	experience int not null,
	row int,
	col int
);


create table dungeon_enemies(
	name varchar(50) not null,
	damage int not null,
	health int not null
);

create table game_enemies(
	id int unique not null,
	name varchar(50) not null,
    	damage int not null,
    	health int not null,
	row int,
	col int 
);

create table inventory(
    	id int unique not null,
	name varchar(50) not null,
	damage int,
	amount int
);

create table dungeon_items(
	name varchar(50) not null,
   	damage int,
	amount int
);

create table game_items(
   	id int unique not null,
	name varchar(50) not null,
    	damage int,
	amount int,
	row int,
	col int
);


.separator ","
.mode csv
.import "csv/dungeon_enemies.csv" dungeon_enemies
.import "csv/dungeon_items.csv" dungeon_items
