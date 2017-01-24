#pragma once
const int DIMW = 50, DIMH = 50;//ground tile size
const int SCREENW = 1680, SCREENH = 1050;//console size
const int WORLDW = 6000, WORLDH = 6000;//map size
const int MAPW = WORLDW / DIMW, MAPH = WORLDH / DIMH;//for ground matrix

//const int ISLANDBORDERH = 6, ISLANDBORDERW = 6;
//const int ISLANDW = 14 + ISLANDBORDERW, ISLANDH = 14 + ISLANDBORDERH, CLIFFH = 2, BIG_CLIFFH = 3;

const int ISLANDW = 10, ISLANDH = 10;
const int FPS = 60;
const int PLAYERVELX = 5, PLAYERVELY = 5;

enum ID{ PLAYER, FOOTSOLDIER, TERRAIN_EMPTY, TERRAIN_FULL, WEAPON, BULLET, MISC};
enum STATE{ TITLE, PLAYING, LOST };

const int COL_RANGEX = DIMW*3, COL_NUMX = WORLDW / COL_RANGEX;
const int COL_RANGEY = DIMH*3, COL_NUMY = WORLDH / COL_RANGEY;
const int COMMONRAD = DIMW / 2;

//specific dimensions of trees
const int TREE_1_LW = 138, TREE_1_RW = 70, TREE_1_H = 303;//<-138->( 75 )<-70-> == 280
const int TREE_2_LW = 63, TREE_2_RW = 84, TREE_2_H = 303;//<-63->( 30 )<- 84-> == 177
const int TREE_3_LW = 57, TREE_3_RW = 36, TREE_3_H = 216;//<-57 ->( 27 )<- 36-> == 120
const int TREE_4_LW = 100, TREE_4_RW = 80, TREE_4_H = 276;//<-100->( 36 )<- 80-> == 432
const int TREE_5_LW = 69, TREE_5_RW = 108, TREE_5_H = 267;//<-69->( 39 )<- 108-> == 216

//island blocks
const int SCAFFOLD_FLOOR = 5;
const int SCAFFOLD_BASE = 10;
const int BRICK_FLOOR = 15;
const int BRICK_BASE = 20;
const int GRASS_FLOOR = 25;
const int GRASS_BASE = 30;

const int MIX_SCAFFOLD_BRICK_LEFT_FLOOR = 35;
const int MIX_SCAFFOLD_BRICK_RIGHT_FLOOR = 40;
const int MIX_SCAFFOLD_BRICK_LEFT_BASE = 45;
const int MIX_SCAFFOLD_BRICK_RIGHT_BASE = 50;

const int MIX_GRASS_BRICK_LEFT_FLOOR = 55;
const int MIX_GRASS_BRICK_RIGHT_FLOOR = 60;
const int MIX_GRASS_BRICK_LEFT_BASE = 65;
const int MIX_GRASS_BRICK_RIGHT_BASE = 70;

const int DETAIL_SCAFFOLD = 75;
const int DETAIL_BRICK = 80;
const int DETAIL_GRASS = 85;
const int DETAIL_MIX_SCAFFOLD_BRICK_LEFT = 90;
const int DETAIL_MIX_SCAFFOLD_BRICK_RIGHT = 95;
const int DETAIL_MIX_GRASS_BRICK_LEFT = 100;
const int DETAIL_MIX_GRASS_BRICK_RIGHT = 105;

const int DETAIL_BRICK_WALL = 110;