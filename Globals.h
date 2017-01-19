#pragma once
const int DIMW = 50, DIMH = 50;//ground tile size, among other things
const int SCREENW = 1680, SCREENH = 1050;//console size
const int WORLDW = 2000, WORLDH = 2000;//map size
const int MAPW = WORLDW / DIMW, MAPH = WORLDH / DIMH;//for ground matrix
const int ISLANDBORDERH = 6, ISLANDBORDERW = 6;
const int ISLANDW = 14 + ISLANDBORDERW, ISLANDH = 14 + ISLANDBORDERH, CLIFFH = 2, BIG_CLIFFH = 3;
const int FPS = 60;
const int WALL_DISP = 60;
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

const int FOL_1_x = 155;
const int FOL_1_y = 288;
const int FOL_2_x = 171;
const int FOL_2_y = 272;
const int FOL_3_x = 188;
const int FOL_3_y = 248;
const int FOL_4_x = 160;
const int FOL_4_y = 240;
const int FOL_5_x = 128;
const int FOL_5_y = 240;
const int FOL_6_x = 112;
const int FOL_6_y = 232;
const int FOL_7_x = 100;
const int FOL_7_y = 224;
const int FOL_8_x = 172;
const int FOL_8_y = 276;

const int FLAG_1_x = 61;
const int FLAG_1_y = 418;

const int WALL = 4;

const int WALL_END_T2 = 6;

const int WALL_COR_LEFT_T2 = 8;//elaborate shading walls
const int WALL_COR_RIGHT_T2 = 10;

const int WALL_COR_LEFT = 12;
const int WALL_COR_RIGHT = 14;


const int WALL_COR_TOP_LEFT_T2 = 16;//corners
const int WALL_COR_TOP_RIGHT_T2 = 18;
const int WALL_COR_TOP_LEFT_T1 = 20;
const int WALL_COR_TOP_RIGHT_T1 = 22;

const int WALL_COR_BOT_LEFT_T0 = 24;
const int WALL_COR_BOT_RIGHT_T0 = 26;

const int WALL_COR_BOT_LEFT_T1 = 28;
const int WALL_COR_BOT_RIGHT_T1 = 30;
const int WALL_COR_BOT_LEFT_T2 = 32;
const int WALL_COR_BOT_RIGHT_T2 = 34;


const int WALL_BACK_LEFT_T1 = 36;
const int WALL_BACK_RIGHT_T1 = 38;

const int WALL_BACK_LEFT_T2 = 40;
const int WALL_BACK_RIGHT_T2 = 42;

const int TIER_1 = 44;
const int TIER_2 = 46;

const int FADE_1 = 54;
const int FADE_2 = 56;
const int FADE_END = 58;

const int DETAIL_SHADOW_T1_1 = 60;
const int DETAIL_SHADOW_T1_2 = 62;
const int DETAIL_SHADOW_COR_T1_1 = 64;
const int DETAIL_SHADOW_COR_T1_2 = 66;
const int DETAIL_SHADOW_COR_T1_3 = 68;

const int BUSH_SEED_1 = 69;
const int TREE_SEED_1 = 70;
const int TREE_SEED_2 = 72;
const int TREE_SEED_3 = 74;
const int TREE_SEED_4 = 76;
const int TREE_SEED_5 = 77;
const int BIRD_SEED_1 = 78;

const int DETAIL_SHADOW_BASE_COR_1 = 80;
const int DETAIL_SHADOW_BASE_COR_2 = 82;
const int DETAIL_SHADOW_BASE_1 = 84;


const int SCAFFOLD_FLOOR_1 = 5;
const int SCAFFOLD_BASE_1 = 10;
const int BRICK_FLOOR_1 = 15;
const int BRICK_BASE_1 = 20;
const int DIRT_FLOOR_1 = 25;
const int DIRT_BASE = 30;

const int MIX_SCAFFOLD_BRICK_LEFT_FLOOR_1 = 35;
const int MIX_SCAFFOLD_BRICK_RIGHT_FLOOR_1 = 40;
const int MIX_SCAFFOLD_BRICK_LEFT_BASE_1 = 45;
const int MIX_SCAFFOLD_BRICK_RIGHT_BASE_1 = 50;

const int MIX_DIRT_BRICK_LEFT_FLOOR_1 = 55;
const int MIX_DIRT_BRICK_RIGHT_FLOOR_1 = 60;
const int MIX_DIRT_BRICK_LEFT_BASE_1 = 65;
const int MIX_DIRT_BRICK_RIGHT_BASE_1 = 70;
